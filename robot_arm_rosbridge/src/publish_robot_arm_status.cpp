#include "ros/ros.h"
#include "std_msgs/String.h"
#include "actionlib_msgs/GoalStatusArray.h"
#include "moveit_msgs/ExecuteTrajectoryActionFeedback.h"
#include "moveit_msgs/MoveGroupActionFeedback.h"

#include <sstream>

std_msgs::String feedback_moveit_str;
std_msgs::String feedback_robot_str;

/**
 * @brief get feedback from the trajectory. IDLE or MONITOR
 * IDLE -> The robot arm is waiting an instruction.
 * MONITOR -> The robot arm is moving to the position sent to moveit.
 * 
 * @param feedback_status execute_trajectory/feedback topic type
 */
void robotFeedbackCallback(const moveit_msgs::ExecuteTrajectoryActionFeedbackConstPtr feedback_status)
{
    ROS_INFO("Robat arm is in [%s] state !", feedback_status->feedback.state.c_str());
    feedback_robot_str.data = feedback_status->feedback.state.c_str();

}

/**
 * @brief get feedback from the move_group action. IDLE or PLANNING
 * IDLE -> MoveIT is waiting a position or a motion plan was computed succesfully.
 * PLANNING -> MoveIT is planning a list of joint position to the robot arm.
 * 
 * @param feedback_status move_group/feedback topic type
 */
void moveGroupFeedbackCallback(const moveit_msgs::ExecuteTrajectoryActionFeedbackConstPtr feedback_status)
{
    ROS_INFO("Hey, MoveIT is in [%s] state !", feedback_status->feedback.state.c_str());

    feedback_moveit_str.data = feedback_status->feedback.state.c_str();
}

//-----------------------------------------------------------------------------------


int main(int argc, char **argv)
{
    ros::init(argc, argv, "talker");
    ros::NodeHandle n;
    ros::Publisher moveit_arm_status_pub = n.advertise<std_msgs::String>("moveit_status", 10);
    ros::Publisher robot_arm_status_pub = n.advertise<std_msgs::String>("robot_status", 10);
    ros::Rate loop_rate(10);

    std_msgs::String no_data_str;
    no_data_str.data = "No data available !";

    // MoveIT initialization 


    ros::Subscriber sub_moveit_feedback = n.subscribe("move_group/feedback", 10, moveGroupFeedbackCallback);
    ROS_INFO("Listening move_group feedback : move_group/feedback");
    ros::Subscriber sub_robot_feedback = n.subscribe("execute_trajectory/feedback", 10, robotFeedbackCallback);
    ROS_INFO("Listening robot trajectory feedback : execute_trajectory/status");

    while (ros::ok())
    {
        
        if (feedback_moveit_str.data != ""){
            ROS_INFO("%s", feedback_moveit_str.data.c_str());
            moveit_arm_status_pub.publish(feedback_moveit_str);
        }

        else{
            ROS_INFO("%s", no_data_str.data.c_str()); 
            moveit_arm_status_pub.publish(no_data_str);
        } 

        if (feedback_robot_str.data != ""){
            ROS_INFO("%s", feedback_robot_str.data.c_str());
            robot_arm_status_pub.publish(feedback_robot_str);
        }

        else{
            ROS_INFO("%s", no_data_str.data.c_str()); 
            robot_arm_status_pub.publish(no_data_str);
        } 

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}