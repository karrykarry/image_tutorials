#include"optical_flow_test.hpp"

Flow::Flow(ros::NodeHandle n, ros::NodeHandle priv_nh):
	flag(false)
{
	result_bgr_pub = n.advertise<sensor_msgs::Image>("/usb_cam/output/BGR",100);
	result_hsv_pub = n.advertise<sensor_msgs::Image>("/usb_cam/output/HSV",100);
	image_sub = n.subscribe("/usb_cam/image_raw", 10, &Flow::imagecallback, this);

	// opticalFlow = superres::createOptFlow_DualTVL1();//CPU TV-L1
	opticalFlow = superres::createOptFlow_Farneback();//CPU TV-L1
	// opticalFlow = cv::superres::createOptFlow_DualTVL1_CUDA();//GPU TV-L1
	// opticalFlow = superres::createOptFlow_DualTVL1_GPU;//CPU TV-L1


}


void
Flow::imagecallback(const sensor_msgs::Image::ConstPtr& msg){
	static bool IsFirst = true;

	// cv_bridge::CvImagePtr cv_ptr;
	try
	{
		cv_ptr = *cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}

	cur_image = cv_ptr.image;
	if(IsFirst){
		pre_image = cur_image;
		IsFirst = false;
		flag = true;
	}


	// process_cpu();
	// process_gpu();

	// cv::cvtColor(cv_ptr->image,color_image,cv::COLOR_BGR2GRAY);
	//
	// cv_ptr->image = color_image;
    //
	// // cv::namedWindow("image",CV_WINDOW_AUTOSIZE);
	// // cv::imshow("image",color_image);
	// // cv::imshow("image",cv_ptr->image);
    //
	// sensor_msgs::ImagePtr output_image = 
	// 	cv_bridge::CvImage(std_msgs::Header(),"mono8",color_image).toImageMsg();

	// result_pub.publish(cv_ptr->toImageMsg());
	// result_pub.publish(output_image);
	cv::waitKey(1);


}


int
Flow::process_cpu(){
	cv::Mat flowX;
	cv::Mat flowY;

	opticalFlow->calc(pre_image,cur_image,flowX,flowY);

	Mat magnitude,angle;
	cartToPolar(flowX,flowY,magnitude,angle,true);		//オプティカルフローを極座標に変換

	Mat hsvPlanes[3];
	hsvPlanes[0] = angle;
	normalize(magnitude, magnitude, 0, 1, NORM_MINMAX);	//正規化
	hsvPlanes[1] = magnitude;
	hsvPlanes[2] = Mat::ones(magnitude.size(), CV_32F);

	//HSVを合成して1枚の画像にする
	Mat hsv;
	merge(hsvPlanes, 3, hsv);

	Mat flowBgr;
	cvtColor(hsv, flowBgr, cv::COLOR_HSV2BGR);

	cv_bridge::CvImage hsv_image;
	// sensor_msgs::Image hsv_image;

	// sensor_msgs::ImagePtr output_image = 
	//  	cv_bridge::CvImage(std_msgs::Header(),"bgr8",flowBgr).toImageMsg();
	
	// hsv_image = cv_bridge::
	
	// hsv_image.header.stamp = ros::Time::now();
	// hsv_image.header.frame_id = "/map";
	hsv_image.header = cv_ptr.header;
	// hsv_image.encoding = sensor_msgs::image_encodings::TYPE_32FC1;
	// hsv_image.encoding = sensor_msgs::image_encodings::TYPE_8UC3;
	hsv_image.encoding = cv_ptr.encoding;
	// hsv_image.encoding = sensor_msgs::image_encodings::BAYER_GRBG8;
	// hsv_image.encoding = sensor_msgs::image_encodings::BGR8;
	hsv_image.image = flowBgr;

	result_hsv_pub.publish(hsv_image.toImageMsg());
	// result_hsv_pub.publish(output_image);




	cv::imshow("optical flow BGR", flowBgr);
	cv::imshow("optical flow HSV", hsv);
	cv::imshow("cur_image", cur_image);
	cv::imshow("pre_image", pre_image);

	pre_image = cur_image;

	return 0;
}

int
Flow::process_gpu(){

	cv::Mat flowX;
	cv::Mat flowY;
	
	cv::cuda::GpuMat gpuCurr(cur_image), gpuPrev(pre_image), gpuFlowX, gpuFlowY;
	
	opticalFlow->calc(gpuPrev, gpuCurr, gpuFlowX, gpuFlowY);
	gpuFlowX.download(flowX);
	gpuFlowY.download(flowY);

	Mat magnitude,angle;
	cartToPolar(flowX,flowY,magnitude,angle,true);		//オプティカルフローを極座標に変換

	Mat hsvPlanes[3];
	hsvPlanes[0] = angle;
	normalize(magnitude, magnitude, 0, 1, NORM_MINMAX);	//正規化
	hsvPlanes[1] = magnitude;
	hsvPlanes[2] = Mat::ones(magnitude.size(), CV_32F);

	//HSVを合成して1枚の画像にする
	Mat hsv;
	merge(hsvPlanes, 3, hsv);

	Mat flowBgr;
	cvtColor(hsv, flowBgr, cv::COLOR_HSV2BGR);

	cv::imshow("optical flow BGR", flowBgr);
	cv::imshow("optical flow HSV", hsv);
	cv::imshow("input", cur_image);

	pre_image = cur_image;

	return 0;


}
