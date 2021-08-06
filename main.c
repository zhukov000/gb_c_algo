
#include"lesson6.h"

int main () {

  // example bubble 1d sort
  const unsigned n = 9;
  int arr[] = {1,9,2,5,7,6,4,3,8};
  bubbleSort(arr, n);
  printArr(arr, n);
  printf("\n\n");

  // example bubble 1d sort for 2d array -
  // for static array can using 1d array functions
  int arr1[3][3] = {1,9,2,5,7,6,4,3,8};
  bubbleSort(arr1, n);
  for(unsigned i=0; i<3; ++i) {
    for(unsigned j=0; j<3; ++j) {
      printf("%2d ", arr1[i][j]);
    }
    printf("\n");
  }
  printf("\n\n");

  // example bubble 2d sort dynamic array
  int** arr2 = init2dArr(n, n);
  fill2dArr(arr2, n, n);
  bubble2dSort(arr2, n, n);
  print2dArr(arr2, n, n);
  free2dArr(arr2, n);

  // Trabb Pardo Knuth algorithm
  tpk_algo();

  return 0;
}
