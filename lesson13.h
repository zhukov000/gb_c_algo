#include<stdio.h>

#include"dynamic_stack.h"

#define swap(Type, a, b) { \
              Type c = a; \
              a = b; \
              b = c; }

int**     genGraf(unsigned n, unsigned m);
int**     genOrientedGraf(unsigned n, unsigned m);
void      printAdj(int** graph, unsigned n);
void      freeGraf(int** adj, unsigned n);

int** genGraf(unsigned n, unsigned m) {
  if (m > n * (n - 1) / 2) {
    printf("Error: Too much edges\n");
    return 0;
  }

  int** adj = (int**)calloc(n, sizeof(int*));
  for(unsigned i=0; i<n; ++i) {
    adj[i] = (int*)calloc(n, sizeof(int));
  }

  while(m) {
    for(unsigned i=0; i<n && m; ++i) {
      for(unsigned j=i+1; j<n && m; ++j) {
        int v = rand() % 10 > 3 ? 1 : 0;
        if (v && !adj[i][j]) {
          adj[i][j] = adj[j][i] = v;
          m--;
        }
      }
    }
  }

  return adj;
}

int** genOrientedGraf(unsigned n, unsigned m) {
  if (m > n * (n - 1)) {
    printf("Error: Too much edges\n");
    return 0;
  }

  int** adj = (int**)calloc(n, sizeof(int*));
  for(unsigned i=0; i<n; ++i) {
    adj[i] = (int*)calloc(n, sizeof(int));
  }

  while(m) {
    for(unsigned i=0; i<n && m; ++i) {
      for(unsigned j=0; j<n && m; ++j) {
        if (i == j) continue;
        int v = rand() % 2;
        if (v && !adj[i][j]) {
          adj[i][j] = v;
          m--;
        }
      }
    }
  }

  return adj;
}

void printAdj(int** graph, unsigned n) {
  printf("\n");
  for(unsigned i=0; i<n; ++i) {
    for(unsigned j=0; j<n; ++j) {
      printf(" %d", graph[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void freeGraf(int** adj, unsigned n) {
  for(unsigned i=0; i<n; ++i) {
    free(adj[i]);
  }
  free(adj);
}

void dfs(int** g, int* visited, int u, unsigned n) {
  printf("%u -> ", u);
  visited[u] = 1;
  for(unsigned v=0; v<n; ++v) {
    if (g[u][v] && !visited[v]) {
      dfs(g, visited, v, n);
    }
  }
}

void task1() {
  const int n = 5;
  const int m = 7;

  int** g1 = genGraf(n, m);
  printAdj(g1, n);

  printf("DFS use stack:\n");
  Stack* st = initStack();
  int* visited = (int*)calloc(n, sizeof(int));
  for(unsigned v=0; v<n; ++v) {
    if (!visited[v]) {
      pushStack(st, v);
      while (st->stackSize > 0) {
        unsigned i = popStack(st);
        if (visited[i]) continue;
        printf("%u -> ", i);
        visited[i] = 1;
        for(unsigned j=0; j<n; ++j) {
          if (g1[i][j]) {
            pushStack(st, j);
          }
        }
      }
      printf("x\n");
    }
  }
  free(visited);

  printf("DFS use recursion (system stack):\n");
  visited = (int*)calloc(n, sizeof(int));
  for(unsigned v=0; v<n; ++v) {
    if (!visited[v]) {
      dfs(g1, visited, 0, n);
    }
  }
  printf("x\n");
  free(visited);

  freeGraf(g1, n);
}

//
// sort pair below
// ----------------------------------------

typedef struct {
  int first;
  int second;
} PairInt;

int lePair(const PairInt * left, const PairInt * right) {
  return (left->first < right->first) || (left->first == right->first && left->second < right->second);
}

int leqPair(const PairInt * left, const PairInt * right) {
  return (left->first <= right->first);
}

void siftDownPair(PairInt *arr, int i, int size) {
  PairInt newElem = arr[i];
  while(2 * i + 1 < size) {
    int child = 2 * i + 1;
    // choose max from children
    if (child + 1 < size && lePair(arr + child, arr + (child + 1))) {
      ++child;
    }
    if (leqPair(arr + child, &newElem)) break;

    arr[i] = arr[child];
    i = child;
  }
  arr[i] = newElem;
}

void heapPairSort(PairInt *arr, int size) {
  for(int i=size/2-1; i>=0; --i) {
    siftDownPair(arr, i, size);
  }
  for(int i=size-1; i>0; --i) {
    swap(PairInt, arr[0], arr[i]);
    siftDownPair(arr, 0, i);
  }
}

// ----------------------------------------

void printPairArr(const PairInt* cntIn, int n) {
  for(int i=n-1; i>=0; --i) {
    printf("vertex %d income %d\n", cntIn[i].second, cntIn[i].first);
  }
}

void countIncome(int v, int* visited, int** g, PairInt* cntIn, unsigned n) {
  visited[v] = 1;
  for(unsigned u=0; u<n; ++u) {
    if (g[u][v]) {
      cntIn[v].first++;
      if (!visited[u]) {
        countIncome(u, visited, g, cntIn, n);
      }
    }
  }
}

void task2() {
  const int n = 10;
  const int m = 60;

  int** g2 = genOrientedGraf(n, m);
  printAdj(g2, n);

  PairInt* cntIn1 = (PairInt*)malloc(n * sizeof(PairInt));
  PairInt* cntIn2 = (PairInt*)malloc(n * sizeof(PairInt));
  for(unsigned i=0; i<n; ++i) {
    cntIn1[i].first = cntIn2[i].first = 0;
    cntIn1[i].second = cntIn2[i].second = i;
  }

  for(unsigned i=0; i<n; ++i) {
    for(unsigned j=0; j<n; ++j) {
      if (g2[i][j]) {
        cntIn1[j].first++;
      }
    }
  }
  heapPairSort(cntIn1, n);
  printf("By adjacent matrix:\n");
  printPairArr(cntIn1, n);

  int* visited = (int*)calloc(n, sizeof(int));
  for(unsigned u=0; u<n; ++u) {
    if (!visited[u]) {
      countIncome(u, visited, g2, cntIn2, n);
    }
  }
  free(visited);

  heapPairSort(cntIn2, n);
  printf("Use recursion:\n");
  printPairArr(cntIn2, n);

  freeGraf(g2, n);
  free(cntIn1);
  free(cntIn2);
}
