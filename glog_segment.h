#pragma once

#include <atomic>
#include <mutex>
#include <string>

class GlogSegment final {
 public:
  GlogSegment() = default;
  ~GlogSegment() = default;

 public:
  static GlogSegment* instance();

  void set_argv0(const std::string& arv0);
  void set_log_dir(const std::string& log_dir);
  void RecreateLog();
  bool initialized();

 private:
  void InitLogging();

 private:
  std::atomic_bool initialized_ = {false};
  std::mutex mutex_;
  std::atomic_uint log_index_ = {1};
  std::string log_dir_ = "/tmp";
  std::string argv0_ = "";
};
