VOTracker
=========

This project includes the code for final assignment of WAES3106 Image Processing

### Update ###

+ 20140222 [First update, established a framework]
+ 20140227 [Second update, added drawing library]
+ 20140227 [Second update, added feature extraction library]

### To-do List ##

+ Implement a drawing library [Partially DONE, Contributor: Leong Chin Poh]
  - Key points drawing needed.
  - Segment image drawing needed.
+ Implement a Key points tracking library based on different methods
  - Optical Flow
  - Homography
+ Implement Kalman filter library for object tracking
+ Implement Information filter library for object tracking
+ Implement a segmentation library for segmenting object according to features

### Configuration Guide ###

1. Clone the repo to anywhere you want and then `cd` to the directory.
2. Because this project is written in Mac OS X, if you are using other systems, please remove following directories and files before you run `cmake`: `CMakeFiles`, `CMakeCache.txt` and `libvotrackerlib.dylib` under `lib` folder.
3. Run `cmake .` to configure the environment.
4. Run `make` to compile the whole project.

### Contact ###

Hu Yuhuang

_No. 42, North, Flatland_

Email: duguyue100@gmail.com
