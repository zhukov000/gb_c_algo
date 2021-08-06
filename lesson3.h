#ifndef LESSON3_GB
#define LESSON3_GB

#include <math.h>

//
int isPrime(unsigned x) {
  unsigned d = 2;
  while ((d * d <= x) && (x % d != 0)) ++d;
  return (x > 1) && (d * d > x);
}

//
int isPrimeSqrt(int x) {
  int last = (int) sqrt(x);
  for(int i = 2; i<= last; ++i) {
    if (x % i == 0)
      return 0;
  }
  return 1;
}

//
int prime_number_student(int *value)
{
  if(*value > 1 && *value < 3)
    return 1;

  if(*value < 2 || *value % 2 == 0)
    return 0;

  int v = (int)sqrt(*value);
  for(int i=3; i<=v; i+=2) {
    if ( *value % i == 0 )
      return 0;
  }
  return 1;
}

#endif
