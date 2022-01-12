cmake_minimum_required(VERSION 3.0.2)
project(toy_pkg)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES toy_pkg
  CATKIN_DEPENDS roscpp rospy std_msgs
  DEPENDS
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(${PROJECT_NAME}
  src/toy_pkg.cpp
)

## Specify libraries to link a library or executable target against
target_link_libraries(toy_pkg
  ${catkin_LIBRARIES}
)

## Declare a C++ executable
add_executable(toy_pkg_node src/toy_pkg_node.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(toy_pkg_node
  ${catkin_LIBRARIES}
  toy_pkg
)