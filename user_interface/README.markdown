# User interface

This project is the second part of the autonomous cart project.

## Usage

### Initialization

Check if roscore is launched

```shell
roscore
```

Compile and source your workspace

```shell
cd ~/"your_workspace"
catkin_make
source devel/setup.bash
```

### Launching the user interface

Launch the Moveit demo ("your_workspace"/src/robot_arm_moveit/)

```shell
roslaunch robot_arm_moveit_config demo.launch
```

Run each .cpp you want :
get_joints_states -> Subscribe to the /joint_state node a print the position(in radian) of each joint.

```shell
rosrun user_interface get_joints_states.cpp
```

get_trajectory_status -> Subscribe to the /execute_trajectory/feedback node and the move_group/feedback node and print the status of MoveIt and the robot.

```shell
rosrun user_interface get_trajectory_status.cpp
```

send_position_to_moveit -> Allow the user to send a position (in meter for the position and radian for the orientation) to moveit. MoveIt will compute a trajectory path and will make the robot move to the requested position.
Exemple of position that work : w = 0, x = 1(or -0.5), y = 0 and z = 0.

```shell
rosrun user_interface send_position_to_moveit.cpp
```

You can see in RViz, a simulation of the robot arm move to the requested point.

## License

[MIT](https://choosealicense.com/licenses/mit/)
