cmake_minimum_required(VERSION 3.0)

project(glog_segment)

find_package(glog REQUIRED)

include_directories(glog_INCLUDE_DIR)
add_executable(glog_segment main.cc glog_segment.cc)
target_link_libraries(glog_segment glog::glog)
