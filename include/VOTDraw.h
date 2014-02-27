// Author: Leong Chin Poh & Hu Yuhuang
// Date: 2014-02-26

#include "sys_lib.h"

class VOTDraw
{
 public:
  VOTDraw()
    {
      
    }

  ////// Draw Box Functions //////
  void drawBox(cv::Mat in, cv::Mat & out, std::string region, int color)
  {
    TrackRegion temp(region);
    drawBox(in, out, temp, color);
  }

  void drawBox(cv::Mat in, cv::Mat & out, TrackRegion region, int color)
  {
    Rect temp;
    temp.x=region.x;
    temp.y=region.y;
    temp.width=region.width;
    temp.height=region.height;
    out=in;
    drawBox(out, temp, color);
  }

  void drawBox(cv::Mat in, cv::Mat & out, cv::Rect region, int color)
  {
    out=in;
    drawBox(out, region, color);
  }

  void drawBox(cv::Mat & out, cv::Rect region, int color)
  {
    if (color==1) // draw red box
      cv::rectangle(out, region, CV_RGB(255,0,0), 1);
    else if (color==2) // draw green box
      cv::rectangle(out, region, CV_RGB(0,255,0), 1);
  }

  void drawBoxes(vector<cv::Mat> in, vector<cv::Mat> & out, vector<string> list, int color)
  {
    if (in.size()!=list.size())
      {
	cout << "error: number of images and image list do not match" << endl;
	return ;
      }

    for (int i=0;i<in.size();i++)
      {
	cv::Mat temp;
	drawBox(in[i], temp, list[i], color);
	out.push_back(temp);
	temp.release();
      }
  }

  void drawBoxes(vector<cv::Mat> in, vector<cv::Mat> & out, vector<TrackRegion> list, int color)
  {
    if (in.size()!=list.size())
      {
	cout << "error: number of images and image list do not match" << endl;
	return ;
      }

    for (int i=0;i<in.size();i++)
      {
	cv::Mat temp;
	drawBox(in[i], temp, list[i], color);
	out.push_back(temp);
	temp.release();
      }
  }

  void drawBoxes(vector<cv::Mat> in, vector<cv::Mat> & out, vector<Rect> list, int color)
  {
    if (in.size()!=list.size())
      {
	cout << "error: number of images and image list do not match" << endl;
	return ;
      }

    for (int i=0;i<in.size();i++)
      {
	cv::Mat temp;
	drawBox(in[i], temp, list[i], color);
	out.push_back(temp);
	temp.release();
      }
  }

  ////// Draw Keypoints Functions //////
  
};
