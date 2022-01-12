#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TransformStamped.h>

ros::Publisher odometryPub;

void odometryCallback(const geometry_msgs::PoseStamped::ConstPtr& msg){
  geometry_msgs::TransformStamped outMsg;
  outMsg.header = msg->header;
  outMsg.transform.translation.x = msg->pose.position.x;
  outMsg.transform.translation.y = msg->pose.position.y;
  outMsg.transform.translation.z = msg->pose.position.z;
  outMsg.transform.rotation = msg->pose.orientation;
  outMsg.child_frame_id = "base_link";
  odometryPub.publish(outMsg);
}

int main(int argc, char **argv){
  ros::init(argc, argv, "proxy_node");
  ros::NodeHandle nh("~");

  // Publishers
  odometryPub = nh.advertise<geometry_msgs::TransformStamped>("/mavros/local_position/transform", 1);

  // Subscribers
  ros::Subscriber odometrySub = nh.subscribe("/mavros/local_position/pose", 1, odometryCallback);

  ros::spin();

  return 0;
}
