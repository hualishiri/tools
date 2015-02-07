#include "util/logger.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

namespace tools {
namespace {

LogLevel log_level = kDebug;
FILE* log_file = stdout;
char now_str[sizeof("2011/11/11 11:11:11")];
const char* LevelName[] = {
  "NONE",
  "FATAL",
  "CRITICAL",
  "ERROR",
  "WARNING",
  "INFO",
  "DEBUG"
};

} //namespace

void UpdateTime() {
  time_t now = 0;
  time_t t = time(NULL);
  if (t - now == 0 ) return;
  now = t;
  struct tm tm;
  tm = *localtime(&now);
  sprintf(now_str, 
          "%04d/%02d/%02d %02d:%02d:%02d",
          1900 + tm.tm_year,
          tm.tm_mon + 1,
          tm.tm_mday,
          tm.tm_hour,
          tm.tm_min,
          tm.tm_sec);
}

void LogPrint(LogLevel level, const char* fmt, ...) {
  va_list args;
  if (level > log_level) return;
  va_start(args, fmt);
  if (log_file) vfprintf(log_file, fmt, args);
  va_end(args);
  fflush(log_file);
}

void LogInternal(LogLevel level, const char* fmt, ...) {
  va_list args;
  if (level > log_level) return;
  UpdateTime();
  if (log_file) fprintf(log_file, "%s [%s] ", now_str, LevelName[level]);
  va_start(args, fmt);
  if (log_file) vfprintf(log_file, fmt, args);
  va_end(args);
  fflush(log_file);
}

} //namespace tools
