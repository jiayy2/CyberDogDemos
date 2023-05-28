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
#ifndef TOF_PUB_HPP_
#define TOF_PUB_HPP_

#include <chrono>
#include <string>
#include <memory>
#include <utility>
#include "rclcpp/rclcpp.hpp"
#include "pluginlib/class_loader.hpp"
#include "tof_base/tof_base.hpp"
#include "protocol/msg/single_tof_payload.hpp"

using namespace cyberdog;
using namespace cyberdog::sensor;
class TofPub : public rclcpp::Node
{
public:
  TofPub()
  : Node("TofPub")
  {
    name_ = "TofPub";
    count_ = 0;
    class_loader_ = std::make_shared<pluginlib::ClassLoader<cyberdog::sensor::TofBase>>("cyberdog_tof", "cyberdog::sensor::TofBase");
    tof_pub_ = this->create_publisher<protocol::msg::SingleTofPayload>(
    "tof", rclcpp::SystemDefaultsQoS());

    tof_ = class_loader_->createSharedInstance("cyberdog::sensor::TofCarpo");

    tof_->SetSinglePayloadCallback(
    std::bind(
      &TofPub::SingleTofPayloadCallback, this,
      std::placeholders::_1));
    // init
    tof_->Init(false);
    // open
    tof_->Open();
    // start tof
    tof_->Start();
  }

private:

  void SingleTofPayloadCallback(std::shared_ptr<protocol::msg::SingleTofPayload> msg)
  {
    count_++;
    if((count_ % 40) == 0)
    {
      RCLCPP_INFO(this->get_logger(), "get msg frame:[%s]",msg->header.frame_id.c_str());
    }

    tof_pub_->publish(*msg);
    
    // if(count_ >= 20) {
    //   // stop tof
    //   RCLCPP_INFO(this->get_logger(), "stop tof");
    //   // tof_->Stop();
    //   // shutdown;
    //   rclcpp::shutdown();
    // }
  }

  rclcpp::CallbackGroup::SharedPtr group_;
  std::shared_ptr<pluginlib::ClassLoader<cyberdog::sensor::TofBase>> class_loader_;
  
  std::shared_ptr<cyberdog::sensor::TofBase> tof_;
  rclcpp::Publisher<protocol::msg::SingleTofPayload>::SharedPtr tof_pub_;
  std::string name_;
  int count_;
};

#endif  // TOF_PUB_HPP_
