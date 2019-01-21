#include"convert2gray.hpp"

Gray::Gray(ros::NodeHandle n,ros::NodeHandle priv_nh):
	R(0.5)
{
	map_pub = n.advertise<nav_msgs::OccupancyGrid>("/image2map",100);

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
	
	create_obstacle_map(edge_image,&grid_map);	
	grid_map.header.stamp = ros::Time::now();
	map_pub.publish(grid_map);
	cv::waitKey(10);
}

void
Gray::setparam(nav_msgs::OccupancyGrid *map,cv::Mat image){
   	map->header.frame_id = "/map";
	map->data.resize(int(image.rows/R) * int(image.cols/R));
	map->info.width = int(image.cols/R);
	map->info.height = int(image.rows/R);
	map->info.resolution = R;
	map->info.origin.position.x = (0.0 - image.cols)/2.0; 
	map->info.origin.position.y = (0.0 - image.rows)/2.0;

	cout<<"height"<<image.rows<<endl;//height = rows
	cout<<"width"<<image.cols<<endl;//width = cols
}

void 
Gray::create_obstacle_map(
		cv::Mat edge_png, nav_msgs::OccupancyGrid *map_){            //全体のマップを作成
	geometry_msgs::Point obstacle_point;


	for(int col=0;col < edge_png.cols;col++){
		for(int row=0;row < edge_png.rows;row++){
			int x = int(col);
			int y = int((edge_png.rows-1) - row);
			if((0 <= x && x < edge_png.cols) && (0 <= y && y < edge_png.rows)){
				long num = x + y * map_->info.width;
				if((int)edge_png.at<unsigned char>(row,col)) map_->data[num] = 100;
			}
		}

	}

}
