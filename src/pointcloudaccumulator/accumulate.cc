#include "pointcloudaccumulator.ih"

void PointCloudAccumulator::accumulate(sensor_msgs::PointCloud2 const &cloud)
{
    pcl::PCLPointCloud2::Ptr pcl_pc2 = boost::make_shared<pcl::PCLPointCloud2>();
    pcl::PCLPointCloud2::Ptr filtered = boost::make_shared<pcl::PCLPointCloud2>();;
    sensor_msgs::PointCloud2 post_tf;

    // ROS_INFO("Gonna transform!\n");
    d_tflistener.waitForTransform(d_transform_to, cloud.header.frame_id, ros::Time(0), ros::Duration(1.0));
    pcl_ros::transformPointCloud(d_transform_to, cloud, post_tf, d_tflistener);
    // ROS_INFO("Did transforming!\n");
    // ROS_INFO("After filter the cloud has %d points\n", post_tf.width * post_tf.height);

    if (post_tf.width * post_tf.height == 0)
    {
        ROS_INFO("Transformed cloud is empty.");
        return;
    }

    pcl_conversions::toPCL(post_tf, *pcl_pc2);
    
    pcl::VoxelGrid<pcl::PCLPointCloud2> filter;
    filter.setInputCloud(pcl_pc2);
    filter.setLeafSize(d_mindist, d_mindist, d_mindist);
    filter.filter(*filtered);

    PointCloud converted;
    pcl::fromPCLPointCloud2(*filtered, converted);

    radius_filter(converted, d_mindist);
    // ROS_INFO("Currently have %lu points stored.\n", d_pointcloud->size());

    d_pointcloud->header.frame_id = d_transform_to;
    pcl_conversions::toPCL(ros::Time::now(), d_pointcloud->header.stamp);
    d_publisher.publish(d_pointcloud);
}