// Copyright (c) 2023-2023 Beijing Xiaomi Mobile Software Co., Ltd. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef TOF_SUB_HPP_
#define TOF_SUB_HPP_
#include <chrono>
#include <string>
#include <memory>
#include <utility>
#include "rclcpp/rclcpp.hpp"
#include "protocol/msg/single_tof_payload.hpp"
#include "protocol/msg/head_tof_payload.hpp"
#include "protocol/msg/rear_tof_payload.hpp"
class TofSub : public rclcpp::Node
{
public:
  TofSub()
  : Node("TofSub")
  {
    name_ = "TofSub";
    count_ = 0;
    count1_ = 0;
    count2_ = 0;
    // subcribe self tof
    tof_ = 
    this->create_subscription<protocol::msg::SingleTofPayload>(
      "tof", 5,
      std::bind(&TofSub::TofCallback, this,std::placeholders::_1));

    // subcribe head_tof_payload
    head_tof_ = 
    this->create_subscription<protocol::msg::HeadTofPayload>(
      "head_tof_payload", 5,
      std::bind(&TofSub::HeadTofCallback, this,std::placeholders::_1));

    // subcribe rear_tof_payload
    rear_tof_ = 
    this->create_subscription<protocol::msg::RearTofPayload>(
      "rear_tof_payload", 5,
      std::bind(&TofSub::RearTofCallback, this,std::placeholders::_1));
  }

private:
  int CheckShutDown(int count)
  {
    if(count >= 10) {
      RCLCPP_INFO(this->get_logger(), "shutdown scribe");
      // shutdown;
      rclcpp::shutdown();
    }
  }

  void TofCallback(const protocol::msg::SingleTofPayload::SharedPtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "get tof msg");
    count_++;
    CheckShutDown(count_);
  }

  void HeadTofCallback(const protocol::msg::HeadTofPayload::SharedPtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "get head tof msg");
    count1_++;
    CheckShutDown(count1_);
  }

  void RearTofCallback(const protocol::msg::RearTofPayload::SharedPtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "get rear tof msg");
    count2_++;
    CheckShutDown(count2_);
  }

  rclcpp::CallbackGroup::SharedPtr group_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Subscription<protocol::msg::SingleTofPayload>::SharedPtr tof_ {nullptr};
  rclcpp::Subscription<protocol::msg::HeadTofPayload>::SharedPtr head_tof_ {nullptr};
  rclcpp::Subscription<protocol::msg::RearTofPayload>::SharedPtr rear_tof_ {nullptr};
  std::string name_;
  int count_;
  int count1_;
  int count2_;
};

#endif  // TOF_SUB_HPP_
