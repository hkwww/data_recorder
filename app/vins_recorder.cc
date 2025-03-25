#include <nav_msgs/Odometry.h>
#include <ros/ros.h>
#include <rosbag/bag.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/Imu.h>

rosbag::Bag bag;

std::string imu_topic = "/mavros/imu/data_raw";
std::string image_topic = "/color_image";
std::string gt_pose_topic = "/mavros/local_position/odom";

void ImageHandler(const sensor_msgs::Image::ConstPtr& msg) {
  bag.write(image_topic, msg->header.stamp, *msg);
}

void ImuHandler(const sensor_msgs::Imu::ConstPtr& msg) {
  bag.write(imu_topic, msg->header.stamp, *msg);
}

void PoseHandler(const nav_msgs::Odometry::ConstPtr& msg) {
  bag.write(gt_pose_topic, msg->header.stamp, *msg);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "vins_recorder");

  ros::NodeHandle priv_hh("~");
  std::string bag_path;
  priv_hh.param("bag_path", bag_path, std::string(""));

  bag.open(bag_path, rosbag::bagmode::Write);

  ros::NodeHandle nh;
  ros::Subscriber sub_image = nh.subscribe(image_topic, 100000, ImageHandler);
  ros::Subscriber sub_imu = nh.subscribe(imu_topic, 10000, ImuHandler);
  ros::Subscriber sub_gt_pose = nh.subscribe(gt_pose_topic, 10000, PoseHandler);

  ros::spin();

  bag.close();

  return 0;
}