#include "timing.h"

#define buf_size 80


int identity(int x) { return x; }

int sum(int s)
{
  int i;
  for(i=0; i < 1000000; i++) s += i;
  return s;
}

#define CLOCKTYPE CLOCK_MONOTONIC
/* this one should be appropriate to avoid errors on multiprocessors systems */

double TIM_time_it(int (*action)(int), int arg)
{
  struct timespec tsi, tsf;

  clock_gettime(CLOCKTYPE, &tsi);
  action(arg);
  clock_gettime(CLOCKTYPE, &tsf);

  double elaps_s = difftime(tsf.tv_sec, tsi.tv_sec);
  long elaps_ns = tsf.tv_nsec - tsi.tv_nsec;
  return elaps_s + ((double)elaps_ns) / 1.0e9;
}
