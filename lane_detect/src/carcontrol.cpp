#include "carcontrol.h"

CarControl::CarControl()
{
    carPos.x = 120;
    carPos.y = 300;
    steer_publisher = node_obj1.advertise<std_msgs::Float32>("sudo_steerAngle",10);
    speed_publisher = node_obj2.advertise<std_msgs::Float32>("sudo_speed",10);
}

CarControl::~CarControl() 
{

}

float CarControl::errorAngle(const Point &dst)
{
    static double pre_error , error,pre_pre_error,Out, pre_Out , sex_porn, P_part,I_part,D_part;
    if (dst.x == carPos.x) return 0;        // tren mot duong thang doc di dung huong
    if (dst.y == carPos.y) return (dst.x < carPos.x ? -90 : 90);    // tren duong thang ngang(horizon) queo 90
    double pi = acos(-1.0); // tinh pi
    double dx = dst.x - carPos.x; 
    double dy = carPos.y - dst.y; 

    if (dx < 0) 
    {
        error = -atan(-dx / dy) * 180 / pi;

    }
    else
    {
        error = atan(dx / dy) * 180 / pi;
  
    }

    // P_part = KP*(error - pre_error);
    // I_part = 0.5*KI*T*(error + pre_error);
    // D_part = KD/T*( error - 2*pre_error+ pre_pre_error);
    // Out = pre_Out + P_part + I_part + D_part ;
    // pre_pre_error = pre_error;
    // pre_error = error;
    // pre_Out = Out;  

    P_part = KP*error;
    I_part = KI*T*(error + pre_error);
    D_part = KD/T*( error - pre_error);
    Out = P_part + I_part + D_part ;
    pre_error = error;


    sex_porn = Out;
    
    return sex_porn;

    // if (dx < 0) return -atan(-dx / dy) * 180 / pi;

    // return atan(dx / dy) * 180 / pi;
}

void CarControl::driverCar(const vector<Point> &left, const vector<Point> &right, float velocity)
{
    int i = left.size() - 11;
    float error = preError;
    while (left[i] == DetectLane::null && right[i] == DetectLane::null) // ko co lane
    {
        i--;
        if (i < 0) return;
    }
    if (left[i] != DetectLane::null && right[i] !=  DetectLane::null) // co ca 2 lane
    {
        error = errorAngle((left[i] + right[i]) / 2);
    } 
    else if (left[i] != DetectLane::null) // co lane trai
    {
        error = errorAngle(left[i] + Point(laneWidth / 2, 0));
    }
    else    // co lane phai
    {
        error = errorAngle(right[i] - Point(laneWidth / 2, 0));
    }

    std_msgs::Float32 angle;
    std_msgs::Float32 speed;

    angle.data = error;
    speed.data = velocity;

    steer_publisher.publish(angle);
    speed_publisher.publish(speed);    
} 
