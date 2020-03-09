cmake_minimum_required(VERSION 3.0)

project(glog_segment)

find_package(glog REQUIRED)

add_library(glog_util SHARED glog_segment.cc custom_glog_sink.cc)
target_link_libraries(glog_util glog::glog)

add_executable(glog_segment main.cc)
target_link_libraries(glog_segment glog_util)

add_executable(glog_log_sink custom_glog_sink_test.cc)
target_link_libraries(glog_log_sink glog_util)
