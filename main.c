/**
* azhukov
*/

#include"lesson2.h"
#include"lesson3.h"

int main() {

  helloWorld(); // lesson 2
  // lesson 3
  for (unsigned p = 0; p < 100; ++p) {
    printf("%2u - %c", p, isPrime(p) ? 'P' : ' ');
    printf(p % 10 == 9 ? "\n" : " ");
  }
  return 0;
}
