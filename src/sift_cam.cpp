#include"sift_cam.hpp"

Sift_cam::Sift_cam(ros::NodeHandle n,ros::NodeHandle priv_nh)
{
	map_pub = n.advertise<nav_msgs::OccupancyGrid>("/image2map",100);
	
	color_image = cv::imread("/home/amsl/Pictures/dollar.png",1);
}




// void
// Sift_cam::process(){
// 	// カラー画像をグレースケールに変換
// 	Mat gray_image;
// 	cvtColor(color_image, gray_image, CV_RGB2GRAY);
// 	normalize(gray_image, gray_image, 0, 255, NORM_MINMAX);
//
//
// // SIFT特徴点の抽出
// 	vector<KeyPoint> keypoints;
// 	vector<KeyPoint>::iterator itk;
// 	double threshold = 0.05;
// 	double edge_threshold = 10.0;
// 	
// 	cv::SiftFeatureDetector detector(threshold, edge_threshold);
// 	// detector.detect(gray_image, keypoints);
//
// 	// キーポイントの数を表示
// 	int keypoint_num = keypoints.size();
// 	cout << "keypoint_num :" << keypoint_num << endl;
//
// 	// 結果を表示
// 	Mat output_image_1, output_image_2;
// 	drawKeypoints(color_image, keypoints, output_image_1, Scalar(0, 255, 0), 0);
// 	drawKeypoints(color_image, keypoints, output_image_2, Scalar(0, 255, 0), 4);
// 	imshow("Result Keypoint", output_image_1);
// 	imshow("Result Keypoint Size and Direction", output_image_2);
// }

int
Sift_cam::process(){

		cv::Mat img_2 = color_image.clone();
		if (!color_image.data ) {
			std::cout << "画像がよみこめません" << std::endl; 
			return -1;
		}
		int minHessian = 400;
		cv::Ptr < cv::xfeatures2d::SURF>detectorSURF = cv::xfeatures2d::SURF::create(minHessian);
		cv::Ptr < cv::xfeatures2d::SIFT>detectorSIFT = cv::xfeatures2d::SIFT::create(minHessian);
		std::vector < cv::KeyPoint>keypoints_1, keypoints_2;
		detectorSURF->detect(color_image, keypoints_1);
		detectorSIFT->detect(img_2, keypoints_2);

		cv::Mat img_1_keypoints;
		cv::Mat img_2_keypoints;
		cv::drawKeypoints(color_image, keypoints_1, img_1_keypoints, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
		cv::drawKeypoints(img_2, keypoints_2, img_2_keypoints, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);

		cv::imshow("INPUT", color_image);
		cv::imshow("SURF", img_1_keypoints);
		cv::imshow("SIFT", img_2_keypoints);

	
		cv::waitKey(2);
}
