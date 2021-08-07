#ifndef TIME_MEASURE_GB
#define TIME_MEASURE_GB

#include <sys/time.h>

typedef void(*TFunc)();
typedef void(*IntSortFunc)(int*, unsigned);

double get_clock_diff(TFunc func) {

  struct timeval start, end;

  gettimeofday(&start, NULL);

  func();

  gettimeofday(&end, NULL);

  double time_taken;
  time_taken = (end.tv_sec - start.tv_sec) * 1e6;
  time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

  return time_taken;
}

double get_clock_diff_sort(IntSortFunc func, int * arr, unsigned size) {
  struct timeval start, end;

  gettimeofday(&start, NULL);

  func(arr, size);

  gettimeofday(&end, NULL);

  double time_taken;
  time_taken = (end.tv_sec - start.tv_sec) * 1e6;
  time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

  return time_taken;
}

#endif
