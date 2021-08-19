#ifndef NAIVE_PQ
#define NAIVE_PQ

/**
  insert      - 1
  extractMin  - n
*/

#include<assert.h>

#define MAX_HEAP_PQ_SIZE 1000000

typedef struct {
  int priority;
  int value;
} NodeNPQ;

NodeNPQ heapNPQ[MAX_HEAP_PQ_SIZE];
int heapNPQlast, heapNPQfirst;

void heapNPQ_init() {
  heapNPQlast = -1;
  heapNPQfirst = 0;
}

int nle(int nleft, int right) {
  return heapNPQ[nleft].priority < heapNPQ[right].priority;
}

int nleq(int nleft, int right) {
  return heapNPQ[nleft].priority <= heapNPQ[right].priority;
}

int inc(int i) {
  return (i + 1) % MAX_HEAP_PQ_SIZE;
}

void heapNPQ_insert(NodeNPQ node) {
  assert(heapNPQlast - heapNPQfirst + 1 < MAX_HEAP_PQ_SIZE && "Heap overflow");

  heapNPQlast = inc(heapNPQlast);
  heapNPQ[heapNPQlast] = node;
}

NodeNPQ heapNPQ_extractMin() {
  assert(heapNPQfirst <= heapNPQlast && "Heap empty");

  int imin = heapNPQfirst;
  for(unsigned i=heapNPQfirst+1; i <= heapNPQlast; ++i) {
    if (nle(i % MAX_HEAP_PQ_SIZE, imin % MAX_HEAP_PQ_SIZE)) {
      imin = i;
    }
  }

  NodeNPQ ans = heapNPQ[imin % MAX_HEAP_PQ_SIZE];

  for(unsigned i=imin; i>heapNPQfirst; --i) {
    heapNPQ[i % MAX_HEAP_PQ_SIZE] = heapNPQ[(i-1) % MAX_HEAP_PQ_SIZE];
  }
  heapNPQfirst++;

  return ans;
}

#endif // NAIVE_PQ

