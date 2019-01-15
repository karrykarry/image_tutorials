#include"convert2gray.hpp"

Gray::Gray(ros::NodeHandle n,ros::NodeHandle priv_nh):
	width(60),height(30),R(0.1)
{
	priv_nh.getParam("/input_image",input_path);
	priv_nh.getParam("/min_num",min);
	priv_nh.getParam("/max_num",max);
	
	input_image = cv::imread("/home/amsl/Pictures/tsukuba.png",1);
	if(input_image.empty()){
		cout<<"aaaaa"<<endl;
		return;
	}

	setparam(&grid_map,input_image);
}

void
Gray::process(){

	// cout<<<<endl;
	cvtColor(input_image, gray_image,CV_RGB2GRAY);
	cv::Canny(gray_image,edge_image,min,max,3);
	
	cv::namedWindow("Edge",CV_WINDOW_AUTOSIZE);
	cv::imshow("Edge",edge_image);
	
	
	grid_map.header.stamp = ros::Time::now();
	cv::waitKey(0);
}

void
Gray::setparam(nav_msgs::OccupancyGrid *map,cv::Mat image){
   	map->header.frame_id = "/map";
	map->data.resize(int(image.rows/R) * int(image.cols/R));
	map->info.width = int(image.rows/R);
	map->info.height = int(image.cols/R);
	map->info.resolution = R;
	map->info.origin.position.x = (0.0 - image.rows)/2.0; 
	map->info.origin.position.y = (0.0 - image.cols)/2.0;
}

void 
Gray::create_obstacle_map(
		cv::Mat edge_png, nav_msgs::OccupancyGrid *map_){            //全体のマップを作成
	geometry_msgs::Point obstacle_point;

	vector<int>	count((long(width/R) * long(height/R)), 0);
	for(int i = 0; i != map_->data.size(); i++){
		map_->data[i] = 0;
	}


	// for(size_t i = 0; i < cloud->points.size(); i++){
	// 	int x = int((cloud->points[i].x - map_->info.origin.position.x) / R);
	// 	int y = int((cloud->points[i].y - map_->info.origin.position.y) / R);
	// 	if((0 <= x && x < width/R) && (0 <= y && y < height/R)){
	// 		long num = x + y * map_->info.width;
	// 		count[num] += 1; 
	// 	}
	// }

}
