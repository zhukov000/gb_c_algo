#ifndef LESSON4_GB
#define LESSON4_GB

#define ABS(x) (x < 0 ? -x : x)
#define WALL 1
#define EMPTY 0
#define THRESHOLD 30000

#include<assert.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

// interface: convert orig to res, return length
unsigned conv(unsigned orig, unsigned base, char * res, unsigned i);
// interface: a power b
double power(double a, signed b);
// interface: a power b
double power_dummy(double a, signed b);
// init random matrix 0 and 1
void init01(unsigned n, unsigned m, int* arr);
// print matrix
void print(unsigned n, unsigned m, const int* arr);
// recursive search numbers of routes chess king from (0,0) to (n-1,m-1) with hurdles
unsigned search_r(unsigned i, unsigned j, unsigned n, unsigned m, const int* arr);
// DP search
unsigned search_dp(unsigned n, unsigned m, const int* arr);

// recursive implementation
unsigned conv(unsigned orig, unsigned base, char * res, unsigned i) {

  assert(base > 1 && base < 37 && "Impossible base for convert");

  if (orig == 0) {
    if (i == 0) {
        res[i] = '0';
        i++;
    }
    res[i] = 0; // string terminate
    return i;
  }

  unsigned digit = orig % base;
  unsigned len = conv(orig / base, base, res, i + 1);
  res[len - 1 - i] = digit > 9 ? (char)('A' + digit - 10) : (char)('0' + digit);

  return len;
}

// power implementation for signed b with using binary divison
double power(double a, int b) {
  if (b == 0) return 1;

  if (b % 2 != 0) {
    double c = a * power(a, ABS(b) - 1);
    return b > 0 ? c : 1 / c;
  }

  double c = power(a, ABS(b) / 2);
  return b > 0 ? c * c : 1 / c / c;
}

// power implementation for signed b with using recursion
double power_dummy(double a, signed b) {
  if (b == 0) return 1;

  if (b < 0)
    return 1 / power_dummy(a, ABS(b));

  return a * power_dummy(a, b - 1);
}

void init01(unsigned n, unsigned m, int* arr) {
  srand(time(0));
  for(unsigned i=0; i<n; ++i) {
    for(unsigned j=0; j<m; ++j) {
      arr[i * m + j] = (rand() % (1 << 16) > THRESHOLD ? WALL: EMPTY);
    }
  }
  // first and last always reachable
  arr[0] = arr[n*m-1] = 0;
}

void print(unsigned n, unsigned m, const int* arr) {
  for(unsigned i=0; i<n; ++i) {
    for(unsigned j=0; j<m; ++j) {
      printf("%2d", arr[i*m+j]);
    }
    printf("\n");
  }
}

unsigned search_r(unsigned i, unsigned j, unsigned n, unsigned m, const int* arr) {
  if (i == 0 || j == 0)
    return 1;
  if (arr[i*m+j] == 1)
    return 0;
  return search_r(i-1, j, n, m, arr) + search_r(i, j-1, n, m, arr);
}

unsigned search_dp(unsigned n, unsigned m, const int* arr) {
  // dp - array for store count of routes
  unsigned **dp;
  // allocate memory for dp
  dp = (unsigned **) malloc(sizeof(unsigned *) * n);
  for(unsigned i=0; i<n; ++i) {
    dp[i] = (unsigned *) calloc(m, sizeof(unsigned)); // calloc set zeroes
  }
  // calc the answer
  for(unsigned i=0; i<n; ++i) {
    for(unsigned j=0; j<m; ++j) {
      if (i == 0 || j == 0) {
        dp[i][j] = 1;
      }
      else if (arr[i*m+j] == 1) {
        dp[i][j] = 0;
      }
      else {
        dp[i][j] = dp[i-1][j] + dp[i][j-1];
      }
    }
  }
  unsigned ans = dp[n-1][m-1]; // save the answer

  // free memory
  for(unsigned i=0; i<n; ++i) {
    free(dp[i]);
  }
  free(dp);

  return ans;
}

#endif // LESSON4_GB

