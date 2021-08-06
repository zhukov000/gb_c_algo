#ifndef LESSON7_GB
#define LESSON7_GB

#define swap(x,y) pSwap(&x, &y)

void pSwap(int *x, int *y) {
  int t = *x;
  *x = *y;
  *y = t;
}

// qsort partition Lomuto
int qpL(int * arr, int left, int right)
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

// qsort Lomuto
void qsL(int * arr, int left, int right)
{
	if (left + 1 < right)
	{
		int pi = qpL(arr, left, right);
		qsL(arr, left, pi);
		qsL(arr, pi + 1, right);
	}
}

void qsortL(int * arr, unsigned size) {
  qsL(arr, 0, size);
}

// qsort Hoare subarr: arr[left:right]
void qsH(int * arr, int left, int right) {
  int i = left;
  int j = right;
  int x = arr[(left + right) / 2];

  // qsort partition Hoare
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
    qsH(arr, left, j);
  if (i < right)
    qsH(arr, i, right);
}

void qsortH(int * arr, unsigned size) {
  qsH(arr, 0, (int)size-1);
}

// block sort
void bsort(int *a, const unsigned size) {

}

#endif // LESSON7_GB
