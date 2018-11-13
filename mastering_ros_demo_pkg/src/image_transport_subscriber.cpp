#include <ros/ros.h>
#include "std_msgs/Float32.h"
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
// #include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <math.h>
#include <cstdint>
#include <cstdbool>

using namespace cv;
using namespace std;
/***********************************************************************************************************************/

/*************************************************************************************************************************/

//--- INITIALIZE VIDEOWRITER
    VideoWriter writer;
    bool isColor = true;
    int codec = CV_FOURCC('M', 'J', 'P', 'G');  // select desired codec (must be available at runtime)
    double fps = 25.0;                          // framerate of the created video stream
    string filename = "./live.avi";             // name of the output video file
    

class ImageConverter
{
  private:
    ros::NodeHandle nh_,nh_pub;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    ros::Publisher pub_vel;
    std_msgs::Float32 my_vel;
  public:
    // constructor
    ImageConverter() : it_(nh_)
    {
        image_sub_ = it_.subscribe("/sudo_image", 1, &ImageConverter::imageCb, this);
        pub_vel = nh_pub.advertise<std_msgs::Float32>("/speed",10);
    }
    ~ImageConverter()
    {
        cv::destroyAllWindows();
    }
    void imageCb(const sensor_msgs::ImageConstPtr &msg)
    {
        cv::Mat grayImage;
        cv_bridge::CvImagePtr cv_ptr;
        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception &e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }
        ROS_INFO("ahihi");
        waitKey(10);
        // cvWaitKey(10);
        imshow("view", cv_ptr->image);
        //************write video************//
        Mat src = ( cv_ptr->image ).clone();
        // check if we succeeded
        if (!writer.isOpened()) {
            cerr << "Could not open the output video file for write\n";
            return ;
        }

        /******************************** publish speed ***********************************************/
        my_vel.data=10.0f;

        pub_vel.publish(my_vel);
        /*****************************************************************************************************/
        writer.write(src);
    }
};
int main(int argc, char **argv)
{
    writer.open(filename, codec, fps, Size(320,240), isColor);
    ros::init(argc, argv, "image_listener_thuhinh");
    ros::NodeHandle nh;
    cv::namedWindow("view");
    cv::startWindowThread();
    ImageConverter ic;
    ros::spin();
    cv::destroyWindow("view");

}
