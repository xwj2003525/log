#pragma once

#include "common.h"
#include <cstdlib>
#include <string>

enum class level { TRACE, DEBUG, INFO, WARN, ERROR, FATAL };

void initlevel(level);

struct synclog {

  synclog(const char *tid, level l, const char *filename, int line,
          const char *func);
  ~synclog();
  struct stream &stream();

private:
  level l_;
  struct stream buf_;
};

level getlevel();

#define LOG(severity)                                                          \
  if (getlevel() <= level::severity)                                           \
  synclog(get_tid(), level::severity, __FILE__, __LINE__, __func__).stream()
