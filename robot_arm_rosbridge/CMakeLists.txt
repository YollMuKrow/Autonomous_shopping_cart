cmake_minimum_required(VERSION 3.0.2)
project(robot_arm_rosbridge)

find_package(catkin REQUIRED COMPONENTS
  rosbridge_server
  roscpp 
  rospy 
  std_msgs
  sensor_msgs
  message_runtime
  moveit_msgs
)

catkin_package(
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(publish_robot_arm_status src/publish_robot_arm_status.cpp)
target_link_libraries(publish_robot_arm_status ${catkin_LIBRARIES})

