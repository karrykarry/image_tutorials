#ifndef _OPTICAL_FLOW_TEST_HPP_
#define _OPTICAL_FLOW_TEST_HPP_

#include<ros/ros.h>
#include<iostream>
#include<vector>
#include<string.h>

#include<sensor_msgs/Image.h>
#include<image_transport/image_transport.h>
#include<cv_bridge/cv_bridge.h>
#include<opencv2/opencv.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/xfeatures2d.hpp>
#include<opencv2/cudaoptflow.hpp>
#include<opencv2/superres/optical_flow.hpp>
// #include<opencv2/cuda.hpp>
#include<opencv2/cudaimgproc.hpp>
// #include<opencv2/core/private.cuda.hpp>

#include<nav_msgs/OccupancyGrid.h>

// #include<opencv2/gpu/gpu.hpp>

using namespace std;
using namespace cv;

class Flow{

	private:
		ros::Publisher result_bgr_pub;
		ros::Publisher result_hsv_pub;
		ros::Subscriber image_sub;
		cv_bridge::CvImage cv_ptr;

		cv::Mat pre_image;
		cv::Mat cur_image;
	
		cv::Ptr<cv::superres::DenseOpticalFlowExt> opticalFlow;

	public:
		Flow(ros::NodeHandle n,ros::NodeHandle priv_nh);
		void imagecallback(const sensor_msgs::Image::ConstPtr& msg);
		
		bool flag;

		int process_cpu();
		int process_gpu();
};

#endif

