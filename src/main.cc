#include <iostream>

#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"
#include "sensor_msgs/PointCloud2.h"
#include "pcl-1.9/pcl/point_cloud.h"
#include "pcl-1.9/pcl/point_types.h"
#include "pcl-1.9/pcl/conversions.h"
#include "pcl_ros/transforms.h"
#include "pcl_ros/publisher.h"
#include "pcl_conversions/pcl_conversions.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf/transform_listener.h"

using namespace std;
using PointCloud = pcl::PointCloud<pcl::PointXYZ>;

ros::Publisher pub;
ros::Publisher utf;

class Thingamajig
{
    tf::TransformListener d_tflistener;
    PointCloud d_master_cloud;

    public:
        void the_callback(sensor_msgs::PointCloud2 const &cloud)
        {
            sensor_msgs::PointCloud2 post_tf;
            geometry_msgs::TransformStamped transform;

            // auto newcloud = ros::topic::waitForMessage<sensor_msgs::PointCloud2>("/xtion/depth_registered/points", ros::Duration(1.0));
            d_tflistener.waitForTransform("/base_link", cloud.header.frame_id, ros::Time(0), ros::Duration(1.0));
            pcl_ros::transformPointCloud("/base_link", cloud, post_tf, d_tflistener);
            
            pcl::PCLPointCloud2 pcl_pc2;
            pcl_conversions::toPCL(post_tf, pcl_pc2);

            PointCloud transformed;
            pcl::fromPCLPointCloud2(pcl_pc2, transformed);

            d_master_cloud += transformed;
            pcl::toPCLPointCloud2(d_master_cloud, pcl_pc2);
            pcl_conversions::fromPCL(pcl_pc2, post_tf);

            pub.publish(post_tf);
        }
};

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "pointcloud_poc");
    ros::NodeHandle nodehandle;
    Thingamajig jig;
    pub = nodehandle.advertise<sensor_msgs::PointCloud2>("pointcloud_plc_out", 1);
    
    // utf = nodehandle.advertise<sensor_msgs::PointCloud2>("pointcloud_plc_utf");

    ros::Subscriber depth_receiver = nodehandle.subscribe("/xtion/depth_registered/points", 5, &Thingamajig::the_callback, &jig);
    ros::spin();
}