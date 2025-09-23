//
// Created by kaylor on 9/23/25.
//

#pragma once
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/empty.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "ros2_sport_client.h"
#include "unitree_api/msg/request.hpp"


 class HunterUnitreeRos2: public rclcpp::Node{
 public:
  HunterUnitreeRos2();
 private:
  SportClient sport_client_;
  unitree_api::msg::Request req_;
  rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr standup_sub_;
  rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr standdown_sub_;
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_sub_;
  void StandUpCallback(const std_msgs::msg::Empty::SharedPtr msg);
  void StandDownCallback(const std_msgs::msg::Empty::SharedPtr msg);
  void CmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg);
};
