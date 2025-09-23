#include <rclcpp/rclcpp.hpp>
#include "hunter_unitree_ros2.h"

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node  = std::make_shared<HunterUnitreeRos2>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
