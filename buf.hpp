#pragma once

#include "tools.h"
#include <string>

template <size_t SIZE> struct buf {
  NO_CM(buf);
  buf();

  const char *begin() const;
  const char *end() const;
  char *cur() const;

  void add(const char *, size_t len);
  int rest() const;
  int len() const;
  void reset();

  std::string str() const;

private:
  char _buf[SIZE];
  char *_cur = _buf;
};

template <size_t SIZE> buf<SIZE>::buf() { memset(_buf, 0, SIZE); }

template <size_t SIZE> inline void buf<SIZE>::add(const char *src, size_t len) {
  if (static_cast<size_t>(end() - cur()) > len) {
    memcpy(_cur, src, len);
    _cur += len;
  }
}

template <size_t SIZE> inline std::string buf<SIZE>::str() const {
  return std::string(_buf, len());
}

template <size_t SIZE> inline const char *buf<SIZE>::begin() const {
  return _buf;
}
template <size_t SIZE> inline const char *buf<SIZE>::end() const {
  return _buf + SIZE;
}

template <size_t SIZE> inline int buf<SIZE>::rest() const {
  return end() - cur();
}
template <size_t SIZE> inline int buf<SIZE>::len() const { return _cur - _buf; }

template <size_t SIZE> inline char *buf<SIZE>::cur() const { return _cur; }

template <size_t SIZE> inline void buf<SIZE>::reset() { _cur = _buf; }
