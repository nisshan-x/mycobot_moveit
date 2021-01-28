# mycobot_moveit
Unofficial myCobot moveit repositiry

# Environment
| item |  |
|---|---|
| OS | Ubuntu 18.04 |
| ROS | melodic |
| Arm Robot | myCobot |

# Preparation
1. Install pymycobot. See how to install it. https://github.com/elephantrobotics/pymycobot(Atom v2.4, pymycobot==2.1.2)

2. Build ROS packages. mycobot_moveit needs [Tiryoh](https://github.com/Tiryoh/mycobot_ros)'s repository (Thank you!).
```
cd catkin_ws/src
git clone https://github.com/Tiryoh/mycobot_ros
git clone https://github.com/nisshan-x/mycobot_moveit
rosdep update
rosdep install -i --from-paths mycobot_moveit
catkin_make
```

# Usage
Connect myCobot and PC with USB-C cable, and launch:

`roslaunch mycobot_moveit mycobot_moveit_control.launch`

Note: Don't forget to provide power via AC adaptor to myCobot.

# License
This software is released under the MIT License, see LICENSE.txt.