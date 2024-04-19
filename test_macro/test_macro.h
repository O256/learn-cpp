#include <stdio.h>

#define IF_NOT(x)                                                              \
  if ((!(x)) ? (printf("★IF_NOT(%s)★ in %s, %d\n", #x, __FILE__, __LINE__), 1) \
             : 0)
