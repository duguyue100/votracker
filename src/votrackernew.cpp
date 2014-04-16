// Author: Hu Yuhuang
// Date: 2014-04-16

#include "sys_lib.h"
#include "votracker_lib.h"

void computeWindow(vector<VOTKeyPoint> preO, vector<VOTKeyPoint> B, Rect preW, vector<KeyPoint> keypointsI, cv::Mat descriptorsI, Rect & predictedW)
{
  // for ESS
}

void computeWindow(vector<VOTKeyPoint> preO, vector<VOTKeyPoint> B, TrackRegion preW, vector<KeyPoint> keypointsI, cv::Mat descriptorsI, Rect & predictedW)
{
  computeWindow(preO, B, preW.getRectangle(), keypointsI, descriptorsI, predictedW);
}

void tracking(vector<VOTKeyPoint> preO, vector<VOTKeyPoint> B, Rect preW, vector<KeyPoint> keypointsI, cv::Mat descriptorsI, Rect & predictedW, vector<VOTKeyPoint> & nextO)
{
  // for background, seems need to calculate again based on dynamic model
  nextO=preO;
  FeatureExtraction featureExtractor;
  vector<VOTKeyPoint> nextWInRegion;
  vector<VOTKeyPoint> nextWInBack;
  vector<VOTKeyPoint> F;

  // compute predicted window
  computeWindow(preO, B, preW.getRectangle(), keypointsI, descriptorsI, predictedW);

  // compute feature set
  featureExtractor.computeVOTKeyPoint(region, keypointsI, descriptorsI, nextWInRegion, nextWInBack);
  featureExtractor.computeFeatureSet(nextWInRegion, preO, B, F);

  // update dynamic model
  int noPoint=F.size();
  for (int i=0;i<noPoint;i++)
    nextO.push_back(F[i]);
}

int main(int argc, char ** argv)
{
  string imageList="";
  string regionList="";
  
  ////// configure input file arguments
  if (argc<3 || argc>3)
    {
      cout << "wrong number of arguments" << endl;
      return 0;
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

  // Testing for single image
  // 1. extract SIFT keypoint and descriptor. [DONE]
  // 2. complete necessary computing function.
  // 3. complete ESS.
  // 4. Test the system on single image first.

  FeatureExtraction featureExtractor;
  VOTools tools;
  vector<KeyPoint> prePoints;
  Mat preDescriptors;
  vector<KeyPoint> nextPoints;
  Mat nextDescriptors;

  Mat pre=images[0];
  Mat next=images[1];
  featureExtractor.extractFeature(pre, prePoints, preDescriptors, 1);
  featureExtractor.extractFeature(next, nextPoints, nextDescriptors, 1);

  vector<KeyPoint> prePointsInRegion;
  vector<KeyPoint> prePointsInBack;
  Mat preDescriptorsInRegion;
  Mat preDescriptorsInBack;

  vector<VOTKeyPoint> preInRegion;
  vector<VOTKeyPoint> preInBack;

  featureExtractor.computeVOTKeyPoint(originalRegion, prePoints, preDescriptors, preInRegion, preInBack);

  double distance=0;
  VOTKeyPoint U;
  featureExtractor.computeNearestNeighbor(preInBack, preInRegion[0], U, distance);
  cout << preInRegion.size() << endl << preInBack.size() << endl << distance <<  endl;
  
  return 0;
}
