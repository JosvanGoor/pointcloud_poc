#include "pointcloudaccumulator.ih"

void PointCloudAccumulator::radius_filter(PointCloud const &input, float mindist)
{
    if (d_pointcloud->size() == 0)
        d_pointcloud->push_back(input[0]);

    std::vector<int> indices;
    std::vector<float> distances;
    d_kdtree.setInputCloud(d_pointcloud);

    size_t done_did = 0;
    for (auto const &point : input)
    {
        ++done_did;
        if (d_kdtree.radiusSearch(point, mindist, indices, distances, 1) == 0)
            d_pointcloud->push_back(point);
    }

    // ROS_INFO("Tested %lu points.", done_did);

}