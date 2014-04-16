VOTracker
=========

This project includes the code for final assignment of WAES3106 Image Processing

### Update ###

+ 20140222 [First update, established a framework]
+ 20140227 [Second update, added drawing library]
+ 20140227 [Second update, added feature extraction library]
+ 20140228 [Third update, added some tools]
+ 20140314 [Fourth update, updated tools and new methods]
+ 20140416 [Fifth update, updated utility functions for tracking]

### To-do List ##

+ Implement a drawing library [Partially DONE, Contributor: Leong Chin Poh]
  - Key points drawing needed.
  - Segment image drawing needed.
+ Implement a Key points tracking library based on different methods
  - Optical Flow
  - Homography [DONE]
+ Implement Kalman filter library for object tracking
+ Implement Information filter library for object tracking
+ Implement a segmentation library for segmenting object according to features
+ Implement ESS.

### Configuration Guide ###

1. Clone the repo to anywhere you want and then `cd` to the directory.

`$ git clone https://github.com/duguyue100/votracker`

`$ cd votracker`

2. Run CMake to configure the environment.

`$ cmake .`

3. Run `make` to compile the whole project.

`$ make`

4. The files in `resources` are specified for particular user, in case you need to generate your own list, you can follow two methods:
  - Use VOT evaluation kit to generate image list
  - [For Linux and Mac OS only]If you don't have VOT evaluation kit, you need to decompress VOT dataset to a folder, in this case, we assume the absolute path of the folder is `/home/user/sequences`, and we want to generate complete image list for `bicycle` folder. you can run following commands:

`$ cd /home/user/sequences`

`$ cd bicycle`

`$ ls -d -1 $PWD/*.jpg > images.txt`

Then a complete image list is generated in `bicycle` folder.

### Notes ###

1. Currently, we use Flann matcher only to detect the matched file, this could result misdetection after around 20 frames.
2. In current version, we constrain the search window, the effect for first few frame is fine, however, due to some unknown problems, the box suddenly out of the search region. [20140314]

### Contact ###

Hu Yuhuang

_No. 42, North, Flatland_

Email: duguyue100@gmail.com
