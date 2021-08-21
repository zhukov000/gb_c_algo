#ifndef THIN_HEAP_PQ
#define THIN_HEAP_PQ

/**
  insert      - 1
  extractMin  - log(n)
*/

#include<assert.h>

typedef struct {
  int priority;
  int value;
  int rank;
  int thinness;             // 1 for thin node, 0 for others

  struct THNode * child;  // first child (with max rank)
  struct THNode * right;  // right brother
  struct THNode * left;   // left brother or parent
} THNode;

typedef struct {
  THNode * first;         // root with min priority
  THNode * last;          // last root
} ThinHeap;

#define MAX_RANK 50
#define swap(Type, a, b) { \
              Type c = a; \
              a = b; \
              b = c; }

ThinHeap * makeTHeap() {
  ThinHeap * newHeap = (ThinHeap *) malloc(sizeof(ThinHeap));
  newHeap->first = 0;
  newHeap->last = 0;
  return newHeap;
}

THNode * makeTHNode(int value, int priority) {
  THNode * newNode = (THNode *) malloc(sizeof(THNode));
  newNode->value = value;
  newNode->priority = priority;
  newNode->rank = 0;
  newNode->thinness = 0;
  newNode->child = newNode->right = newNode->left = 0;
  return newNode;
}

int isThin(THNode* node) {
  if (node->rank == 1) {
    return node->child == 0;
  } else {
    return ((THNode*)node->child)->rank + 1 != node->rank;
  }
}

void insertTHeap(ThinHeap * heap, THNode * node) {
  if (heap->first == 0) {
    heap->first = node;
    heap->last = node;
  } else if (node->priority < heap->first->priority) {
    node->right = heap->first;
    heap->first->left = node;
    heap->first = node;
  } else {
    heap->last->right = node;
    node->left = heap->last;
    heap->last = node;
  }
}

THNode getMinTHeap(ThinHeap * heap) {
  assert(heap->first && "Try to get min element from empty heap");
  return *(heap->first);
}

ThinHeap* mergeTHeap(ThinHeap* h1, ThinHeap* h2) {
  if (h1->first == 0) {
    return h2;
  } else {
    if (h2->first == 0) {
      return h1;
    } else {
      if (h1->first->priority > h2->first->priority) {
        swap(ThinHeap*, h1, h2);
      }
      h1->last->right = h2->first;
      h2->first->left = h1->last;
      h1->last = h2->last;
      return h1;
    }
  }
}

THNode* extractMinTHeap(ThinHeap * heap) {
  if (heap->first == 0) return 0;

  THNode * tmp = heap->first;
  heap->first = heap->first->right;
  if (heap->first == 0) {
    heap->last = 0;
  } else {
    heap->first->left = 0;
  }
  // append his children to list and change rank
  THNode * x = tmp->child;
  while (x != 0) {
    if (isThin(x)) x->rank--;
    x->left = 0;
    THNode * next = x->right;
    x->left = x->right = 0;
    insertTHeap(heap, x);
    x = next;
  }
  // join all roots with same rank
  THNode * aux[MAX_RANK+1];
  for(unsigned i=0; i<=MAX_RANK; ++i) {
    aux[i] = 0;
  }
  int max = -1;
  x = heap->first;
  THNode * next = 0;
  while (x != 0) {
    while(aux[x->rank] != 0) {
      next = x->right;
      if (aux[x->rank]->priority < x->priority) {
        swap(THNode*, aux[x->rank], x);
      }
      aux[x->rank]->right = x->child;
      ((THNode*)x->child)->left = aux[x->rank];
      aux[x->rank]->left = x;
      x->child = aux[x->rank];
      aux[x->rank] = 0;
      x->rank ++;
    }
    aux[x->rank] = x;
    if (x->rank > max) max = x->rank;
    x = next;
  }
  free(heap);
  heap = makeTHeap();
  for(int i=0; i<=max; ++i) {
     insertTHeap(heap, aux[i]);
  }
  tmp->child = tmp->left = tmp->right = 0;
  return tmp;
}

void freeTHeap(ThinHeap * heap) {
  THNode * curRoot = heap->first;
  while(curRoot) {
    THNode * nxtRoot = curRoot->right;
    freeTHNode(curRoot);
    curRoot = nxtRoot;
  }
  free(heap);
}

void freeTHNode(THNode * node) {
  // free right brother
  if (node->right != 0) freeTHNode(node->right);
  // free childs
  if (node->child != 0) freeTHNode(node->child);
  free(node);
}

void DEBUG_PRINT_HEAP(ThinHeap * heap) {
  if (heap == 0) return;

  printf("Heap address = %d\n", heap);

  THNode * cur = heap->first;
  while (cur) {
    if (cur == heap->first) {
      DEBUG_PRINT_NODE(cur, "first root");
    } else if (cur == heap->last) {
      DEBUG_PRINT_NODE(cur, "last root");
    } else {
      DEBUG_PRINT_NODE(cur, "root");
    }
    cur = cur->right;
  }
  printf("\n");
}

void DEBUG_PRINT_NODE(THNode * node, const char * msg) {
  if (node == 0) return;

  printf("%s={val:%d, prior:%d, rank:%d, addr:%d, right:%d}\n",
         msg, node->value, node->priority, node->rank, node, node->right);
}


#endif // THIN_HEAP_PQ

