#include"lesson7.h"
#include"time_measure.h"

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

unsigned seed = 0;

void printArr(const int * arr, const unsigned size) {
  for(unsigned i=0; i<size; ++i) {
    printf("%2d ", arr[i]);
  }
  printf("\n");
}

// fill array random numbers [1, base]
void fillArr(int * arr, const unsigned size, unsigned base) {
  srand(seed);
  for(unsigned i=0; i<size; ++i) {
    arr[i] = rand() % base + 1;
  }
}

void sortResult(IntSortFunc sortFun) {
  const int n = 20;
  const int b = 99;

  int arr[n];
  fillArr(arr, n, b);

  printf("Before sort: ");
  printArr(arr, n);

  sortFun(arr, n);

  printf("After sort:  ");
  printArr(arr, n);
}

/**
  For different sizes (10, 100, 1000 ... 1e5) gen array with different base (10, 100, 1000 ... 1e6)
  and sort with sortFun for TestCnt times
*/
void sortCheck(IntSortFunc sortFun) {
  const int TestCnt = 30;

  for(unsigned size=10; size<1e6-1; size *= 10) {
    double sumRes = 0;
    unsigned cnt = 0;
    for(unsigned base=10; base<1e7-1; base *= 10) {
      for(unsigned test=0; test<TestCnt; ++test){
        int * arr = (int *) malloc(sizeof(int) * size);
        seed += base + test;
        fillArr(arr, size, base);

        sumRes += get_clock_diff_sort(sortFun, arr, size);
        if (!checkSorted(arr, size)) {
            printf(" FAIL \n");
            return;
        }
        cnt++;
        free(arr);

        if (sumRes > cnt) break; // if too slow then break
      }
      if (sumRes > cnt) break; // if too slow then break
    }
    if (sumRes > cnt) {
      printf(" more 1 s. |");
    }
    else {
        printf("%10.6lf |", sumRes / cnt);
    }
  }
  printf("\n");
}

int main() {

  seed = time(NULL);

  printf("\nInsertion sort: \n"); sortResult(insertionSort);
  printf("\nQuick sort Hoare: \n"); sortResult(qsortH);
  printf("\nQuick sort Luomo: \n"); sortResult(qsortL);
  printf("\nImproved quick sort: \n"); sortResult(qsortImpr);
  printf("\nMerge sort: \n"); sortResult(mergeSort);
  printf("\nCounting sort: \n"); sortResult(countingSort);
  printf("\nBucket sort (array): \n"); sortResult(bucketSort);
  printf("\nBucket sort (list): \n"); sortResult(bucketSortLst);

  printf("\n");
  printf("    Sort name   |%10d |%10d |%10d |%10d |%10d |\n", 10, 100, 1000, 10000, 100000);
  printf(" Insertion sort |"); sortCheck(insertionSort); // TOO SLOW
  printf(" qsort Luomo    |"); sortCheck(qsortL);
  printf(" qsort Hoare    |"); sortCheck(qsortH);
  printf(" Improved qsort |"); sortCheck(qsortImpr);
  printf(" Merge sort     |"); sortCheck(mergeSort);
  printf(" Counting sort  |"); sortCheck(countingSort);
  printf(" Buckets (arr)  |"); sortCheck(bucketSort);
  printf(" Buckets (list) |"); sortCheck(bucketSortLst);

  printf("Sort only even:\n");
  sortResult(bucketSortLstOnlyEven);

  return 0;
}
