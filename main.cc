#include <glog/logging.h>

#include <string>
#include <thread>

#include "glog_segment.h"

int main(int argc, char* argv[]) {
  GlogSegment::instance()->set_argv0(argv[0]);
  GlogSegment::instance()->set_log_dir("/home/pd/Documents/");
  GlogSegment::instance()->RecreateLog();
  LOG(INFO) << "hello1";
  LOG(ERROR) << "hello1";
  GlogSegment::instance()->RecreateLog();
  LOG(INFO) << "hello2";
  LOG(ERROR) << "hello2";

  return 0;
}
