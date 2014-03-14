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
  VOTools tools;
  vector<KeyPoint> pre_points;
  vector<KeyPoint> next_points;

  Mat pre=images[0](Rect(originalRegion.x, originalRegion.y, originalRegion.width, originalRegion.height));
  Mat nextOrigin=images[1];
  TrackRegion selectedRegion;
  tools.selectTrackedRegion(nextOrigin, originalRegion, selectedRegion);
 
  Mat next=nextOrigin(Rect(selectedRegion.x, selectedRegion.y, selectedRegion.width, selectedRegion.height));
  featureExtractor.extractKeyPoints(pre, pre_points, 1);
  featureExtractor.extractKeyPoints(next, next_points, 1);

  vector<DMatch> goodMatches;
  vector<Point2f> preGoodPoints;
  vector<Point2f> nextGoodPoints;
  featureExtractor.findGoodMatch(pre, next, pre_points, next_points, 1, goodMatches, preGoodPoints, nextGoodPoints);
  vector<Point2f> next_corners(4);
  Rect trackedRegion;
  VOTDraw votdraw;
  tools.generateTrackedCorner(pre, preGoodPoints, nextGoodPoints, next_corners);
  tools.generateBox(next_corners, trackedRegion, 2);

  tools.calculateOriginalRegion(selectedRegion.getRectangle(), trackedRegion, trackedRegion);
  votdraw.drawBox(next, next, trackedRegion, 2);
  imshow("test", next);
  waitKey(0);

  cout << trackedRegion.x << "," << trackedRegion.y << "," << trackedRegion.width << "," << trackedRegion.height << endl;

  ////// Multiple frames match //////

  VOTools tool;
  FeatureExtraction f;
  cv::Rect pre_region=Rect(originalRegion.x, originalRegion.y, originalRegion.width, originalRegion.height);
  for (int i=0;i<images.size()-1 ;i++)
    {
      cv::Mat preImage=images[i](pre_region);
      cv::Mat nextImageOrigin=images[i+1];
      tools.selectTrackedRegion(nextImageOrigin, pre_region, selectedRegion);
      cv::Mat nextImage=nextImageOrigin(selectedRegion.getRectangle());

      // find keypoints
      vector<KeyPoint> pPoints;
      vector<KeyPoint> nPoints;
      f.extractKeyPoints(preImage, pPoints, 1);
      f.extractKeyPoints(nextImage, nPoints, 1);

      // find good matches
      vector<DMatch> goodMatch;
      vector<Point2f> preGood;
      vector<Point2f> nextGood;
      f.findGoodMatch(preImage, nextImage, pPoints, nPoints, 1, goodMatch, preGood, nextGood);
      vector<Point2f> ncorners(4);
      cv::Rect tRegion;
      // generate result
      tool.generateTrackedCorner(preImage, preGood, nextGood, ncorners);
      tool.generateBox(ncorners, tRegion, 2);

      tools.calculateOriginalRegion(selectedRegion.getRectangle(), tRegion, tRegion);

      // output result;
      fout << TrackRegion(tRegion).getRegion() << endl;
      // reset pre_region
      pre_region=tRegion;

      // show result

      Mat image_matches;
      drawMatches(preImage, pPoints, nextImage, nPoints, goodMatch, image_matches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
      
      imshow("test", image_matches);
      waitKey(0);

      cv::Mat temp;
      votdraw.drawBox(nextImageOrigin, temp, tRegion, 2);
      imshow("test1", temp);
      waitKey(0);
    }

  // to do list
  // 1. draw image [DONE]
  // 2. write a keypoint extractor library [partially DONE]
  // 3. complete a feature matching for every frame and examine result.
  // 4. implement Kalman filter
  // 5. draw new image
  // 6. output box

  /*
  Mat image_matches;
  drawMatches(pre, pre_points, next, next_points, goodMatches, image_matches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

  imshow("test", image_matches);
  waitKey(0);
  */

  fout.close();

  return 0;
}
