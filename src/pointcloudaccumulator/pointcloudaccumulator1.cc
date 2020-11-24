#include "pointcloudaccumulator.ih"

PointCloudAccumulator::PointCloudAccumulator()
:   d_pointcloud(nullptr),
    d_kdtree(true),
    d_publisher(),
    d_pointcloud_in(),
    d_tflistener(),
    d_transform_to()
{
    
}