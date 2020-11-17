#include "pointcloudaccumulator.ih"

void PointCloudAccumulator::accumulate(sensor_msgs::PointCloud2 const &cloud)
{
    pcl::PCLPointCloud2::Ptr pcl_pc2 = boost::make_shared<pcl::PCLPointCloud2>();
    pcl::PCLPointCloud2::Ptr filtered = boost::make_shared<pcl::PCLPointCloud2>();;
    sensor_msgs::PointCloud2 post_tf;

    ROS_INFO("Gonna transform!\n");
    d_tflistener.waitForTransform("/base_link", cloud.header.frame_id, ros::Time(0), ros::Duration(1.0));
    pcl_ros::transformPointCloud("/base_link", cloud, post_tf, d_tflistener);
    ROS_INFO("Did transforming!\n");
    ROS_INFO("After filter the cloud has %d points\n", post_tf.width * post_tf.height);


    pcl_conversions::toPCL(post_tf, *pcl_pc2);
    
    pcl::VoxelGrid<pcl::PCLPointCloud2> filter;
    filter.setInputCloud(pcl_pc2);
    filter.setLeafSize(0.1f, 0.1f, 0.1f);
    filter.filter(*filtered);

    PointCloud converted;
    pcl::fromPCLPointCloud2(*filtered, converted);

    radius_filter(converted, 0.1);
    ROS_INFO("Currently have %lu points stored.\n", d_pointcloud->size());

    d_pointcloud->header.frame_id = "map";
    pcl_conversions::toPCL(ros::Time::now(), d_pointcloud->header.stamp);
    d_publisher.publish(d_pointcloud);
}