#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>
#include <stdio.h>

void my_callback(const geometry_msgs::Twist::ConstPtr & msg );

int main(int argc, char **argv)
{
    /* code */
    ros::init(argc,argv,"cmd_vel");
    ros::NodeHandle nh;
    std_msgs::Float32 sign_msg;
    
    ros::Publisher cmd_sign_pub = nh.advertise<std_msgs::Float32>("sign",100);
    
    while (ros::ok())
    {
        int c = getchar();   // call your non-blocking input function
        if (c == 't')
        {
            sign_msg.data=1;
            cmd_sign_pub.publish(sign_msg);
        }
        else if (c == 'p')
        {
            sign_msg.data=0;
            cmd_sign_pub.publish(sign_msg);
        }
        else if (c == 'g')
        {
            sign_msg.data=2;
            cmd_sign_pub.publish(sign_msg);            
        }
    }
    ros::spin();
    return 0;
}
