// Author: Hu Yuhuang
// Date: 2014-03-20

#include "sys_lib.h"
#include "votracker_lib.h"

// Function: check validation of arguments
// --- Input ---
// argc: number of arguments
// argv: array of arguments
// --- Output ---
// imageList: address of image list file
// regionList: address of ground truth file
void CHECKARGU(int argc, char ** argv, string & imageList, string & regionList)
{
  if (argc<3 || argc>3)
    {
      cout << "wrong arguments" << endl;
      exit(0);
    }
  else
    {
      imageList=argv[1];
      regionList=argv[2];
    }
}

// Function: load data
// --- Input ---
// imageList: address of image list file
// regionList: address of ground truth file
// --- Output ---
// imList: vector form of all images' address
// regionInfo: ground truth region of first frame
void LOADDATA(string imageList, string regionList, vector<string> & imList, string & regionInfo)
{
  ////// load images' address
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
  fin >> regionInfo;
  fin.close(); 
}

// Function: load all frames
// --- Input ---
// imList: imList: vector form of all images' address
// --- Output ---
// images: contains all frames
void LOADIMAGES(vector<string> imList, vector<cv::Mat> & images)
{
  for (int i=0;i<imList.size();i++)
    {
      images.push_back(imread(imList[i].c_str()));
    }
}

int main(int argc, char ** argv)
{
  /*----------PREPROCESSING----------*/

  ////// Image List and Ground Truth //////
  string imageList="";
  string regionList="";

  ///// Data Container //////
  vector<string> imList;
  vector<cv::Mat> images;
  string regionInfo;
 
  ////// I/O Variables //////
  ofstream fout("output.txt");
 
  CHECKARGU(argc, argv, regionList, regionList);
  LOADDATA(imageList, regionList, imList, regionInfo);
  LOADIMAGES(imList, images);


  /* HAAR TEST */

  ////// Data Container //////
  vector<cv::Mat> trainSet;

  ////// Tools //////
  TrackRegion originalRegion(regionInfo);
  TrackRegion selectedRegion;

  ////// Supporting Variables //////
  VOTools tools;
  
  Mat pre=images[0](originalRegion.getRectangle());

  // init training set
  tools.addToTrainSet(trainSet, pre, 5);

  Mat nextOrigin=images[1];
  tools.selectTrackedRegion(nextOrigin, originalRegion, selectedRegion);
 
  Mat next=nextOrigin(selectedRegion.getRectangle());

  // to-do list:
  // 1. set up training dataset [each sample region is duplicated for 5 times].
  // 2. train haar detector
  // 3. process image
  // 4. detect box and add detected region to training dataset.


  fout.close();
  return 0;
}
