#include "main.ih"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "pointcloud_poc");
    ros::NodeHandle node;

    PointCloudAccumulator pca
    {
        get_string_param("pointcloud_input"),
        get_string_param("output_topic")
    };
    ros::spin();
}