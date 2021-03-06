#include "voxblox_ros/esdf_server.h"

#include <gflags/gflags.h>

int main(int argc, char** argv) {
  ros::init(argc, argv, "voxblox");
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, false);
  google::InstallFailureSignalHandler();
  ros::NodeHandle nh;
  ros::NodeHandle nh_private("~");

  voxblox::EsdfServer node(nh, nh_private);
  
  // Modified
  ros::MultiThreadedSpinner s(2); // 4 Threads
  ros::spin(s);

  //ros::spin();
  return 0;
}
