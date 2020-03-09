#include "custom_glog_sink.h"

#include <iostream>
#include <sstream>

void CustomGlogSink::send(google::LogSeverity severity, const char* full_filename,
                          const char* base_filename, int line, const struct ::tm* tm_time,
                          const char* message, size_t message_len) {
  auto padding_zero = [](uint32_t a) { return (a < 10 ? "0" : ""); };
  std::string time = std::to_string(tm_time->tm_year + 1900) + "-" +
                     padding_zero(tm_time->tm_mon + 1) + std::to_string(tm_time->tm_mon + 1) + "-" +
                     padding_zero(tm_time->tm_mday) + std::to_string(tm_time->tm_mday) + " " +
                     padding_zero(tm_time->tm_hour) + std::to_string(tm_time->tm_hour) + ":" +
                     padding_zero(tm_time->tm_min) + std::to_string(tm_time->tm_min) + ":" +
                     padding_zero(tm_time->tm_sec) + std::to_string(tm_time->tm_sec);

  std::stringstream ss;

  ss << kSeverityMap[severity] + " " + time << " " << base_filename << ":" << line << ": "
     << message;

  std::cout << ss.str();
  //  std::cout << "CustomGlogSink:"
  //            << google::LogSink::ToString(severity, full_filename, line, tm_time, message,
  //                                         message_len)
  //            << std::endl;
}

void CustomGlogSink::WaitTillSent() {
  // std::cout << "CustomGlogSink::WaitTillSent" << std::endl;
}

