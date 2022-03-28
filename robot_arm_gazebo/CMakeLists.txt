cmake_minimum_required(VERSION 3.0.2)
project(robot_arm_gazebo)

find_package(catkin REQUIRED COMPONENTS
  gazebo_ros
)

find_package(gazebo REQUIRED)

catkin_package(
  DEPENDS
    gazebo_ros
)

if(CATKIN_ENABLE_TESTING)
  find_package(roslaunch REQUIRED)
  roslaunch_add_file_check(launch)
endif()

install(DIRECTORY worlds plugins models materials launch
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

