/**
 * @author Alexis Lheritier 
 * @date 23/03/2022
 */

#include "ros/ros.h"

#include "sensor_msgs/JointState.h"
void jointStateCallback(const sensor_msgs::JointStateConstPtr joint)
{

  ROS_INFO("-------------------------------------------");
  int number_joint = joint->name.size();
  for(int i = 0; i < number_joint; i++){

    ROS_INFO("-------");
    ROS_INFO("Listening joint number [%d]", i);
    ROS_INFO("Joint name [%s]", joint->name[i].c_str());
    ROS_INFO("Joint position(radian) [%f]", joint->position[i]);
    if(joint->effort.size() > i)
      ROS_INFO("Joint effort [%f]", joint->effort[i]);
    if(joint->velocity.size() > i)
      ROS_INFO("Joint velocity [%f]", joint->velocity[i]);
  }
  
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "joint_states_listener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("joint_states", 1000, jointStateCallback);

  ROS_INFO("Listener subscribe to /joint_states");
  ros::spin();

  return 0;
}
