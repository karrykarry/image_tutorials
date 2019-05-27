#ifndef _SIFT_CAM_HPP_
#define _SIFT_CAM_HPP_

#include<ros/ros.h>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>


// #include <opencv2/features2d/features2d.hpp>
// #include <opencv2/highgui/highgui.hpp>
// #include <opencv2/nonfree/features2d.hpp>
// #include <opencv2/nonfree/nonfree.hpp>
#include<nav_msgs/OccupancyGrid.h>

using namespace std;
using namespace cv;

class Sift_cam{

	private:
		ros::Publisher map_pub;
		
		cv::Mat color_image;
		cv::Mat output_image;
		
		cv::Mat_<cv::Vec3b> img1;
		cv::Mat_<cv::Vec3b> img2;	

	public:
		Sift_cam(ros::NodeHandle n,ros::NodeHandle priv_nh);
		int process();
};

#endif
