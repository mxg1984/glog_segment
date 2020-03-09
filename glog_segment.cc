#include "glog_segment.h"

#include <glog/logging.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

GlogSegment* GlogSegment::instance() {
  static GlogSegment obj;
  return &obj;
}

GlogSegment::GlogSegment() {
  char current_executable_path[kMaxPathLen] = {0};
#ifdef _WIN32
  GetModuleFileName(NULL, current_executable_path, sizeof(current_executable_path));
#else
  readlink("/proc/self/exe", current_executable_path, kMaxPathLen);
#endif
  argv0_.assign(current_executable_path);
}

void GlogSegment::InitCustomGoogleLogging(const std::string& log_dir) {
  std::unique_lock<std::mutex> lock(mutex_);
  log_dir_ = log_dir;
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
  CHECK(!argv0_.empty()) << "must initialize argv[0] before using glog";
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

std::string GlogSegment::argv0() const {
  std::unique_lock<std::mutex> lock(mutex_);
  return argv0_;
}

void GlogSegment::set_log_dir(const std::string& log_dir) {
  std::unique_lock<std::mutex> lock(mutex_);
  log_dir_ = log_dir;
}

bool GlogSegment::initialized() {
  return initialized_;
}
