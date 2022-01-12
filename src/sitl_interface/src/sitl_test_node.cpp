/* SITL Inerface                               */
/* Author: Lorenzo Gentilini                   */
/* E-Mail: lorenzo.gentilini6@unibo.it         */
/* Date: September 2020                        */
/* File: sitl_test_node.cpp                    */

#include <ros/ros.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <nav_msgs/Odometry.h>
#include <mavros_msgs/AttitudeTarget.h>

#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2_ros/transform_broadcaster.h>

mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
  current_state = *msg;
}

ros::Publisher odom_pub;
void odom_cb(const nav_msgs::Odometry::ConstPtr& msg){
  nav_msgs::Odometry actualOdom = *msg;
  actualOdom.header.frame_id = "odom";
  odom_pub.publish(actualOdom);

  // Publish TF
  static tf2_ros::TransformBroadcaster br;
  geometry_msgs::TransformStamped transformStamped;
  transformStamped.header.stamp = ros::Time::now();
  transformStamped.header.frame_id = "odom";
  transformStamped.child_frame_id = "base_link";
  transformStamped.transform.translation.x = actualOdom.pose.pose.position.x;
  transformStamped.transform.translation.y = actualOdom.pose.pose.position.y;
  transformStamped.transform.translation.z = actualOdom.pose.pose.position.z;
  transformStamped.transform.rotation.x = actualOdom.pose.pose.orientation.x;
  transformStamped.transform.rotation.y = actualOdom.pose.pose.orientation.y;
  transformStamped.transform.rotation.z = actualOdom.pose.pose.orientation.z;
  transformStamped.transform.rotation.w = actualOdom.pose.pose.orientation.w;

  br.sendTransform(transformStamped);
}

int main(int argc, char **argv){
  ros::init(argc, argv, "test_node");
  ros::NodeHandle nh;

  ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State> ("mavros/state", 10, state_cb);
  ros::Subscriber odom_sub = nh.subscribe<nav_msgs::Odometry> ("mavros/local_position/odom", 1, odom_cb);
  ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool> ("mavros/cmd/arming");
  ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode> ("mavros/set_mode");

  odom_pub = nh.advertise<nav_msgs::Odometry>("/mavros_odom", 1);

  // Setpoint publishing rate MUST be faster than 2Hz
  ros::Rate rate(20.0);

  // Wait for FCU connection
  while(ros::ok() && !current_state.connected){
    ros::spinOnce();
    rate.sleep();
  }

  mavros_msgs::SetMode offb_set_mode;
  offb_set_mode.request.custom_mode = "OFFBOARD";

  mavros_msgs::CommandBool arm_cmd;
  arm_cmd.request.value = true;

  ros::Time last_request = ros::Time::now();

  while(ros::ok()){
    if(current_state.mode != "OFFBOARD" && (ros::Time::now() - last_request > ros::Duration(5.0))){
      if(set_mode_client.call(offb_set_mode) && offb_set_mode.response.mode_sent){
          ROS_INFO("Offboard enabled");
      }
      
      last_request = ros::Time::now();
    } else{
        if(!current_state.armed &&(ros::Time::now() - last_request > ros::Duration(5.0))){
          if(arming_client.call(arm_cmd) &&
            arm_cmd.response.success){
            ROS_INFO("Vehicle armed");
          }
          last_request = ros::Time::now();
        }
    }
      
    ros::spinOnce();
    rate.sleep();
  }

  return 0;
}
