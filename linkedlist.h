#ifndef LIST_GB
#define LIST_GB

#include<malloc.h>

typedef struct {
  int data;
  void * next;
} listNode;

typedef struct {
  listNode* head;
  unsigned size;
} linkedList;

unsigned cntAllocatedNodes = 0;
listNode memoryNodes[1000000];

listNode *allocateNode() {
  return &(memoryNodes[cntAllocatedNodes++]);
}

void initList(linkedList * pLst) {
  pLst->head = 0;
  pLst->size = 0;
}

listNode* newlistNode(int value) {
  listNode* r = allocateNode(); // (listNode *) malloc(sizeof(listNode));
  r->data = value;
  r->next = 0;
  return r;
}

// add to head
void addToList(linkedList* pLst, int value) {
  listNode * newHead = newlistNode(value);
  newHead->next = pLst->head;
  pLst->head = newHead;
  pLst->size++;
}

//
listNode* sortList(listNode* head, unsigned size) {
  if (size < 2) return head;

  listNode* mid = head;

  unsigned leftCnt = size/2+size%2;
  unsigned rightCnt = size - leftCnt;

  for(unsigned i=0; i<leftCnt; ++i) mid = mid->next;

  head = sortList(head, leftCnt);
  mid = sortList(mid, rightCnt);

  listNode* left = head;
  listNode* right = mid;

  head = 0;
  listNode* cur = 0;
  // merge
  while ((leftCnt > 0) || (rightCnt > 0)) {
    if ((rightCnt == 0) || ((leftCnt > 0) && (left->data < right->data))) {
      if (!cur) {
        head = cur = left;
      } else {
        cur->next = left;
        cur = left;
      }
      left = left->next;
      leftCnt--;
    } else {
      if (!cur) {
        head = cur = right;
      } else {
        cur->next = right;
        cur = right;
      }
      right = right->next;
      rightCnt--;
    }
  }
  return head;
}

#endif // LIST_GB
