/* sift.cpp
 *
 * 2018.12.21
 *
 * author : R.Kusakari
 *
*/ 
#include <ros/ros.h>
#include "sift_cam.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "sift");
	ros::NodeHandle n;
	ros::NodeHandle priv_nh("~");

	cout<<"-----sift ----" <<endl;

  ros::Rate rate(1);

	Sift_cam sift_c(n,priv_nh);
	
	while(ros::ok()){
	sift_c.process();

    ros::spinOnce();
    rate.sleep();
	
	}
	// gray.process();
	// ros::spin();

    return 0;
}

       

