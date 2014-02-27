// Author: Hu Yuhuang
// Date: 2014-02-27

#include "sys_lib.h"
#include "votracker_lib.h"

int main(int argc, char ** argv)
{
  string imageList="";
  string regionList="";

  if (argc<3 || argc>3)
    {
      cout << "error: number of arguments is wrong" << endl;
      cout << "useage: ./votdrawbox path_to_image_list path_to_region_list" << endl;

      return 0;
    }
  
  imageList=argv[1];
  regionList=argv[2];

  ////// Load Image //////
  vector<string> imList;
  ifstream fin(imageList.c_str());
  while (!fin.eof())
    {
      string input;
      fin >> input;
      imList.push_back(input);
    }
  cout << "[MESSAGE] Image list loaded" << endl;
  // the last element is empty, due to nature of the file.
  imList.pop_back();
  fin.close();

  vector<cv::Mat> images;
  for (int i=0;i<imList.size();i++)
    {
      images.push_back(imread(imList[i].c_str()));
    }
  cout << "[MESSAGE] Image loaded" << endl;
  ////// Load Region //////
  vector<string> reList;
  fin.open(regionList.c_str());
  while (!fin.eof())
    {
      string input;
      fin >> input;
      reList.push_back(input);
    }
  reList.pop_back();
  fin.close();
  cout << "[MESSAGE] Region information loaded" << endl;

  VOTDraw votdraw;
  ////// Single Image Test //////

  cv::Mat singleImageTest;

  votdraw.drawBox(images[0], singleImageTest, reList[0], 1);
  imshow("Single Image Test", singleImageTest);

  cout << "[MESSAGE] Press any key to continue multiple image test" << endl;
  waitKey(0);

  ////// Multiple Image Test //////

  cout << "[MESSAGE] Multiple images test: Press SPACE to change the image" << endl;
  vector<cv::Mat> multipleImageTest;
  votdraw.drawBoxes(images, multipleImageTest, reList, 1);

  for (int i=0;i<multipleImageTest.size();i++)
    {
      if (waitKey(0)==32 && i<multipleImageTest.size())
	{
	  imshow("Multiple Image Test", multipleImageTest[i]);
	}
      else break;
    }

  return 0;
}
