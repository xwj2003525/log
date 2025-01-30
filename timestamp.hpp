#pragma once

#include <boost/operators.hpp>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <sys/time.h>
struct timestamp : public boost::equality_comparable<timestamp>,
                   public boost::less_than_comparable<timestamp> {

  timestamp();
  explicit timestamp(uint64_t t);

  std::string to_string() const;
  uint64_t epochms() const;
  static timestamp now();
  timestamp &operator=(const timestamp &t);
  bool operator<(const timestamp &t) const;
  bool operator==(const timestamp &t) const;
  timestamp operator+(const timestamp &t) const;

  static timestamp abs_gap(const timestamp &t1, const timestamp &t2);

private:
  uint64_t _epochms;
};

inline std::string timestamp::to_string() const {
  struct timeval tv;
  tv.tv_sec = _epochms / 1000;           // 秒部分
  tv.tv_usec = (_epochms % 1000) * 1000; // 微秒部分

  struct tm timeinfo;
  localtime_r(&tv.tv_sec, &timeinfo); // 使用线程安全的 localtime_r

  std::ostringstream oss;
  oss << std::setw(4) << std::setfill('0') << (timeinfo.tm_year + 1900) << "-"
      << std::setw(2) << std::setfill('0') << (timeinfo.tm_mon + 1) << "-"
      << std::setw(2) << std::setfill('0') << timeinfo.tm_mday << " "
      << std::setw(2) << std::setfill('0') << timeinfo.tm_hour << ":"
      << std::setw(2) << std::setfill('0') << timeinfo.tm_min << ":"
      << std::setw(2) << std::setfill('0') << timeinfo.tm_sec << "."
      << std::setw(3) << std::setfill('0')
      << (tv.tv_usec / 1000); // 只取毫秒部分（3 位）

  return oss.str();
}

inline timestamp::timestamp() : _epochms(0) {}

inline timestamp::timestamp(uint64_t t) : _epochms(t) {}

inline uint64_t timestamp::epochms() const { return _epochms; }

inline timestamp timestamp::now() {
  struct timeval tv;
  gettimeofday(&tv, nullptr);
  uint64_t milliseconds = tv.tv_sec * 1000 + tv.tv_usec / 1000;
  return timestamp(milliseconds);
}

inline timestamp &timestamp::operator=(const timestamp &t) {
  if (this != &t) {
    this->_epochms = t._epochms;
  }
  return *this;
}

inline bool timestamp::operator<(const timestamp &t) const {
  return _epochms < t._epochms;
}

inline bool timestamp::operator==(const timestamp &t) const {
  return _epochms == t._epochms;
}

inline timestamp timestamp::operator+(const timestamp &t) const {
  return timestamp(_epochms + t._epochms);
}

inline timestamp timestamp::abs_gap(const timestamp &t1, const timestamp &t2) {
  if (t1 < t2) {
    return timestamp(t2.epochms() - t1.epochms());
  }
  return timestamp(t1.epochms() - t2.epochms());
}
