#include "ros/ros.h"
#include <std_msgs/Float32.h>
#include <iostream>

void number_callback(const std_msgs::Float32::ConstPtr& msg) {
    if(msg->data == 1)
    {
        ROS_INFO("re trai");
    }
    else if(msg->data == 0)
    {
        ROS_INFO("re phai");
    }
}

int main(int argc, char **argv) { 
    ros::init(argc, argv,"sub_sign");
    ros::NodeHandle node_obj;
    ros::Subscriber number_subscriber = node_obj.subscribe("/sign",10,number_callback);
    ros::spin();
    return 0;
}