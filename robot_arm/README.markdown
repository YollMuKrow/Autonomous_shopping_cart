# Robot arm

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

### Launching RViz

```shell
roslaunch robot_arm display.launch
```

Potential error :

- Rviz can crash at the start : Close and relaunch roscore or restart Ubuntu.

## License

[MIT](https://choosealicense.com/licenses/mit/)
