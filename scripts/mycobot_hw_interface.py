#!/usr/bin/env python2
import subprocess
import rospy

from std_msgs.msg import Float32MultiArray
from pymycobot.mycobot import MyCobot

class MycobotHwInterface:
    def __init__(self):
        port = subprocess.check_output(['echo -n /dev/ttyUSB*'], shell=True)
        self.mycobot_ = MyCobot(port)
        self.mycobot_.power_on()

        rospy.init_node('mycobot_hw_interface', anonymous=True)
        self.joint_state_msg_pub_ = rospy.Publisher('joint_states_array', Float32MultiArray, queue_size=10)
        self.joint_cmd_sub = rospy.Subscriber("joint_cmd_array", Float32MultiArray, self.jointCommandCallback)

        self.rate_ = rospy.Rate(10) # 10hz

        self.joint_state_array_ = []
        JOINT_NUMBER = 6
        for tmp in range(JOINT_NUMBER):  # initialize array
            tmp = 0.0
            self.joint_state_array_.append(tmp)
        self.pre_data_list = []
        self.first_flag = True

    def main_loop(self):
        while not rospy.is_shutdown():
            self.joint_state_msg_sender()
            self.rate_.sleep()

    def joint_state_msg_sender(self):
        angles = self.mycobot_.get_radians()
        for index, value in enumerate(angles):
            if index != 2:
                value *= -1
            self.joint_state_array_[index] = value
        # str = "angles: %s" % angles
        # rospy.loginfo(str)

        joint_state_msg = Float32MultiArray(data=self.joint_state_array_)
        self.joint_state_msg_pub_.publish(joint_state_msg)

    def jointCommandCallback(self, msg):
        data_list = []
        for index, value in enumerate(msg.data):
            if index != 2:
                value *= -1
            data_list.append(value)

        if self.first_flag:
            for value in data_list:
                self.pre_data_list.append(value)
            self.first_flag = False

        if self.pre_data_list != data_list:
            # print type(data.position[0])
            rospy.loginfo(rospy.get_caller_id() + "%s", msg.data)
            self.mycobot_.send_radians(data_list, 80)
            self.pre_data_list = []
            for value in data_list:
                self.pre_data_list.append(value)

if __name__ == '__main__':
    try:
        mc_hw_if = MycobotHwInterface()
        mc_hw_if.main_loop()
    except rospy.ROSInterruptException:
        pass

