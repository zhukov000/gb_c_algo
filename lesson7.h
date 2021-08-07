#ifndef LESSON7_GB
#define LESSON7_GB

#include"linkedlist.h"

#include<stdio.h>

#define swap(x,y) pSwap(&x, &y)

void pSwap(int *x, int *y) {
  int t = *x;
  *x = *y;
  *y = t;
}

// partition Lomuto for quick sort
int qpartL(int * arr, int left, int right)
{
	int pivot = right - 1;
	int i = left;
	for (int j = left; j < right - 1; j++)
	{
		if ( arr[j] < arr[pivot] )
		{
			swap(arr[i], arr[j]);
			i++;
		}
	}
	swap(arr[i], arr[pivot]);
	return i;
}

// quick sort Lomuto recursive implementation [left; right]
void _qsortL(int * arr, int left, int right)
{
	if (left + 1 < right)
	{
		int pi = qpartL(arr, left, right);
		_qsortL(arr, left, pi);
		_qsortL(arr, pi + 1, right);
	}
}

// convinient interface for quick sort Lomuto
void qsortL(int * arr, unsigned size) {
  _qsortL(arr, 0, size);
}

// the recursive implementation for quick sort Hoare [left; right]
void _qsortH(int * arr, int left, int right) {
  int i = left;
  int j = right;

  // Hoare partition
  int x = arr[(left + right) / 2];
  do {
    while (arr[i] < x) ++i;
    while (arr[j] > x) --j;

    if (i <= j) {
      swap(arr[i], arr[j]);
      i++;
      j--;
    }
  } while (i <= j);

  if (j > left)
    _qsortH(arr, left, j);
  if (i < right)
    _qsortH(arr, i, right);
}

// convinient interface for quick sort Hoare
void qsortH(int * arr, unsigned size) {
  _qsortH(arr, 0, (int)size-1);
}

// insertion sort for subarray [left; right]
void _insertionSort(int * arr, int left, int right) {
  for(unsigned i=left; i<right; ++i) {
    for(int j=i+1; j>left && arr[j]<arr[j-1]; --j)
      swap(arr[j], arr[j-1]);
  }
}

// convinient interface for insertion sort
void insertionSort(int * arr, unsigned size) {
  _insertionSort(arr, 0, (int)size-1);
}

// improved quick sort
void _qsortImp(int * arr, int left, int right) {
  if (right - left < 10) {
    _insertionSort(arr, left, right);
  }
  else {
    // median
    int mid = (left + right) / 2;
    if ( arr[left] > arr[mid] ) swap(arr[left], arr[mid]);
    if ( arr[mid] > arr[right] ) {
      swap(arr[mid], arr[right]);
      if ( arr[left] > arr[mid] ) swap(arr[left], arr[mid]);
    }
    //
    int i = left;
    int j = right;
    int x = arr[mid];

    do {
      while (arr[i] < x) ++i;
      while (arr[j] > x) --j;

      if (i <= j) {
        swap(arr[i], arr[j]);
        i++;
        j--;
      }
    } while (i <= j);

    _qsortImp(arr, left, j);
    _qsortImp(arr, i, right);
  }
}

// convinient interface for improved quick sort
void qsortImpr(int * arr, unsigned size) {
  _qsortImp(arr, 0, (int)size - 1);
}

// merge array
void _merge(int * arr, int left, int mid, int right) {
  int l = left;
  int r = mid+1;
  int t = 0;
  int *a = (int*) malloc(sizeof(int) * (right-left+1));
  while(l <= mid && r <= right) {
      a[t++] = arr[l] < arr[r] ? arr[l++] : arr[r++];
  }
  while (l <= mid) a[t++] = arr[l++];
  while (r <= right) a[t++] = arr[r++];
  for(unsigned i=0; i<right-left+1; ++i) {
    arr[i + left] = a[i];
  }
  free(a);
}

// merge sort [left, right]
void _mergeSort(int * arr, int left, int right) {
  if (right > left) {
    int mid = (right + left) / 2;
    _mergeSort(arr, left, mid);
    _mergeSort(arr, mid+1, right);
    _merge(arr, left, mid, right);
  }
}

// convinient interface for merge sort
void mergeSort(int * arr, unsigned size) {
  _mergeSort(arr, 0, (int)size-1);
}

