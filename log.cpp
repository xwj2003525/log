#include "log.h"

level g_level = level::FATAL;

inline void initlevel(level l) { g_level = l; }

const char *level_to_string(level l) {
  switch (l) {
  case level::TRACE:
    return "\033[93m[TRACE]\033[0m"; // 浅黄色
  case level::DEBUG:
    return "\033[92m[DEBUG]\033[0m"; // 浅绿色
  case level::INFO:
    return "\033[94m[INFO ]\033[0m"; // 浅蓝色
  case level::WARN:
    return "\033[35m[WARN ]\033[0m";
  case level::ERROR:
    return "\033[91m[ERROR]\033[0m"; // 浅红色
  case level::FATAL:
    return "\033[91m[FATAL]\033[0m"; // 浅白色
  default:
    return "\033[37m[BADLEVEL]\033[0m"; // 默认白色
  }
}

synclog::synclog(const char *tid, level l, const char *filename, int line,
                 const char *func)
    : l_(l) {
  add_meta(timestamp::now().to_string().c_str(), tid, level_to_string(l),
           filename, func, line, buf_);
}

level getlevel() { return g_level; }
stream &synclog::stream() { return buf_; }

synclog::~synclog() {
  buf_ << "\n";
  const Smallbuf &buf = (buf_.buf());
  size_t ret = fwrite(buf.begin(), 1, buf.len(), stdout);
  // check ret

  if (l_ == level::FATAL) {
    fflush(stdout);
    abort();
  }
}
