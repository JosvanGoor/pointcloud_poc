#include "main.ih"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "pointcloud_poc");
    ros::NodeHandle node;

    PointCloudAccumulator pca
    {
        get_param<std::string>("pointcloud_input"),
        get_param<std::string>("output_topic")
    };
    ros::spin();
}