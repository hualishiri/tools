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
  LogInternal(kInfo, s);                            \
  LogPrint(kInfo, "\n");                            \
} while(0)

#define LogWarning(s...) do {                       \
  LogInternal(kWarning, s);                         \
  LogPrint(kWarning, "\n");                         \
} while(0)

#define LogError(s...) do {                        \
  LogInternal(kError, s);                          \
  LogPrint(kError, "\n");                          \
} while(0)

#define LogCritical(s...) do {                     \
  LogInternal(kCritical, s);                       \
  LogPrint(kCritical, "\n");                       \
} while(0)

#define LogFatal(s...) do {                        \
  LogInternal(kFatal, s);                          \
  LogPrint(kFatal, "\n");                          \
} while(0)

#ifdef LOGDEBUG
#define LogDebug(s...) do {                        \
  LogInternal(kDebug, s);                          \
  LogPrint(kDebug, " [%s]", __PRETTY_FUNCTION__);  \
  LogPrint(kDebug, "\n");                          \
} while(0)

#else
#define LogDebug(s...)
#endif

void LogInternal(LogLevel level, const char* fmt, ...);
void LogPrint(LogLevel level, const char* fmt, ...);

} //namespace tools

#endif //TOOLS_UTIL_LOGGER_H_
