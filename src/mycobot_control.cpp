#include <ros/ros.h>
#include <mycobot_moveit/mycobot_hw.h>
#include <controller_manager/controller_manager.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "mycobot_control");

	MyRobot robot;
	controller_manager::ControllerManager cm(&robot);

	ros::AsyncSpinner spinner(1);
	spinner.start();

	ros::Time prev_time = ros::Time::now();
	ros::Rate rate(10.0); // 10 Hz rate

	while (ros::ok())
	{
		const ros::Time time = ros::Time::now();
		const ros::Duration period = time - prev_time;

		robot.read(time, period);
		cm.update(time, period);
		robot.write(time, period);

		rate.sleep();
	}
	return 0;
}