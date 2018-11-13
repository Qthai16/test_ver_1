#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>


std_msgs::Float32 vel,ang;
ros::Publisher sent_vel_linear;
ros::Publisher sent_vel_ang ;
int flag;

void my_callback(const geometry_msgs::Twist::ConstPtr & msg );

int main(int argc, char **argv)
{
    /* code */
    ros::init(argc,argv,"my_cmd_vel");
    ros::NodeHandle nh_re,nh_tra_linear;
    ros::NodeHandle nh_tra_ang;
    sent_vel_linear = nh_tra_linear.advertise<std_msgs::Float32>("/sudo_speed",1);
    sent_vel_ang = nh_tra_ang.advertise<std_msgs::Float32>("/sudo_steerAngle",1);
    ros::Subscriber get_cmd = nh_re.subscribe("/cmd_vel",100, my_callback);
    ros::spin();
    return 0;
}

void my_callback(const geometry_msgs::Twist::ConstPtr &msg )
{
    vel.data = msg->linear.x * 60;
    ang.data = 0-(msg->angular.z * 50);
    ROS_INFO("ahihi");
    sent_vel_linear.publish(vel);
    sent_vel_ang.publish(ang);
    // flag = 1;
}
