#include "glog_segment.h"

#include <glog/logging.h>

GlogSegment* GlogSegment::instance() {
  static GlogSegment obj;
  return &obj;
}

void GlogSegment::InitLogging() {
  if (!initialized_) {
    google::InitGoogleLogging(argv0_.c_str());
    initialized_ = true;
  }
  google::SetLogFilenameExtension((std::to_string(log_index_++) + "_").c_str());
  google::SetLogDestination(google::GLOG_INFO, log_dir_.c_str());
}

void GlogSegment::RecreateLog() {
  std::unique_lock<std::mutex> lock(mutex_);
  if (initialized_) {
    google::ShutdownGoogleLogging();
    initialized_ = false;
  }
  InitLogging();
}

void GlogSegment::set_argv0(const std::string& argv0) {
  std::unique_lock<std::mutex> lock(mutex_);
  argv0_ = argv0;
}

void GlogSegment::set_log_dir(const std::string& log_dir) {
  std::unique_lock<std::mutex> lock(mutex_);
  log_dir_ = log_dir;
}

bool GlogSegment::initialized() {
  return initialized_;
}
