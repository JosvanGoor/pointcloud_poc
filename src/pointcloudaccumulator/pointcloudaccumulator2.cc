#include "pointcloudaccumulator.ih"

PointCloudAccumulator::PointCloudAccumulator(string const &pc_in, string const &out)
:   PointCloudAccumulator()
{
    d_pointcloud = boost::make_shared<PointCloud>();

    ros::NodeHandle node;
    d_publisher = node.advertise<PointCloud>(out, 1);
    d_pointcloud_in = node.subscribe("/xtion/depth_registered/points", 5, &PointCloudAccumulator::accumulate, this);
}