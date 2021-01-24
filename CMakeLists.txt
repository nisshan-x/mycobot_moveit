cmake_minimum_required(VERSION 3.1.3)
project(mycobot_moveit)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  tf
  moveit_ros_planning_interface
  hardware_interface
  transmission_interface
  controller_manager
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp hardware_interface transmission_interface controller_manager
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(mycobot_moveit_commander src/mycobot_moveit_commander.cpp)
add_dependencies(mycobot_moveit_commander ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(mycobot_moveit_commander
  ${catkin_LIBRARIES}
)

add_executable(mycobot_control src/mycobot_control.cpp src/mycobot_hw.cpp)
add_dependencies(mycobot_control ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(mycobot_control
  ${catkin_LIBRARIES}
)

install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  PATTERN "setup_assistant.launch" EXCLUDE)
install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

catkin_install_python(PROGRAMS
  scripts/mycobot_hw_interface.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)