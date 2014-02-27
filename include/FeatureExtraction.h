// Author: Hu Yuhuang
// Date: 2014-02-27

#include "sys_lib.h"

class FeatureExtraction
{
 public:
  FeatureExtraction()
    {
      
    }

  void extractKeyPoints(cv::Mat in, vector<KeyPoint> & keypoints, int method)
  {
    // In this function, we now support SIFT, SURF, GoodFeatureToTrack only
    // SIFT = 1;
    // SURF = 2;
    // GoodFeatureToTrack = 3;

    int nFeatures=400;

    if (method==1)
      {
	SiftFeatureDetector detector(nFeatures);
	detector.detect(in, keypoints);
      }
    else if (method==2)
      {
	SurfFeatureDetector detector(nFeatures);
	detector.detect(in, keypoints);
      }
    else if (method==3)
      {
	cv::goodFeaturesToTrack(in, keypoints, nFeatures, 0.05, 1.0);
      }
    else
      {
	cout << "error: method is wrong" << endl;
      }
  }

  void findGoodMatch(cv::Mat pre, cv::Mat next, vector<KeyPoint> pre_points, vector<KeyPoint> next_points, int findMatchMethod, vector<DMatch> & goodMatches, vector<Point2f> & preGoodPoints, vector<Point2f> & nextGoodPoints)
  {
    // Find good match using Flann matcher
    // SIFT = 1;
    // SURF = 2;

    if (findMatchMethod==2)
      {
	// for SURF
      }
    else if (findMatchMethod==1)
      {
	// for SIFT
	SiftDescriptorExtractor extractor;
	
	cv::Mat pre_descriptor, next_descriptor;
	extractor.compute(pre, pre_points, pre_descriptor);
	extractor.compute(next, next_points, next_descriptor);

	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	matcher.match(pre_descriptor, next_descriptor, matches);

	double maxDist=0, minDist=10000;

	// find max and min distance
	for (int i=0;i<matches.size();i++)
	  {
	    double dist=matches[i].distance;
	    if (dist>maxDist) maxDist=dist;
	    if (dist<minDist) minDist=dist;
	  }

	// find good matches
	// This parameter can be adjust, now 6 would give a pretty good result for first class
	for (int i=0;i<pre_descriptor.rows;i++)
	{
	  if (matches[i].distance < 6*minDist)
	    {
	      goodMatches.push_back(matches[i]);
	    }
	}

	// located good matches

	for (int i=0; i<goodMatches.size();i++)
	  {
	    preGoodPoints.push_back(pre_points[goodMatches[i].queryIdx].pt);
	    nextGoodPoints.push_back(next_points[goodMatches[i].trainIdx].pt);
	  }
	
      }
  }

  // To-do list in this class
  // 1. Optical Flow method
  // 2. seems goodFeaturesToTrack shared different feature points,
  //    therefore, write another function for it.
  // 3. Consider to write a function to wrap all the process for a set of frames.

};
