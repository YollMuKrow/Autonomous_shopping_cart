/**
 * @author Alexis Lheritier 
 * @date 23/03/2022
 * @todo Add movement constraint -> plugins OMPL constraint planning /!\ planning algorithm issues
 * @todo Add websockets management (ROSBridge + Unity)
 */

#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>


/**
 * @brief Class of the moveit group planning interface
 * 
 * @attention End effector position and rotation are defined depending the absolute 
 *            position of the robot. The absolute position is situated at the bottom 
 *            left corner of the base (In front view). Check documentation or 
 *            SolidWorks assemblage for more information.
 */
class Moveit_position_interface{
    public : 
        //Constructor
        Moveit_position_interface(const std::string &group_name){
            move_group_ptr = new moveit::planning_interface::MoveGroupInterface(group_name);
        }

        //Destructor
        ~Moveit_position_interface(){
            delete move_group_ptr;
        }

        //variable
        moveit::planning_interface::MoveGroupInterface *move_group_ptr;
        moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
        float orientation_w = 0.0;
        float position_x = 0.0;
        float position_y = 0.0;
        float position_z = 1.0;

};

void set_movement_constraint(){

}

/**
 * @brief Set the end effector position and orientation from the stanpoint of the end effector
 *  
 * @param orientation_w -> quaternion in w from the perspective of the end effector  
 * @param position_x -> position in x from the perspective of the end effector  
 * @param position_y -> position in x from the perspective of the end effector  
 * @param position_z -> position in x from the perspective of the end effector  
 */
void set_end_effector_position(Moveit_position_interface *move_group){
    geometry_msgs::Pose target_pose;
    target_pose.orientation.w = move_group->orientation_w;
    target_pose.position.x = move_group->position_x;
    target_pose.position.y = move_group->position_y;
    target_pose.position.z = move_group->position_z;
    move_group->move_group_ptr->setPoseTarget(target_pose);
}

/**
 * @brief Check if the position and rotation is valid and planned it
 * 
 * @return true -> a planning sequence is found
 * @return false -> no planning sequence found
 */
bool plan_sequence(Moveit_position_interface* move_group){
    moveit::planning_interface::MoveGroupInterface::Plan my_plan; // MoveIT compute a valid plan.
    return (move_group->move_group_ptr->plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
}

/**
 * @brief order to a group to move accordingly to the joint position set by the planning sequence
 * 
 * @param move_group one of the move_group to move
 */
void move_to_position(Moveit_position_interface* move_group){
    ROS_INFO("Position valid. Robot is in motion !");
    move_group->move_group_ptr->move();
    ROS_INFO("The robot has reached the desired position !");
}

/**
 * @brief Check if a string is in a float format
 * 
 * @param float_number String to check
 * @return true String is in a float format
 * @return false  String is not in a float format
 */
bool is_string_a_float(std::string float_number){
    std::string::const_iterator iterator = float_number.begin();
    int dot = 0;
    if(*iterator == '-'){
        ++iterator;
    }

    while(iterator != float_number.end()){
        if(*iterator == '.')
            dot++;
        if(!std::isdigit(*iterator) && *iterator != '.' || 
            dot > 1 || *(float_number.begin()) == '.' || 
            (*iterator == '.' && float_number.size() < 2) || 
            (*(float_number.begin()) == '-' && *(float_number.begin()+1) == '.')) 
        {
            std::cerr << "VALUE ERROR : " << float_number << " is not a float" << std::endl;
            return false;
        }
        ++iterator;
    }
    return true;
}

/**
 * @brief Get the float value of a string object 
 * 
 * @param type which data (orientation or position)
 * @return float value of a string
 */
float get_value(std::string type){
    std::cout << type;
    std::string tmp = "";
    std::cin >> tmp;
    while(!is_string_a_float(tmp)){
        std::cout << type;
        std::cin >> tmp;
    }
    return std::stof(tmp.c_str());
}

/**
 * @brief Allows the user to send a position to the robot
 * 
 * @param moveit_position_interface pointer to the moveit class
 */
void position_sent_by_user(Moveit_position_interface *moveit_position_interface){
    moveit_position_interface->orientation_w = get_value("orientation w = ");
    moveit_position_interface->position_x = get_value("position x = ");
    moveit_position_interface->position_y = get_value("position y = ");
    moveit_position_interface->position_z = get_value("position z = ");
    ROS_INFO("The desired position is being calculated  !");
}

int main(int argc, char *argv[])
{
    //ROS initialization
    ros::init(argc, argv, "send_position_to_moveit");
    ros::NodeHandle node_handle;
    ros::AsyncSpinner spinner(1);
    spinner.start(); //asynchronous loop

    static const std::string PLANNING_GROUP_ARM = "arm";
    static const std::string PLANNING_GROUP_HAND = "hand";

    //construction of each move_group 
    Moveit_position_interface move_group_hand(PLANNING_GROUP_HAND);
    Moveit_position_interface move_group_arm(PLANNING_GROUP_ARM);

    // Setting a pointer to the class of each group
    Moveit_position_interface *move_group_hand_ptr;
    Moveit_position_interface *move_group_arm_ptr;
    move_group_arm_ptr = &move_group_arm;
    move_group_hand_ptr = &move_group_hand;

    // Setting speed value of each group ]0.0;1.0]
    // Default value = 0.1
    move_group_arm_ptr->move_group_ptr->setMaxVelocityScalingFactor(1.0);  
    move_group_hand_ptr->move_group_ptr->setMaxVelocityScalingFactor(1.0);

    position_sent_by_user(move_group_arm_ptr);

    set_end_effector_position(move_group_arm_ptr);

    bool plan_status = plan_sequence(move_group_arm_ptr);

    if(plan_status)
        move_to_position(move_group_arm_ptr);
    else
        std::cerr << "ERROR planning sequence invalid !" << std::endl;
    return 0;
}
