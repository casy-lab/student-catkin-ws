/* TOY PKG                                     */
/* Author: Lorenzo Gentilini                   */
/* E-Mail: lorenzo.gentilini6@unibo.it         */
/* Date: March 2021                            */
/* File: toy_pkg_node.cpp                      */

#include <toy_pkg/toy_pkg.hpp>

int main(int argc, char **argv){
  ros::init(argc, argv, "toy_pkg_node");
  ros::NodeHandle nh("~");

  TOY toyobj(nh);
  ros::spin();

  return 0;
}