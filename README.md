# Student ROS Workspace
This repository contains a ROS Noetic workspace with the basics tools to develop novel UAV software and simulate it via the [PX4 Autopilot](https://github.com/PX4/PX4-Autopilot.git).

Here is a list of the provided packages:
* toy_pkg (provides an example package that can be used to reproduce others new)
* [voxblox](https://github.com/ethz-asl/voxblox) (provides all tools to build and manage real-time Euclidean Signed Distance Fields (ESDF) maps)
* [octomap_mapping](https://github.com/OctoMap/octomap_mapping) (provides all tools to build and manage real-time occupancy maps)
* sitl_interface (provides all tools to connect your own ROS nodes to the Gazebo-simulated UAV)
* [realsense](https://github.com/IntelRealSense/realsense-ros) (provides all drivers to connect realsense cameras to your own ROS node)

Please keep the provided packages as an example to develop your owns.