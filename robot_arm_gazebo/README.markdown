# Robot arm gazebo

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

### Launching Gazebo alone

```shell
Gazebo
```

### Launching an empty world

```shell
roslaunch robot_arm_gazebo empty_world.launch
```

### Spawn a robot arm (when an empty world is already running)

```shell
roslaunch robot_arm_gazebo robot_arm_spawn.launch
```

Be carefull : For multiple spawn, you need to modify the position argument and the model argument with a different value in the /launch/robot_arm_spawn.launch file.

### Launching a world with a robot arm and different object

```shell
roslaunch robot_arm_gazebo robot_arm.launch
```

Potential error :

- Gazebo can crash at the start : Close and relaunch roscore or restart Ubuntu.

## License

[MIT](https://choosealicense.com/licenses/mit/)
