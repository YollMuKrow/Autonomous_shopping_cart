/**
 * @author Alexis Lheritier 
 * @date 23/03/2022
 */

#include "ros/ros.h"
#include "actionlib_msgs/GoalStatusArray.h"
#include "moveit_msgs/ExecuteTrajectoryActionFeedback.h"
#include "moveit_msgs/MoveGroupActionFeedback.h"

/**
 * @brief get feedback from the trajectory. IDLE or MONITOR
 * IDLE -> The robot arm is waiting an instruction.
 * MONITOR -> The robot arm is moving to the position sent to moveit.
 * 
 * @param feedback_status execute_trajectory/feedback topic type
 */
void trajectoryFeedbackCallback(const moveit_msgs::ExecuteTrajectoryActionFeedbackConstPtr& feedback_trajectory)
{
  ROS_INFO("Robat arm is in [%s] state !", feedback_trajectory->feedback.state.c_str());
}

/**
 * @brief get feedback from the move_group action. IDLE or PLANNING
 * IDLE -> MoveIT is waiting a position or a motion plan was computed succesfully.
 * PLANNING -> MoveIT is planning a list of joint position to the robot arm.
 * 
 * @param feedback_status move_group/feedback topic type
 */
void moveGroupFeedbackCallback(const moveit_msgs::MoveGroupActionFeedbackConstPtr& feedback_status)
{
  ROS_INFO("MoveIT is in [%s] state !", feedback_status->feedback.state.c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "status_listener");

  ros::NodeHandle n;

  ros::Subscriber sub_trajectory_feedback = n.subscribe("execute_trajectory/feedback", 10, trajectoryFeedbackCallback);
  ROS_INFO("Listening trajectory feedback : execute_trajectory/status");
  ros::Subscriber sub_move_group_feedback = n.subscribe("move_group/feedback", 10, moveGroupFeedbackCallback);
  ROS_INFO("Listening move_group feedback : move_group/feedback");
  
  ros::spin();

  return 0;
}
