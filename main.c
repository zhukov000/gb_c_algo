#include"lesson7.h"

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef void(*IntSortFunc)(int*, unsigned);

unsigned seed = 0;

void printArr(const int * arr, const unsigned size) {
  for(unsigned i=0; i<size; ++i) {
    printf("%2d ", arr[i]);
  }
  printf("\n");
}

void checkSort(IntSortFunc sortFun) {
  const int n = 10;
  int arr[n];

  srand(seed);
  for(unsigned i=0; i<n; ++i) {
    arr[i] = rand() % 99 + 1;
  }

  printf("Before sort: ");
  printArr(arr, n);

  sortFun(arr, n);

  printf("After sort: ");
  printArr(arr, n);
}

int main() {

  seed = time(NULL);

  printf("\nQuick sort Hoare: \n"); checkSort(qsortH);
  printf("\nQuick sort Luomo: \n"); checkSort(qsortL);

  return 0;
}
