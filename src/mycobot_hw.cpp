#include <mycobot_moveit/mycobot_hw.h>

MyRobot::MyRobot(): nh_(""), private_nh_("~")
{
  hardware_interface::JointStateHandle state_handle_1("arm1_joint", &pos_[0], &vel_[0], &eff_[0]);
  jnt_state_interface.registerHandle(state_handle_1);
  hardware_interface::JointStateHandle state_handle_2("arm2_joint", &pos_[1], &vel_[1], &eff_[1]);
  jnt_state_interface.registerHandle(state_handle_2);
  hardware_interface::JointStateHandle state_handle_3("arm3_joint", &pos_[2], &vel_[2], &eff_[2]);
  jnt_state_interface.registerHandle(state_handle_3);
  hardware_interface::JointStateHandle state_handle_4("arm4_joint", &pos_[3], &vel_[3], &eff_[3]);
  jnt_state_interface.registerHandle(state_handle_4);
  hardware_interface::JointStateHandle state_handle_5("arm5_joint", &pos_[4], &vel_[4], &eff_[4]);
  jnt_state_interface.registerHandle(state_handle_5);
  hardware_interface::JointStateHandle state_handle_6("arm6_joint", &pos_[5], &vel_[5], &eff_[5]);
  jnt_state_interface.registerHandle(state_handle_6);
  registerInterface(&jnt_state_interface);

  hardware_interface::JointHandle eff_handle_1(jnt_state_interface.getHandle("arm1_joint"), &cmd_[0]);
  jnt_position_interface.registerHandle(eff_handle_1);
  hardware_interface::JointHandle eff_handle_2(jnt_state_interface.getHandle("arm2_joint"), &cmd_[1]);
  jnt_position_interface.registerHandle(eff_handle_2);
  hardware_interface::JointHandle eff_handle_3(jnt_state_interface.getHandle("arm3_joint"), &cmd_[2]);
  jnt_position_interface.registerHandle(eff_handle_3);
  hardware_interface::JointHandle eff_handle_4(jnt_state_interface.getHandle("arm4_joint"), &cmd_[3]);
  jnt_position_interface.registerHandle(eff_handle_4);
  hardware_interface::JointHandle eff_handle_5(jnt_state_interface.getHandle("arm5_joint"), &cmd_[4]);
  jnt_position_interface.registerHandle(eff_handle_5);
  hardware_interface::JointHandle eff_handle_6(jnt_state_interface.getHandle("arm6_joint"), &cmd_[5]);
  jnt_position_interface.registerHandle(eff_handle_6);
  registerInterface(&jnt_position_interface);

  joint_subscriber_ = nh_.subscribe("/joint_states_array", 10, &MyRobot::jointSubscribeCallback, this);
  cmd_publisher_ = nh_.advertise<std_msgs::Float32MultiArray>("/joint_cmd_array", 10);
}

void MyRobot::jointSubscribeCallback(const std_msgs::Float32MultiArray::ConstPtr &msg){
  for(int i=0; i<6; i++){
    pos_[i] = msg->data[i];
  }
}

void MyRobot::read(ros::Time time, ros::Duration period)
{
  for(int i=0; i<6; i++){
    vel_[i] = 0;
    eff_[i] = 0;
  }
}

void MyRobot::write(ros::Time time, ros::Duration period)
{
  std_msgs::Float32MultiArray commands;
  commands.data.resize(6);
  for(int i=0; i<6; i++){
    commands.data[i] = cmd_[i];
  }
  cmd_publisher_.publish(commands);
}