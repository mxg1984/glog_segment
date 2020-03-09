#include <glog/logging.h>

#include <string>
#include <thread>

#include "custom_glog_sink.h"

int main(int argc, char* argv[]) {
  ::google::InitGoogleLogging(argv[0]);
  CustomGlogSink log_sink;
  google::AddLogSink(&log_sink);

  LOG(INFO) << "hello1";
  LOG(ERROR) << "hello2";
  LOG_TO_SINK(&log_sink, INFO) << "LOG_TO_SINK";
  LOG_TO_SINK_BUT_NOT_TO_LOGFILE(&log_sink, INFO) << "LOG_TO_SINK_BUT_NOT_LOGFILE";

  return 0;
}
