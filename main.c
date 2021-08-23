#include "stdio.h"
#include "lesson9.h"

int main() {
  convertToBin(123);
  convertToBin(17);

  checkNaivePQ();
  checkHeapPQ();
  checkThinHeapPQ();
}
