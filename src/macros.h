#pragma once

#define ERROR(name, err)                                                                                                                   \
  if ((err) == -1)                                                                                                                         \
    perror(name);