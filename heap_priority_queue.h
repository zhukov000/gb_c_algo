#ifndef HEAP_PQ
#define HEAP_PQ

/**
  insert      - log(n)
  extractMin  - log(n)
*/

#include<assert.h>

#define MAX_HEAP_PQ_SIZE 1000000

typedef struct {
  int priority;
  int value;
} NodeHPQ;

NodeHPQ heapHPQ[MAX_HEAP_PQ_SIZE];
int heapHPQSize;

void swapInt(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void swapNodeHPQ(NodeHPQ *a, NodeHPQ *b) {
  swapInt(&(a->priority), &(b->priority));
  swapInt(&(a->value), &(b->value));
}

void heapHPQ_init() {
  heapHPQSize = 0;
}

int hle(int hleft, int right) {
  return heapHPQ[hleft].priority < heapHPQ[right].priority;
}

int hleq(int hleft, int right) {
  return heapHPQ[hleft].priority <= heapHPQ[right].priority;
}

void heapHPQ_siftDown(int i) {
  while(2*i+1 < heapHPQSize) {
    int hleft  = 2*i+1;
    int right = 2*i+2;
    int j = hleft;
    if (right < heapHPQSize && hle(right, hleft)) {
      j = right;
    }
    if (hleq(i, j)) break;
    swapNodeHPQ(heapHPQ + i, heapHPQ + j);
    i = j;
  }
}

void heapHPQ_siftUp(int i) {
  while(hle(i, i/2)) {
    swapNodeHPQ(heapHPQ + i, heapHPQ + i / 2);
    i = i / 2;
  }
}

void heapHPQ_insert(NodeHPQ node) {
  assert(heapHPQSize + 1 < MAX_HEAP_PQ_SIZE && "Heap overflow");

  heapHPQ[heapHPQSize] = node;
  heapHPQ_siftUp(heapHPQSize++);
}

NodeHPQ heapHPQ_extractMin() {
  NodeHPQ ans = heapHPQ[0];
  heapHPQ[0] = heapHPQ[--heapHPQSize];
  heapHPQ_siftDown(0);
  return ans;
}

#endif // HEAP_PQ
