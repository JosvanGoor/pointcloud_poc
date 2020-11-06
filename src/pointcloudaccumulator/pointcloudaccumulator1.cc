#include "pointcloudaccumulator.ih"

PointCloudAccumulator::PointCloudAccumulator()
:   d_pointcloud(nullptr),
    d_kdtree(true)
{
    d_pointcloud = boost::make_shared<PointCloud>();
}