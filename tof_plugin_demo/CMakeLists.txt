cmake_minimum_required(VERSION 3.8)
project(tof_plugin_demo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -g)
endif()

link_directories(/opt/ros2/galactic/lib)
link_directories(/opt/ros2/cyberdog/lib)
# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_index_cpp REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(params REQUIRED)
find_package(pluginlib REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(protocol REQUIRED)
find_package(cyberdog_common REQUIRED)
find_package(cyberdog_embed_protocol REQUIRED)
find_package(cyberdog_system REQUIRED)
find_package(cyberdog_tof REQUIRED)

set(dependencies
  rclcpp
  rclcpp_components
  std_srvs
  std_msgs
  ament_index_cpp
  protocol
  cyberdog_system
  pluginlib
  cyberdog_tof
)

include_directories(include)

add_executable(tof_pub
  src/tof_pub.cpp)

ament_target_dependencies(tof_pub
  rclcpp
  std_srvs
  std_msgs
  protocol
  ament_index_cpp
  cyberdog_system
  pluginlib
  cyberdog_tof
)

target_link_libraries(tof_pub
  ${cyberdog_log_LIBRARIES}
)

add_executable(tof_sub
  src/tof_sub.cpp)

ament_target_dependencies(tof_sub
  rclcpp
  std_srvs
  std_msgs
  protocol
  ament_index_cpp
  cyberdog_system
  pluginlib
  cyberdog_tof
)

target_link_libraries(tof_sub
  ${cyberdog_log_LIBRARIES}
)

install(TARGETS
  tof_pub
  tof_sub
  DESTINATION lib/${PROJECT_NAME})



if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# ament_export_lib
ament_export_include_directories(include)
ament_export_dependencies(${dependencies})
ament_package()
