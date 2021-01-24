#include <ros/ros.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/robot_hw.h>
#include <map>
#include <string>
#include <vector>
#include <std_msgs/Float32MultiArray.h>


class MyRobot : public hardware_interface::RobotHW
{
public:
    MyRobot();
//    bool init(ros::NodeHandle &root_nh, ros::NodeHandle &robot_hw_nh);

    ros::Time getTime() const { return ros::Time::now(); }
    ros::Duration getPeriod() const { return ros::Duration(0.01); }

    void read(ros::Time, ros::Duration);
    void write(ros::Time, ros::Duration);

private:
  ros::NodeHandle nh_;
  ros::NodeHandle private_nh_;
  ros::Publisher cmd_publisher_;
  ros::Subscriber joint_subscriber_;
  // hardware_interface::JointStateInterface gives read access to all joint values
  // without conflicting with other controllers.
    hardware_interface::JointStateInterface jnt_state_interface;
  // hardware_interface::PositionJointInterface inherits from
  // hardware_interface::JointCommandInterface and is used for reading and writing
  // joint positions. Because this interface reserves the joints for write access,
  // conflicts with other controllers writing to the same joints might occure.
  // To only read joint positions, avoid conflicts using
  // hardware_interface::JointStateInterface.
  // hardware_interface::PositionJointInterface jnt_pos_interface;
    hardware_interface::PositionJointInterface jnt_position_interface;

  // Data member array to store the controller commands which are sent to the
  // robot's resources (joints, actuators)
    double cmd_[6];

  // Data member arrays to store the state of the robot's resources (joints, sensors)
    double pos_[6] = {};
    double vel_[6] = {};
    double eff_[6] = {};

  void jointSubscribeCallback(const std_msgs::Float32MultiArray::ConstPtr &msg);
};