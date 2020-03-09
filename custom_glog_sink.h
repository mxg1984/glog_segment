#include <string>
#include <unordered_map>

#include <glog/logging.h>

class CustomGlogSink final : public google::LogSink {
 public:
  CustomGlogSink() = default;
  ~CustomGlogSink() = default;

  virtual void send(google::LogSeverity severity, const char* full_filename,
                    const char* base_filename, int line, const struct ::tm* tm_time,
                    const char* message, size_t message_len) override;
  virtual void WaitTillSent() override;

 private:
  std::unordered_map<uint32_t, std::string> kSeverityMap = {
      {0, "[INFO ]"}, {1, "[WARN ]"}, {2, "[ERROR]"}, {3, "[FATAL]"}};
};
