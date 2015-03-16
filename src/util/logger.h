#ifndef TOOLS_UTIL_LOGGER_H_
#define TOOLS_UTIL_LOGGER_H_

namespace tools {

enum LogLevel {
  kNone = 0,
  kFatal,
  kCritical,
  kError,
  kWarning,
  kInfo,
  kDebug
};

#define LogInfo(s...) do {                          \
  tools::LogInternal(tools::kInfo, s);                            \
  tools::LogPrint(tools::kInfo, "\n");                            \
} while(0)

#define LogWarning(s...) do {                       \
  tools::LogInternal(tools::kWarning, s);                         \
  tools::LogPrint(tools::kWarning, "\n");                         \
} while(0)

#define LogError(s...) do {                        \
  tools::LogInternal(tools::kError, s);                          \
  tools::LogPrint(tools::kError, "\n");                          \
} while(0)

#define LogCritical(s...) do {                     \
  tools::LogInternal(tools::kCritical, s);                       \
  tools::LogPrint(tools::kCritical, "\n");                       \
} while(0)

#define LogFatal(s...) do {                        \
  LogInternal(kFatal, s);                          \
  LogPrint(kFatal, "\n");                          \
} while(0)

#ifdef LOGDEBUG
#define LogDebug(s...) do {                        \
  tools::LogInternal(tools::kDebug, s);                          \
  tools::LogPrint(tools::kDebug, " [%s]", __PRETTY_FUNCTION__);  \
  tools::LogPrint(tools::kDebug, "\n");                          \
} while(0)

#else
#define LogDebug(s...)
#endif

void LogInternal(LogLevel level, const char* fmt, ...);
void LogPrint(LogLevel level, const char* fmt, ...);

} //namespace tools

#endif //TOOLS_UTIL_LOGGER_H_
