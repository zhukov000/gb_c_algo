
#include"lesson6.h"

int main () {

  // example bubble sort
  const unsigned n = 9;
  int arr[] = {1,9,2,5,7,6,4,3,8};
  bubbleSort(arr, n);
  printArr(arr, n);

  // Trabb Pardo Knuth algorithm
  tpk_algo();

  return 0;
}
