#include "pointcloudaccumulator.ih"

void PointCloudAccumulator::accumulate(sensor_msgs::PointCloud2 const &cloud)
{
    pcl::PCLPointCloud2 pcl_pc2;
    pcl_conversions::toPCL(cloud, pcl_pc2);
    
    PointCloud converted;
    PointCloud filtered;
    pcl::fromPCLPointCloud2(pcl_pc2, converted);
    
    pcl::VoxelGrid<PointCloud> filter;
    filter.setInputCloud(converted);
    filter.setLeafSize(0.1f, 0.1f, 0.1f);
    filter.filter(filtered);

    radius_filter(filtered, 0.1);
    ROS_INFO("Currently have %lu points stored.\n", d_pointcloud->size());
}