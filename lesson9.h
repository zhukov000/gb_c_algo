#ifndef GB_LESSON9
#define GB_LESSON9

#include<stdlib.h>

#include"static_stack.h"
#include"naive_priority_queue.h"
#include"heap_priority_queue.h"
#include"thin_heap_priority_queue.h"

#define SEED 1234
#define PQ_CHECK_CNT 10

// show tree struct after change
#define DEBUG_THIN_HEAP

void convertToBin(int x) {
  assert(x > 0 && "Can convert only positive number");

  printf("%d=", x);

  initStack();
  while(x > 0) {
    stackPush(x & 1);
    x >>= 1;
  }

  while(!stackIsEmpty()) {
    printf("%d", stackPop());
  }
  printf("\n");
}

void checkThinHeapPQ() {
  srand(SEED);

  printf("priority queue based on thin heap:\n\n");
  ThinHeap * heap = makeTHeap();

  for(unsigned i=0; i<2*PQ_CHECK_CNT; ++i) {
    if (heap->first == 0 || rand() % 2) {
      THNode* node = makeTHNode(rand() % 100, rand() % 100);
      printf("+ insert value=%2d priority=%2d\n", node->value, node->priority);
      insertTHeap(heap, node);
    } else {
      THNode* node = extractMinTHeap(heap);
      printf("- extract value=%2d priority=%2d\n", node->value, node->priority);
    }
#ifdef DEBUG_THIN_HEAP
    DEBUG_PRINT_HEAP(heap);
#endif // DEBUG_THIN_HEAP
  }

  THNode * node = extractMinTHeap(heap);
  while (node != 0) {
    printf("- extract value=%2d priority=%2d\n", node->value, node->priority);
    node = extractMinTHeap(heap);
  }

  freeTHeap(heap);
}

void checkHeapPQ() {
  srand(SEED);

  printf("priority queue based on heap:\n\n");
  heapHPQ_init();

  for(unsigned i=0; i<PQ_CHECK_CNT; ++i) {
    NodeHPQ node;
    node.value = rand() % 100;
    node.priority = rand() % 100;
    printf("insert value=%2d priority=%2d\n", node.value, node.priority);
    heapHPQ_insert(node);
  }

  printf("\n");
  while (heapHPQSize) {
    NodeHPQ node = heapHPQ_extractMin();
    printf("extract value=%2d priority=%2d\n", node.value, node.priority);
  }
  printf("\n");
}

void checkNaivePQ() {
  srand(SEED);

  printf("priority queue based on array - naive extract:\n\n");
  heapNPQ_init();

  for(unsigned i=0; i<PQ_CHECK_CNT; ++i) {
    NodeNPQ node;
    node.value = rand() % 100;
    node.priority = rand() % 100;
    printf("insert value=%2d priority=%2d\n", node.value, node.priority);
    heapNPQ_insert(node);
  }

  printf("\n");
  while ( heapNPQfirst <= heapNPQlast ) {
    NodeNPQ node = heapNPQ_extractMin();
    printf("extract value=%2d priority=%2d\n", node.value, node.priority);
  }
  printf("\n");
}

#endif // GB_LESSON9
