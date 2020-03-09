#pragma once

#include <atomic>
#include <mutex>
#include <string>

class GlogSegment final {
 public:
  GlogSegment();
  ~GlogSegment() = default;

 public:
  static GlogSegment* instance();

  void InitCustomGoogleLogging(const std::string& log_dir);
  void set_argv0(const std::string& arv0);
  void set_log_dir(const std::string& log_dir);
  std::string argv0() const;
  void RecreateLog();
  bool initialized();

 private:
  void InitLogging();

 private:
  std::atomic_bool initialized_ = {false};
  mutable std::mutex mutex_;
  std::atomic_uint log_index_ = {1};
  std::string log_dir_ = "/tmp";
  std::string argv0_ = "";
  const uint32_t kMaxPathLen = 256;
};
