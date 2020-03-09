#include <glog/logging.h>

#include <iostream>
#include <string>
#include <thread>

#include "custom_glog_sink.h"
#include "glog_segment.h"

int main(int argc, char* argv[]) {
  FLAGS_alsologtostderr = true;
  FLAGS_minloglevel = 0;
  GlogSegment::instance()->InitCustomGoogleLogging("/tmp/");
  std::cout << GlogSegment::instance()->argv0() << std::endl;

  GlogSegment::instance()->RecreateLog();
  CustomGlogSink log_sink;
  google::AddLogSink(&log_sink);
  LOG(INFO) << "hello1";

  GlogSegment::instance()->RecreateLog();
  google::AddLogSink(&log_sink);

  LOG(ERROR) << "hello2";
  LOG_TO_SINK(&log_sink, ERROR) << "hello3";
  LOG_TO_SINK_BUT_NOT_TO_LOGFILE(&log_sink, INFO) << "hello4";

  return 0;
}
