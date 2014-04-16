// Author: Hu Yuhuang
// Date: 2014-02-27

#include "sys_lib.h"

class FeatureExtraction
{
 public:
  FeatureExtraction()
    {
      
    }

  void computeVOTKeyPoint(TrackRegion region, vector<KeyPoint> keypoints, cv::Mat descriptors, vector<VOTKeyPoint> & pointsInRegion, vector<VOTKeyPoint> & pointsInBack)
  {
    computeVOTKeyPoint(region.getRectangle(), keypoints, descriptors, pointsInRegion, pointsInBack);
  }

  // Function: this function is to calculate Theta(W;I) and B
  // INPUT
  // region: object region
  // keypoints: all keypoints in image
  // descriptors: all descriptors in image
  // OUTPUT
  // pointsInRegion: points in region
  // pointsInBack: points in background
  void computeVOTKeyPoint(Rect region, vector<KeyPoint> keypoints, cv::Mat descriptors, vector<VOTKeyPoint> & pointsInRegion, vector<VOTKeyPoint> & pointsInBack)
  {
    int noFeature=keypoints.size();

    for (int i=0;i<noFeature;i++)
      {
	VOTKeyPoint temp;
	temp.x=keypoints[i];
	temp.v=descriptors.row(i);

	if ((temp.x.pt.x>region.x && temp.x.pt.x<region.x+region.width) &&
	    (temp.x.pt.y>region.y && temp.x.pt.y<region.y+region.height))
	  pointsInRegion.push_back(temp);
	else pointsInBack.push_back(temp);
      }
  }

  // Function: calculate distance between u and v
  // INPUT
  // u: neighbor of v
  // v: keypoint
  // OUTPUT
  // distance: distance between keypoints
  void computeKeyPointsDistance(VOTKeyPoint U, VOTKeyPoint V, double & distance)
  {
    Mat temp=U.v-V.v;
    Mat dis=temp*temp.t();

    distance=(double)dis.at<float>(0);
  }

  // Function: find the nearest neighbor and distance
  // INPUT
  // B: a set of VOTKeyPoint
  // V: a VOTKeyPoint
  // OUTPUT
  // U: the nearest neighbor
  // distance: distance between keypoint and neighbor
  void computeNearestNeighbor(vector<VOTKeyPoint> B, VOTKeyPoint V, VOTKeyPoint & U, double & distance)
  {
    computeKeyPointsDistance(B[0], V, distance);
    U=B[0];
    int noPoint=B.size();

    for (int i=1;i<noPoint;i++)
      {
	double d=0;
	computeKeyPointsDistance(B[i], V, d);
	if (d<distance)
	  {
	    U=B[i];
	    distance=d;
	  }
      }
  }

  // Function: compute feature set based on parameter
  // INPUT
  // A: original set
  // B: should be previous set
  // C: should be background set
  // OUTPUT
  // F: result feature set
  void computeFeatureSet(vector<VOTKeyPoint> A, vector<VOTKeyPoint> B, vector<VOTKeyPoint> C, vector<VOTKeyPoint> & F)
  {
    int noPoint=A.size();
    double lambda=0.667;

    double nnb=0, nnc=0;
    VOTKeyPoint NNB, NNC;

    for (int i=0;i<noPoint;i++)
      {
	computeNearestNeighbor(B, A[i], NNB, nnb);
	computeNearestNeighbor(C, A[i], NNC, nnc);

	if (nnb<lambda*nnc) F.push_back(A[i]);
      }
  }

  void computeMotionPenalty(TrackRegion W1, TrackRegion W2, double & motionPenalty)
  {
    computeMotionPenalty(W1.getRectangle(), W2.getRectangle(), motionPenalty);
  }

  // Function: compute motion penalty between two window
  // INPUT
  // W1: first window
  // W2: second window
  // OUPUT
  // motionPenalty: motion penalty
  void computeMotionPenalty(Rect W1, Rect W2, double & motionPenalty)
  {
    double gamma=0.5;
    double W1x=(double)W1.x, W1y=(double)W1.y, W1width=(double)W1.width, W1height=(double)W1.height;
    double W2x=(double)W2.x, W2y=(double)W2.y, W2width=(double)W2.width, W2height=(double)W2.height;

    double O1x=W1x+W1width/2;
    double O1y=W1y+W1height/2;
    double O2x=W2x+W2width/2;
    double O2y=W2y+W2height/2;

    motionPenalty=(O1x-O2x)*(O1x-O2x)+(O1y-O2y)*(O1y-O2y);
    motionPenalty+=abs(W1height-W2height);
    motionPenalty+=abs(W1width-W2width);
    
    double ar1=abs(W1height/W1width-W2height/W2width);
    double ar2=abs(W1width/W1height-W2width/W2height);
    motionPenalty+=max(ar1, ar2);

    motionPenalty*=gamma;
  }

  void computeScoreFunction(TrackRegion W, vector<VOTKeyPoint> preO, vector<VOTKeyPoint> B, TrackRegion preW, vector<KeyPoint> keypointsI, cv::Mat descriptorsI, double & score)
  {
    computeScoreFunction(W.getRectangle(), preO, B, preW.getRectangle(), keypointsI, descriptorsI, score);
  }

  // Function: compute score function
  // INPUT
  // W: test window
  // preO: object model in previous frame
  // B: background model
  // preW: previous predicted window
  // keypointsI: keypoints in current frame
  // descriptorsI: descriptors in current frame
  // OUTPUT
  // score: score for test window
  void computeScoreFunction(Rect W, vector<VOTKeyPoint> preO, vector<VOTKeyPoint> B, Rect preW, vector<KeyPoint> keypointsI, cv::Mat descriptorsI, double & score)
  {
    computeMotionPenalty(W, preW, score);
    score*=-1;
    vector<VOTKeyPoint> WInRegion;
    vector<VOTKeyPoint> WInBack;
    computeVOTKeyPoint(W, keypointsI, descriptorsI, WInRegion, WInBack);

    int noPoint=WInRegion.size();

    for (int i=0;i<noPoint;i++)
      {
	vector<VOTKeyPoint> temp;
	vector<VOTKeyPoint> F;
	temp.push_back(WInRegion[i]);
	computeFeatureSet(temp, preO, B, F);
	if (F.size()>0) score++;
	else score--; 
      }
  }

  // Function: this function is to extractor from a image;
  // INPUT
  // in: input image
  // method: SIFT=1, SURF=2;
  // OUTPUT
  // keypoints: extracted keypoints
  // descriptors: extracted descriptors
  void extractFeature(cv::Mat in, vector<KeyPoint> & keypoints, cv::Mat & descriptors, int method)
  {
    int nFeatures=400;

    if (method==1)
      {
	SiftFeatureDetector detector(nFeatures);
	detector.detect(in, keypoints);
	detector.compute(in, keypoints, descriptors);
      }
    else if (method==2)
      {
	SurfFeatureDetector detector(nFeatures);
	detector.detect(in, keypoints);
	detector.compute(in, keypoints, descriptors);
      }
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
	  if (matches[i].distance < 4.53*minDist)
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
