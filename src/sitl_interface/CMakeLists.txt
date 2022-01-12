cmake_minimum_required(VERSION 2.8.3)
project(sitl_interface)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  tf
  std_msgs
  geometry_msgs
  message_generation
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES sitl_interface
  CATKIN_DEPENDS  roscpp
                  rospy
                  tf
                  std_msgs
                  geometry_msgs
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/include
)

## Declare a C++ executable
add_executable(sitl_test_node src/sitl_test_node.cpp)
target_link_libraries(sitl_test_node
  ${catkin_LIBRARIES}
)
