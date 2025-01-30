
#include "common.h"
#include <sstream>
#include <string>
#include <thread>

stream &stream::operator<<(bool b) {
  if (b) {
    _buf.add("true", 4);
  } else {
    _buf.add("false", 5);
  }
  return *this;
}

stream &stream::operator<<(char c) {
  _buf.add(&c, 1);
  return *this;
}

stream &stream::operator<<(const char *v) {
  if (v) {
    _buf.add(v, strlen(v));
  }
  return *this;
}

stream &stream::operator<<(const std::string &s) {
  _buf.add(s.c_str(), s.size());
  return *this;
}

stream &stream::operator<<(const Smallbuf &b) {
  *this << b.str();
  return *this;
}

void stream::add(const char *c, size_t l) { _buf.add(c, l); }
const Smallbuf &stream::buf() const { return _buf; }
void stream::reset() { _buf.reset(); }

// orther

namespace {
thread_local const std::string tid_str = []() {
  std::ostringstream oss;
  oss << std::this_thread::get_id();
  return oss.str();
}();

thread_local const char *ctid = tid_str.c_str();
} // namespace

void add_meta(const char *time, const char *tid, const char *level,
              const char *filename, const char *func, int line, stream &s) {
  s << time << " " << tid << " " << level << " " << filename << ":" << func
    << ":" << line << " ";
}

const char *get_tid() { return ctid; }
