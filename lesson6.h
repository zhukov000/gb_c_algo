#ifndef LESSON6_GB
#define LESSON6_GB

#include<stdio.h>
#include<math.h>
#include<malloc.h>
#include<time.h>

#define swap(x,y) pSwap(&x, &y)
#define E(a,i,r) a[(i)/(r)][(i)%(r)]

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

int** init2dArr(unsigned rows, unsigned cols) {
  int** arr = (int**)malloc(sizeof(int*) * rows);
  for(unsigned irow=0; irow<rows; ++irow) {
    arr[irow] = (int*)calloc(sizeof(int), cols);
  }
  return arr;
}

void free2dArr(int** arr, unsigned rows) {
  for(unsigned irow=0; irow<rows; ++irow) {
    free(arr[irow]);
  }
  free(arr);
}

void fill2dArr(int** arr, unsigned rows, unsigned cols) {
  srand(time(0));
  for(unsigned irow=0; irow<rows; ++irow) {
    for(unsigned icol=0; icol<cols; ++icol) {
        arr[irow][icol] = rand() % 100;
    }
  }
}

void print2dArr(const int **arr, unsigned rows, unsigned cols) {
  for(unsigned irow=0; irow<rows; ++irow) {
    for(unsigned icol=0; icol<cols; ++icol) {
      printf("%3d ", arr[irow][icol]);
    }
    printf("\n");
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

void bubble2dSort(int **arr, unsigned r, unsigned c) {
  unsigned size = r * c;
  for(unsigned i=(int)size-1; i>0; --i) {
    for(unsigned j=0; j<i; ++j) {
      if (E(arr,j,r) > E(arr,j+1,r)) {
        swap(E(arr,j,r), E(arr,j+1,r));
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
