#ifndef LESSON6_GB
#define LESSON6_GB

#include<stdio.h>
#include<math.h>

#define swap(x,y) pSwap(&x, &y)

void pSwap(int *x, int *y) {
  int t = *x;
  *x = *y;
  *y = t;
}

void printArr(const int *arr, unsigned size) {
  for(unsigned i=0; i<size; ++i) {
    printf("%3d ", arr[i]);
  }
}

void bubbleSort(int *arr, unsigned size) {
  for(unsigned i=(int)size-1; i>0; --i) {
    for(unsigned j=0; j<i; ++j) {
      if (arr[j] > arr[j+1]) {
        swap(arr[j], arr[j+1]);
      }
    }
  }
}

// Trabb Pardo Knuth algorithm
void tpk_algo() {
  const int n = 11;
  const int threshold = 400;
  double arr[n];

  printf("\nInput %d real numbers: ", n);
  // read
  for(unsigned i=0; i<n; ++i) {
      scanf("%lf", arr+i);
  }
  // reverse
  for(unsigned i=0; i<n/2; ++i) {
      swap(arr[i], arr[n-1-i]);
  }
  // something meaningless
  for(unsigned i=0; i<n; ++i) {
    double x = sqrt(fabs(arr[i])) + 5 * pow(arr[i], 3);
    if (x > threshold) {
      printf("arr[%d] too large\n", i);
    } else {
      printf("arr[%d]=%.9lf\n", i, x);
    }
  }
}

#endif // LESSON6_GB
