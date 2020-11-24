#include "utility.ih"

std::string get_string_param(std::string const &key)
{
    std::string full_key;
    if (!ros::param::search(key, full_key))
    {
        ROS_WARN("-----");
        ROS_WARN("Missing parameter: %s", key.c_str());
        ROS_WARN("Shutting down...");
        ROS_WARN("-----");
        exit(1);
    }

    std::string rval;
    ros::param::get(full_key, rval);
    return rval;
}