cmake_minimum_required(VERSION 3.0.2)
project(pointcloud_poc)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++14)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
    message_generation
    pcl_ros
    roscpp
)

find_package(PCL 1.9 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

generate_messages(
    DEPENDENCIES
    std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

set(SOURCE_CODE
    src/main.cc
)

add_executable(${PROJECT_NAME}_node ${SOURCE_CODE})

## Generate messages before compiling (useful for compiling empty workspace)
# add_dependencies(${PROJECT_NAME}_node bounding_box_server_generate_messages_cpp)

target_link_libraries(${PROJECT_NAME}_node
   ${catkin_LIBRARIES}
)