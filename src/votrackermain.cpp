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

  // to do list
  // 1. draw image
  // 2. implement Kalman filter
  // 3. draw new image
  // 4. output box

  fout.close();

  return 0;
}
