//
// Created by kaylor on 9/23/25.
//

#include "hunter_unitree_ros2.h"

HunterUnitreeRos2::HunterUnitreeRos2(): rclcpp::Node("hunter_unitree_ros2_node"), sport_client_(this) {
//  std::string standup_topic = this->declare_parameter<std::string>("standup_topic", "/stand_up");
//  std::string standdown_topic = this->declare_parameter<std::string>("standdown_topic", "/stand_down");
//  std::string cmd_vel_topic = this->declare_parameter<std::string>("cmd_vel_topic", "cmd_vel");
wait_for_standup_ = this->declare_parameter("wait_for_standup", 5);
standup_sub_ = this->create_subscription<std_msgs::msg::Empty>(
    "/stand_up", 1,
    std::bind(&HunterUnitreeRos2::StandUpCallback, this,
              std::placeholders::_1));
standdown_sub_ = this->create_subscription<std_msgs::msg::Empty>(
    "/stand_down", 1,
    std::bind(&HunterUnitreeRos2::StandDownCallback, this,
              std::placeholders::_1));
standup_and_unlock_sub_ = this->create_subscription<std_msgs::msg::Empty>(
    "/stand_up_and_unlock", 1,
    std::bind(&HunterUnitreeRos2::StandUpAndUnlockCallback, this,
              std::placeholders::_1));
cmd_vel_sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
    "cmd_vel", 1,
    std::bind(&HunterUnitreeRos2::CmdVelCallback, this, std::placeholders::_1));
RCLCPP_INFO(this->get_logger(), "HunterUnitreeRos2 initialized");
}


void HunterUnitreeRos2::StandUpCallback(const std_msgs::msg::Empty::SharedPtr msg) {
  RCLCPP_INFO(this->get_logger(), "Unitree robot stands up");
  sport_client_.StandUp(req_);
  sport_client_.BalanceStand(req_);
}

void HunterUnitreeRos2::StandUpAndUnlockCallback(
    const std_msgs::msg::Empty::SharedPtr msg) {
  RCLCPP_INFO(this->get_logger(), "Unitree robot stands up, delay %ds",
              wait_for_standup_);
  sport_client_.StandUp(req_);
  std::this_thread::sleep_for(std::chrono::seconds(wait_for_standup_));
  RCLCPP_INFO(this->get_logger(), "Unlock all the motors");
  sport_client_.BalanceStand(req_);
}

void HunterUnitreeRos2::StandDownCallback(const std_msgs::msg::Empty::SharedPtr msg) {
  RCLCPP_INFO(this->get_logger(), "Unitree robot stands down");
  sport_client_.StandDown(req_);
}

void HunterUnitreeRos2::CmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg) {
  RCLCPP_DEBUG(this->get_logger(),
               "Unitree ros2 driver received velocity command, x = %.2f, y = %.2f, yaw = %0.4f",
               msg->linear.x,
               msg->linear.y,
               msg->angular.z);
  sport_client_.Move(req_, msg->linear.x, msg->linear.y, msg->angular.z);
}
