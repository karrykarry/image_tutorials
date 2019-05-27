/* optical_flow_node.cpp
 *
 * 2018.12.21
 *
 * author : R.Kusakari
 *
 */ 
#include <ros/ros.h>
#include "optical_flow_test.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	ros::init(argc, argv, "optical_flow");
	ros::NodeHandle n;
	ros::NodeHandle priv_nh("~");

	cout<<"---- optical_flow ----" <<endl;

	ros::Rate rate(5);

	Flow flow(n,priv_nh);

	while(ros::ok()){
		if(flow.flag) flow.process_cpu();

		ros::spinOnce();
		rate.sleep();

	}
	// gray.process();
	// ros::spin();

	return 0;
}




