#ifndef POINTCLOUD_POC_UTILITY_H
#define POINTCLOUD_POC_UTILITY_H

#include <string>

template <typename Type>
Type get_param(std::string const &key);

#include "getparam.f"

#endif