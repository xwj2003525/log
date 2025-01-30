#pragma once

#include "buf.hpp"
#include "timestamp.hpp"

using timestamp = timestamp;
using Smallbuf = buf<4096>;

struct stream {

  NO_COPY(stream);
  stream() = default;
  template <class T> stream &operator<<(T);

  stream &operator<<(bool);
  stream &operator<<(char);
  stream &operator<<(const char *);
  stream &operator<<(const std::string &);

  void add(const char *, size_t len);
  const Smallbuf &buf() const;
  void reset();

private:
  Smallbuf _buf;
};

template <class T> inline stream &stream::operator<<(T t) {
  *this << std::to_string(t);
  return *this;
}

void add_meta(const char *time, const char *tid, const char *level,
              const char *filename, const char *func, int line, stream &);

const char *get_tid();
