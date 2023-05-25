# tof_plugin_demo

### 概述

tof_plugin_demo为小米机器人cyberdog开源项目，为开发者使用tof_plugin提供示例.

开源地址：https://github.com/MiRoboticsLab
技术文档：https://miroboticslab.github.io/blogs/#/

### docker环境

参考文档：https://miroboticslab.github.io/blogs/#/cn/dockerfile_instructions_cn

### 源码下载

将本项目工程下载到cyberdog_ws目录下

### 功能介绍

#### 1、top_pub#发布tof消息

```
//ros msg、srv接口
#include "protocol/msg/single_tof_payload.hpp"
```

#### 2、tof_sub # 订阅tof消息

```
//ros msg、srv接口
#include "protocol/msg/single_tof_payload.hpp"
#include "protocol/msg/head_tof_payload.hpp"
#include "protocol/msg/rear_tof_payload.hpp"
```


### 编译

```shell
source /opt/ros2/galactic/setup.bash

#第一次编译某个功能包需要使用--packages-up-to,编译该功能包及其依赖包

colcon build --merge-install --packages-up-to tof_plugin_demo

#后续升级单个功能包使用--packages-select，只编译该功能包

colcon build --merge-install --packages-select tof_plugin_demo
```

### 运行

#### 1、拷贝到机器狗上

```
#本地终端cyberdog_ws目录
scp -r install/lib/tof_plugin_demo mi@192.168.55.1:/home/mi
#狗上终端/home/mi目录
cp -rf tof_plugin_demo /opt/ros2/cyberdog/lib
sudo rm -rf tof_plugin_demo

#本地终端cyberdog_ws目录
scp -r install/share/tof_plugin_demo mi@192.168.55.1:/home/mi
#狗上终端/home/mi目录
cp -rf tof_plugin_demo /opt/ros2/cyberdog/share
sudo rm -rf tof_plugin_demo

#本地终端cyberdog_ws目录
scp -r install/include/tof_plugin_demo mi@192.168.55.1:/home/mi
#狗上终端/home/mi目录
cp -rf tof_plugin_demo /opt/ros2/cyberdog/include
sudo rm -rf tof_plugin_demo
```

#### 2、在终端启动功能包

``` 
source /opt/ros2/cyberdog/setup.bash

#运行tof_pub
ros2 run tof_plugin_demo tof_pub --ros-args -r __ns:=/`ros2 node list | grep "mi_" | head -n 1 | cut -f 2 -d "/"

#运行运行tof_sub
ros2 run tof_plugin_demo tof_sub --ros-args -r __ns:=/`ros2 node list | grep "mi_" | head -n 1 | cut -f 2 -d "/"

```

