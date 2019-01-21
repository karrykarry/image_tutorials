/* convert2gray.cpp
 *
 * 2018.12.21
 *
 * author : R.Kusakari
 *
*/ 
#include <ros/ros.h>
#include "convert2gray.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "convert");
	ros::NodeHandle n;
	ros::NodeHandle priv_nh("~");

	cout<<"-----change gray----" <<endl;

  ros::Rate rate(1);

	Gray gray(n,priv_nh);
	
	while(ros::ok()){
	gray.process();

    ros::spinOnce();
    rate.sleep();
	
	}
	// gray.process();
	// ros::spin();

    return 0;
}

       
