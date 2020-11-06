#include "pointcloudaccumulator.ih"

void PointCloudAccumulator::accumulate(sensor_msgs::PointCloud2 const &cloud)
{
    pcl::PCLPointCloud2::Ptr pcl_pc2 = boost::make_shared<pcl::PCLPointCloud2>();
    pcl::PCLPointCloud2::Ptr filtered = boost::make_shared<pcl::PCLPointCloud2>();;
    
    pcl_conversions::toPCL(cloud, *pcl_pc2);
    
    pcl::VoxelGrid<pcl::PCLPointCloud2> filter;
    filter.setInputCloud(pcl_pc2);
    filter.setLeafSize(0.1f, 0.1f, 0.1f);
    filter.filter(*filtered);

    PointCloud converted;
    pcl::fromPCLPointCloud2(*filtered, converted);

    radius_filter(converted, 0.1);
    ROS_INFO("Currently have %lu points stored.\n", d_pointcloud->size());
}