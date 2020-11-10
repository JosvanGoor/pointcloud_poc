#include "pointcloudaccumulator.ih"

PointCloudAccumulator::PointCloudAccumulator()
:   d_pointcloud(nullptr),
    d_kdtree(true),
    d_publisher(),
    d_tflistener()
{
    d_pointcloud = boost::make_shared<PointCloud>();

    ros::NodeHandle node;
    d_publisher = node.advertise<PointCloud>("pointcloud_plc_out", 1);
}