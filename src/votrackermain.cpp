// Author: Hu Yuhuang
// Date: 2014-02-22

#include "sys_lib.h"
#include "votracker_lib.h"

int main(int argc, char ** argv)
{
  string imageList="";
  string regionList="";

  ////// configure input file arguments
  if (argc<3)
    {
      cout << "not enough arguments" << endl;
      return 0;
    }
  else if (argc>3)
    {
      cout << "too many arguments" << endl;
    }
  else
    {
      imageList=argv[1];
      regionList=argv[2];
    }

  ////// load images

  vector<string> imList;
  ifstream fin(imageList.c_str());
  while (!fin.eof())
    {
      string input;
      fin >> input;
      imList.push_back(input);
    }
  // the last element is empty, due to nature of the file.
  imList.pop_back();
  fin.close();

  ////// load region for first frame
  fin.open(regionList.c_str());
  string regionInfo;
  fin >> regionInfo;
  fin.close();
  TrackRegion originalRegion(regionInfo);

  ////// processing
  ofstream fout("output.txt");

  // load image frame
  vector<cv::Mat> images;

  for (int i=0;i<imList.size();i++)
    {
      images.push_back(imread(imList[i].c_str()));
    }

  // Single frame point matching

  FeatureExtraction featureExtractor;

  vector<KeyPoint> pre_points;
  vector<KeyPoint> next_points;

  Mat pre=images[0](Rect(originalRegion.x, originalRegion.y, originalRegion.width, originalRegion.height));
  Mat next=images[1];

  featureExtractor.extractKeyPoints(pre, pre_points, 1);
  featureExtractor.extractKeyPoints(next, next_points, 1);

  vector<DMatch> goodMatches;
  vector<Point2f> preGoodPoints;
  vector<Point2f> nextGoodPoints;
  featureExtractor.findGoodMatch(pre, next, pre_points, next_points, 1, goodMatches, preGoodPoints, nextGoodPoints);

  cout << preGoodPoints.size() << endl;
  cout << nextGoodPoints.size() << endl;

  cout << goodMatches.size() << endl;
  Mat image_matches;
  drawMatches(pre, pre_points, next, next_points, goodMatches, image_matches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

  imshow("test", image_matches);
  waitKey(0);

  
  cv::Mat H=findHomography(preGoodPoints, nextGoodPoints, CV_RANSAC);

  vector<Point2f> pre_corners(4);
  pre_corners[0]=cvPoint(0, 0);
  pre_corners[1]=cvPoint(pre.cols, 0);
  pre_corners[2]=cvPoint(0, pre.rows);
  pre_corners[3]=cvPoint(pre.cols, pre.rows);
  vector<Point2f> next_corners(4);

  perspectiveTransform(pre_corners, next_corners, H);

  line( image_matches, next_corners[0] + Point2f( pre.cols, 0), next_corners[1] + Point2f( pre.cols, 0), Scalar(0, 255, 0), 1 );
  line( image_matches, next_corners[1] + Point2f( pre.cols, 0), next_corners[3] + Point2f( pre.cols, 0), Scalar(0, 255, 0), 1 );
  line( image_matches, next_corners[2] + Point2f( pre.cols, 0), next_corners[0] + Point2f( pre.cols, 0), Scalar(0, 255, 0), 1 );
  line( image_matches, next_corners[2] + Point2f( pre.cols, 0), next_corners[3] + Point2f( pre.cols, 0), Scalar(0, 255, 0), 1 );

  imshow("test", image_matches);
  waitKey(0);
  // to do list
  // 1. draw image [DONE]
  // 2. write a keypoint extractor library [partially DONE]
  // 3. complete a feature matching for every frame and examine result.
  // 4. implement Kalman filter
  // 5. draw new image
  // 6. output box

  fout.close();

  return 0;
}
