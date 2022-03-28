# Robot arm moveit config

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

### Launching a demo

```shell
roslaunch robot_arm_moveit demo.launch
```

When the demo is launch, you can test each position by moving the end-effector. When a position is selected, you can press the "Plan" button. You will see a simulation of the arm moving to the end-effector position. Then you can press the button "Execute". The "Execute" button will allow the robot to move to the requested postion.

### Launching a demo with RViz and Gazebo (Not working)

```shell
roslaunch robot_arm_moveit demo_gazebo.launch
```

## License

[MIT](https://choosealicense.com/licenses/mit/)
