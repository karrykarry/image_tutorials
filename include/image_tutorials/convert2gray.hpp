#ifndef _CONVERT2GRAY_HPP_
#define _CONVERT2GRAY_HPP_

#include<ros/ros.h>
#include<iostream>
#include<nav_msgs/Odometry.h>
#include<sensor_msgs/Imu.h>
#include<geometry_msgs/Pose.h>
#include<geometry_msgs/PoseStamped.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/GridCells.h>
#include<message_filters/subscriber.h>
#include<message_filters/sync_policies/approximate_time.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>
#include <opencv2/opencv.hpp>

static const std::string OPENCV_WINDOW = "Image window";
static const std::string OPENCV_WINDOWS = "Gray window";
#define cell_filter 30

using namespace std;

class Gray{

	private:
		ros::Publisher map_pub;
		cv::Mat input_image;
		cv::Mat gray_image;
		cv::Mat edge_image;
		string input_path;
		double min,max;
		float R;

		nav_msgs::OccupancyGrid grid_map;
	
	public:
		Gray(ros::NodeHandle n,ros::NodeHandle priv_nh);
		void process();
		void setparam(nav_msgs::OccupancyGrid *map,cv::Mat image);
		void create_obstacle_map(cv::Mat edge_png, nav_msgs::OccupancyGrid *map_);
};

#endif
