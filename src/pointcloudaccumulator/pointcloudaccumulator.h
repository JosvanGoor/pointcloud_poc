#ifndef POINTCLOUDPOC_PCACCUMULATOR_H
#define POINTCLOUDPOC_PCACCUMULATOR_H

#include "ros/ros.h"
#include "pcl_ros/publisher.h"
#include "pcl_conversions/pcl_conversions.h"

#include "sensor_msgs/PointCloud2.h"
#include "geometry_msgs/TransformStamped.h"

#include "pcl-1.9/pcl/point_types.h"
#include "pcl-1.9/pcl/conversions.h"
#include "pcl-1.9/pcl/search/kdtree.h"
#include "pcl-1.9/pcl/filters/voxel_grid.h"

#include "tf/transform_listener.h"
#include <memory>

using Point = pcl::PointXYZ;
using PointCloud = pcl::PointCloud<Point>;
using PointCloudPtr = PointCloud::Ptr;
using KdTree = pcl::search::KdTree<Point>;

class PointCloudAccumulator
{
    PointCloudPtr d_pointcloud;
    KdTree d_kdtree;

    public:
        PointCloudAccumulator();
        void accumulate(sensor_msgs::PointCloud2 const &cloud);

        PointCloudPTR &pointcloud();

    private:
        // no copies
        PointCloudAccumulator(PointCloudAccumulator const &) = delete;
        PointCloudAccumulator& operator=(PointCloudAccumulator const &) = delete;

        void radius_filter(PointCloud const &input, float mindist = 0.1);
};

#endif