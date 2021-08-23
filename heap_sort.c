#include"heap_sort.h"

void siftDown(int *arr, int i, int size) {
  int newElem = arr[i];
  while(2 * i + 1 < size) {
    int child = 2 * i + 1;
    // choose max from children
    if (child + 1 < size && arr[child] < arr[child + 1])
      ++child;
    if (newElem >= arr[child]) break;

    arr[i] = arr[child];
    i = child;
  }
  arr[i] = newElem;
}

void heapSort(int *arr, int size) {
  for(int i=size/2-1; i>=0; --i) {
    siftDown(arr, i, size);
  }
  for(int i=size-1; i>0; --i) {
    swap(int, arr[0], arr[i]);
    siftDown(arr, 0, i);
  }
}
