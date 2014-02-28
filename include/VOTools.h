// Author: Hu Yuhuang
// Date: 2014-02-28

#include "sys_lib.h"

class VOTools
{
 public:
  VOTools()
    {
    }

  // Function: this function would generate retangle box based on tracked corners
  // in: a vector which restores 4 tracked corners
  // out: a retangle which is estimated from tracked corner
  // method: generate Box method
  //         1. choose max box
  //         2. choose average box
  void generateBox(vector<Point2f> in, cv::Rect & out, int method)
  {
    if (in.size()!=4)
      {
	cout << "error: the size of input is wrong" << endl;
	return ;
      }

    // box calculation
    // now the method is to use maximum box.
    // consider to use average of each side.
    double x=0, y=0, width=0, height=0;

    if (method==1)
      {
	if (in[0].x>in[2].x) x=in[2].x;
	else x=in[0].x;
	if (in[0].y>in[1].y) y=in[1].y;
	else y=in[0].y;
	if (in[1].x>in[3].x) width=in[1].x;
	else width=in[3].x;
	width-=x;
	if (in[2].y>in[3].y) height=in[2].y;
	else height=in[3].y;
	height-=y;
      }
    else if (method==2)
      {
	x=(in[0].x+in[2].x)/2;
	y=(in[0].y+in[1].y)/2;
	width=(in[1].x+in[3].x)/2-x;
	height=(in[2].y+in[3].y)/2-y;
      }

    out.x=x;
    out.y=y;
    out.width=width;
    out.height=height;
  }

  void generateTrackedCorner(cv::Mat pre, vector<Point2f> prePoints, vector<Point2f> nextPoints, vector<Point2f> & next_corners)
  {
    if (next_corners.size()!=4)
      {
	cout << "error: the number of corners is wrong." << endl;
	return ;
      }
    cv::Mat H=findHomography(prePoints, nextPoints, CV_RANSAC);

    // The corner layout is
    // 0: up-left  1: up-right
    // 2: down-left 4: down-right
    vector<Point2f> pre_corners(4);
    pre_corners[0]=cvPoint(0,0);
    pre_corners[1]=cvPoint(pre.cols, 0);
    pre_corners[2]=cvPoint(0, pre.rows);
    pre_corners[3]=cvPoint(pre.cols, pre.rows);

    perspectiveTransform(pre_corners, next_corners, H);

  }
};
