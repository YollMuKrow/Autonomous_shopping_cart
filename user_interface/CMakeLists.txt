cmake_minimum_required(VERSION 3.0.2)
project(user_interface)

find_package(catkin REQUIRED
    COMPONENTS
    roscpp 
    rospy 
    std_msgs
    sensor_msgs
    message_runtime
    moveit_core
    moveit_msgs 
    moveit_ros_planning  
    moveit_ros_planning_interface 
    moveit_ros_move_group 
)

catkin_package(
    CATKIN_DEPENDS 
    roscpp 
    rospy 
    message_runtime 
    std_msgs
    sensor_msgs
    moveit_core    
    moveit_msgs 
    moveit_ros_planning  
    moveit_ros_planning_interface 
    moveit_ros_move_group 
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(send_position_to_moveit src/send_position_to_moveit.cpp)
target_link_libraries(send_position_to_moveit ${catkin_LIBRARIES})

add_executable(get_joints_states src/get_joints_states.cpp)
target_link_libraries(get_joints_states ${catkin_LIBRARIES})

add_executable(get_trajectory_status src/get_trajectory_status.cpp)
target_link_libraries(get_trajectory_status ${catkin_LIBRARIES})
