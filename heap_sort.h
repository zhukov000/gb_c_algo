#ifndef HEAP_SORT
#define HEAP_SORT

#define swap(Type, a, b) { \
              Type c = a; \
              a = b; \
              b = c; }

void heapSort(int *arr, int size);



#endif // HEAP_SORT
