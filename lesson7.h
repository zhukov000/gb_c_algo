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
		int pi = qpart(arr, left, right);
		qsL(arr, left, pi);
		qsL(arr, pi + 1, right);
	}
}

// qsort Hoare
void qs() {

}

// block sort
void bsort(int *a, const unsigned size) {

}

#endif // LESSON7_GB
