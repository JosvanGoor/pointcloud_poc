#include "main.ih"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "pointcloud_poc");
    ros::NodeHandle node;

    PointCloudAccumulator pca;
    
    ros::Subscriber depth_receiver = node.subscribe("/xtion/depth_registered/points", 5, &PointCloudAccumulator::accumulate, &pca);
    ros::spin();
}