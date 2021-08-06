/**
* azhukov
*/

#include"lesson2.h"
#include"lesson3.h"
#include"lesson4.h"

#include"time_measure.h"

void func1() {
  int x[2] = {1e9+7, 2147483647};
  for(unsigned i=0; i<1000; ++i) {
    isPrime(x[i&1]);
  }
}

void func2() {
  int x[2] = {1e9+7, 2147483647};
  for(unsigned i=0; i<1000; ++i) {
    isPrimeSqrt(x[i&1]);
  }
}

void func3() {
  int x[2] = {1e9+7, 2147483647};
  for(unsigned i=0; i<1000; ++i) {
    prime_number_student(&(x[i&1]));
  }
}

int main() {

  double sr = 0;
  unsigned n = 30;

  for(unsigned test=0; test<n; ++test) {
    double r = get_clock_diff(func1);
    sr += r;
  }
  printf("Function i*i <= n - average: %.9lf\n", sr / n);

  sr = 0;
  for(unsigned test=0; test<n; ++test) {
    double r = get_clock_diff(func2);
    sr += r;
  }
  printf("\nFunction sqrt average: %.9lf\n", sr / n);

  sr = 0;
  for(unsigned test=0; test<n; ++test) {
    double r = get_clock_diff(func3);
    sr += r;
  }
  printf("\nStep +2 average: %.9lf\n", sr / n);

  return 0;
}
