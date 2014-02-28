// Author: Hu Yuhuang
// Date: 2014-02-22
// This function is to establish a data structure to encode 

#include "sys_lib.h"

class TrackRegion{

 public:
  double x;
  double y;
  double width;
  double height;

 public:

  // constructors

  TrackRegion(double inx, double iny, double inwidth, double inheight)
    {
      x=inx;
      y=iny;
      width=inwidth;
      height=inheight;
    }

  TrackRegion(cv::Rect rect)
    {
      x=rect.x;
      y=rect.y;
      width=rect.width;
      height=rect.height;
    }

  TrackRegion(string regionInfo)
    {
      int start=0;
      int end=0;

      string stx="";
      while (end<regionInfo.size())
	{
	  if (regionInfo[end]!=',')
	    {
	      stx+=regionInfo[end];
	      end++;
	    }
	  else break;
	}
      x=atof(stx.c_str());
      end++;

      string sty="";
      while (end<regionInfo.size())
	{
	  if (regionInfo[end]!=',')
	    {
	      sty+=regionInfo[end];
	      end++;
	    }
	  else break;
	}
      y=atof(sty.c_str());
      end++;

      string stwidth="";
      while (end<regionInfo.size())
	{
	  if (regionInfo[end]!=',')
	    {
	      stwidth+=regionInfo[end];
	      end++;
	    }
	  else break;
	}
      width=atof(stwidth.c_str());
      end++;

      string stheight="";
      while (end<regionInfo.size())
	{
	  if (regionInfo[end]!=',')
	    {
	      stheight+=regionInfo[end];
	      end++;
	    }
	  else break;
	}
      height=atof(stheight.c_str());
    }

  TrackRegion()
    {
      x=0;
      y=0;
      width=0;
      height=0;
      width=0;
    }

 public:

  // set of setting and getting functions
  void setX(double inx)
  {
    x=inx;
  }

  void setY(double iny)
  {
    y=iny;
  }

  void setWidth(double inwidth)
  {
    width=inwidth;
  }

  void setHeight(double inheight)
  {
    height=inheight;
  }

  double getX()
  {
    return x;
  }

  double getY()
  {
    return y;
  }

  double getWidth()
  {
    return width;
  }

  double getHeight()
  {
    return height;
  }

  // 
  string getRegion()
  {
    stringstream ss;
    string region;

    ss << x << "," << y << "," << width << "," << height;
    ss >> region;

    return region;
  }

  // print region
  void pringRegion()
  {
    cout << x << "," << y << "," << width << "," << height << endl;
  }

};
