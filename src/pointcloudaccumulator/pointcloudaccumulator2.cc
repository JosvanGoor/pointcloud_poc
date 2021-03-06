#include "pointcloudaccumulator.ih"

PointCloudAccumulator::PointCloudAccumulator(string const &pc_in, string const &out)
:   PointCloudAccumulator()
{
    d_pointcloud = boost::make_shared<PointCloud>();

    ros::NodeHandle node;
    d_publisher = node.advertise<PointCloud>(out, 1);
    d_pointcloud_in = node.subscribe("/xtion/depth_registered/points", 5, &PointCloudAccumulator::accumulate, this);
    d_transform_to = get_param<std::string>("storage_tf_frame");
    d_mindist = get_param<float>("point_distance_m");

    ROS_INFO("%s: Mapping incoming pointclouds to %s", __FUNCTION__, d_transform_to.c_str());
}