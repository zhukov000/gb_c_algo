
#include"lesson6.h"

int main () {

  // example bubble 1d sort
  const unsigned n = 9;
  int arr[] = {1,9,2,5,7,6,4,3,8};
  bubbleSort(arr, n);
  printArr(arr, n);
  printf("\n\n");

  // example bubble 2d sort
  int** arr2 = init2dArr(n, n);
  fill2dArr(arr2, n, n);
  bubble2dSort(arr2, n, n);
  print2dArr(arr2, n, n);
  free2dArr(arr2, n);

  // Trabb Pardo Knuth algorithm
  tpk_algo();

  return 0;
}
