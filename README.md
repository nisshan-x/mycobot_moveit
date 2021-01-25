# mycobot_moveit
Unofficial myCobot moveit repositiry

# Environment
Ubuntu:18.04
ROS:melodic

# Preparation
1. Install pymycobot. See how to install it. https://github.com/elephantrobotics/pymycobot
1. Install moveit.
`sudo apt install ros-melodic-moveit`
If you have some errors when running moveit, try the following command: ```sudo apt install ros-melodic-ros-control ros-melodic-ros-controllers ros-melodic-joint-state-controller ros-melodic-effort-controllers ros-melodic-position-controllers```

1. Build ros packages. mycobot_moveit needs [Tiryoh](https://github.com/Tiryoh/mycobot_ros)'s repository (Thank you!).
```
cd catkin_ws/src
git clone https://github.com/Tiryoh/mycobot_ros
git clone https://github.com/nisshan-x/mycobot_moveit
rosdep update
catkin_make
```

# Usage
Connect myCobot and PC with USB-C cable, and
`roslaunch mycobot_moveit mycobot_moveit_control.launch`

Note: Don't forget to provide power via AC adaptor to myCobot.

# License
This software is released under the MIT License, see LICENSE.txt.
