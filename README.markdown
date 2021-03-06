# Autonomous Shopping cart 

The autonomous shopping cart is a project developed by Alexis Lheritier and Alexandre Massonié. 
The goal of this project is to simulate with ROs and Unity an autonomous shopping cart that can take products on a store shelf.

## Installation

Operating system : Ubuntu 20.04.4 LTS
ROS 1 version : noetic
ROS 1 compiler : catkin

First, you need to install ROS on your Ubuntu system.
Check the [ROS documentation](http://wiki.ros.org/noetic/Installation/Ubuntu) for installing ROS noetic.

[Rviz installation](http://wiki.ros.org/noetic/Installation/Ubuntu):

```bash
sudo apt install ros-noetic-desktop-full
```

[Gazebo installation](https://gazebosim.org/tutorials?tut=ros_installing) :

```bash
sudo apt-get install ros-noetic-gazebo-ros-pkgs ros-noetic-gazebo-ros-control
```

[MoveIt installation](https://moveit.ros.org/install/) :

```bash
sudo apt-get install ros-noetic-moveit
```

[Rosbridge installation](http://wiki.ros.org/rosbridge_suite) :

```bash
sudo apt-get install ros-noetic-rosbridge-server
```

When everything is installed, you need to configure your ROS environment and create your workspace.
Check this [tutorial](http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment) for more information.

When your workspace is created (i.e., catkin_make does not return an error), you need to unzip the archive and move all files in "your_workspace"/src/.

The launch the command :

```bash
catkin_make
```

The catkin compiler will compile all the files.
The dependencies will be created at the same time.

Before launching the different files, you need to :

- Launch roscore :

```bash
roscore
```

Open a new terminal and source your project :

```bash
cd ~/"your_workspace"
source devel/setup.bash
```

In another terminal, write those command

```bash
catkin_make
source devel/setup.bash
```

To test if everything works, you can launch :

```bash
roslaunch robot_arm display.launch
```

You should have these two windows :
![robot_arm_rviz](readme_image/robot_arm_rviz.png)

## Architecture

src/ : Source repositry of the project
src/robot_arm : Robot arm URDF source files (config, meshes, textures and URDF).\
src/robot_arm_gazebo : Robot arm URDF version for gazebo (models, materials and worlds).\
src/robot_arm_moveit_config : Folder generated by MoveIT.\
src/robot_arm_rosbridge : Rosbridge server, website and robot arm interface.\
src/user_interface : User interface for the robot arm.

## Usage

For the use of each part of the project, please refer to the README in each folder.

## License

[MIT](https://choosealicense.com/licenses/mit/)