//
int findMax(int * arr, unsigned size) {
  int mx = arr[0];
  for(unsigned i=0; i<size; ++i) {
    if (arr[i] > mx) {
      mx = arr[i];
    }
  }
  return mx;
}

//
int findMin(int * arr, unsigned size) {
  int mn = arr[0];
  for(unsigned i=0; i<size; ++i) {
    if (arr[i] < mn) {
      mn = arr[i];
    }
  }
  return mn;
}

// counting sort
void countingSort(int * arr, unsigned size) {
  int min = findMin(arr, size);
  int max = findMax(arr, size);
  int len = max - min + 1;
  int * cnt = (int *) calloc(len, sizeof(int));
  for(unsigned i=0; i<size; ++i) {
    cnt[arr[i]-min]++;
  }
  int t = 0;
  for(unsigned  j=0; j < len; ++j) {
    while (cnt[j] > 0) {
      arr[t++] = j + min;
      cnt[j]--;
    }
  }
  free(cnt);
}

//
void bucketSortLst(int *arr, const unsigned size) {
  int numBuckets = 10;

  if (size / 100 > 10)  {
    numBuckets = size / 100;
  }
  // free all nodes
  cntAllocatedNodes = 0;

  int min = findMin(arr, size);
  int max = findMax(arr, size);
  int range = max - min + 1;

  linkedList buckets[numBuckets];

  for(unsigned i=0; i<numBuckets; ++i) {
    initList(&buckets[i]);
  }

  for(unsigned i=0; i<size; ++i) {
    int idx = (arr[i] - min) * numBuckets / range;
    addToList(&buckets[idx], arr[i]);
  }

  for(int i=0; i<numBuckets; ++i) {
    buckets[i].head = sortList(buckets[i].head, buckets[i].size);
  }

  unsigned t = 0;
  for(int i=0; i<numBuckets; ++i) {
    listNode * current = buckets[i].head;
    for (unsigned j=0; j<buckets[i].size; ++j) {
      arr[t++] = current->data;
      listNode * tmp = current;
      current = (listNode *) current->next;
      // free(tmp);
    }
  }
}

void bucketSortArr(int *arr, const unsigned size) {
  const int max = size;
  const int b = 10;

  int buckets[b][max+1];
  for(int i=0; i<b; ++i) {
    buckets[i][max] = 0;
  }

  for(int digit = 1; digit < 1000000000; digit *= 10) {
    for(int i=0; i < max; ++i) {
      int d = (arr[i] / digit) % b;
      buckets[d][buckets[d][max]] = arr[i];
      buckets[d][max]++;
    }
    int idx = 0;
    for(int i=0; i<b; ++i) {
      for(int j=0; j < buckets[i][max]; ++j) {
        arr[idx++] = buckets[i][j];
      }
      buckets[i][max] = 0;
    }
  }
}

void bucketSort(int *arr, const unsigned size) {
  if (size > 10000) return;
  bucketSortArr(arr, size);
}

//
void bucketSortLstOnlyEven(int *arr, const unsigned size) {
  int numBuckets = 10;

  if (size / 100 > 10)  {
    numBuckets = size / 100;
  }
  // free all nodes
  cntAllocatedNodes = 0;

  int min = findMin(arr, size);
  int max = findMax(arr, size);
  int range = max - min + 1;

  linkedList buckets[numBuckets];

  for(unsigned i=0; i<numBuckets; ++i) {
    initList(&buckets[i]);
  }

  for(unsigned i=0; i<size; ++i) {
    int idx = (arr[i] - min) * numBuckets / range;
    if (arr[i] % 2 == 0)
      addToList(&buckets[idx], arr[i]);
  }

  for(int i=0; i<numBuckets; ++i) {
    buckets[i].head = sortList(buckets[i].head, buckets[i].size);
  }

  unsigned t = 0;
  for(int i=0; i<numBuckets; ++i) {
    listNode * current = buckets[i].head;
    for (unsigned j=0; j<buckets[i].size; ++j) {
      while (arr[t] % 2 != 0) ++t;
      arr[t++] = current->data;
      listNode * tmp = current;
      current = (listNode *) current->next;
      // free(tmp);
    }
  }
}

// return 0, if not sorted
int checkSorted(int *arr, unsigned size) {
  for(int i=1; i<size; ++i) {
    if (arr[i] < arr[i-1])
      return 0;
  }
  return 1;
}

#endif // LESSON7_GB
