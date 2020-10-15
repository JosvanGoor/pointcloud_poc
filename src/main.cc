#include <iostream>
#include <sstream>

#include <thread>

#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "hello world!\n";

    ros::init(argc, argv, "pointcloud_poc");

    ros::NodeHandle nodehandle;
    ros::Publisher outputter = nodehandle.advertise<std_msgs::String>("pcpoc_text", 1);
    ros::Duration rate(1.0 / 10);

    if (!outputter)
    {
        cerr << "outputter creation failed\n";
        exit(-1);
    }

    size_t idx = 0;

    auto callback = [&]([[maybe_unused]] ros::TimerEvent const& timer_event)
    {
        std_msgs::String msg;
        stringstream ss;
        ss << "hello #" << idx << "\n";
        msg.data = ss.str();

        ROS_INFO("%s", msg.data.c_str());
        outputter.publish(msg);
        ++idx;
    };  

    ros::Timer timer = nodehandle.createTimer(ros::Duration(0.1), callback);
    ros::spin();

    return 0;
}