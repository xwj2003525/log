#pragma once

#include <string.h>

#define NO_COPY(cls)                                                           \
  cls(const cls &) = delete;                                                   \
  cls &operator=(const cls &) = delete;

#define NO_MOVE(cls)                                                           \
  cls(cls &&) = delete;                                                        \
  cls &operator=(cls &&) = delete;

#define NO_CM(cls)                                                             \
  NO_COPY(cls);                                                                \
  NO_MOVE(cls);

#define ZERO(cls) memset(this,0,sizeof(cls));
