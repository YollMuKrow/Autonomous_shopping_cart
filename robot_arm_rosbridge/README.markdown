# Robot arm rosbridge

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

### Launching Rosbridge

```shell
roslaunch robot_arm_rosbridge websockets.launch
```

Then, launch the web_interface.html in you web browser.

When you see the connection status "Connected" then you can continue to the next part.
Otherwise, you can press F5 on you web browser or relaunch websockets.launch and check if a client is connected to the websockets.

If everything is fine, we will test if the communication is open with :

```shell
rostopic pub /txt_msg std_msgs/String "data: 'Hello rosbridge'" -1
```

If the communication is received by the websockets, your message will appear in the testing listener span.

### Rosbridge and RViz

Now, we will link RViz and Rosbridge.

Launch web_interface.html in your browser.
Launch Rosbridge :

```shell
roslaunch robot_arm_rosbridge websockets.launch
```

Launch publish_robot_arm_status.cpp

```shell
rosrun robot_arm_rosbridge publish_robot_arm_status.cpp
```

If it's working, you will see "no data available !" in your browser.

And finally, you can launch the Moveit demo ("your_workspace"/src/robot_arm_moveit/)

```shell
roslaunch robot_arm_moveit_config demo.launch
```

If it's working, you will see the MoveIT status and Robot status when you press plan or execute change.

## License

[MIT](https://choosealicense.com/licenses/mit/)
