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
  featureExtractor.findGoodMatch(pre, next, pre_points, next_points, 2, goodMatches, preGoodPoints, nextGoodPoints);

  Mat image_matches;
  drawMatches(pre, pre_points, next, next_points, goodMatches, image_matches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

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
