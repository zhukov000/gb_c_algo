/**
* azhukov
*/

#include"lesson2.h"
#include"lesson3.h"
#include"lesson4.h"

int main() {

  helloWorld(); // lesson 2

  // lesson 3
  printf("\n");
  for (unsigned p = 0; p < 100; ++p) {
    printf("%2u - %c", p, isPrime(p) ? 'P' : ' ');
    printf(p % 10 == 9 ? "\n" : " ");
  }

  // lesson 4
  printf("\n");
  unsigned n = 123;
  for(unsigned base = 2; base < 17; ++base) {
    char buffer[33] = "0";
    conv(n, base, buffer, 0);
    printf("%u in %u = %s\n", n, base, buffer);
  }
  printf("\n");
  for(int i=-5; i<=5; ++i) {
    printf("2^%d = %.3lf\n", i, power(2., i));
  }
  printf("\n");

  const unsigned N = 13;
  const unsigned M = 25;
  int board[N][M];

  // random initialize
  init01(N, M, board);
  // print
  print(N, M, board);
  // search
  printf("\n");

  unsigned ans = search_r(N-1, M-1, N, M, board);
  printf("Result of recursive search = %d\n", ans); // slow

  ans = search_dp(N, M, board);
  printf("Result of search with using DP optimization = %d\n", ans); // fast

  return 0;
}
