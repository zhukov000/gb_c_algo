#ifndef LIST_GB
#define LIST_GB

#include<malloc.h>

typedef struct {
  int data;
  void* next;
} ListNode;

typedef struct {
  ListNode* head;
  unsigned size;
} LinkedList;

void initList(LinkedList * pLst) {
  pLst->head = 0;
  pLst->size = 0;
}

ListNode* newListNode(int value) {
  ListNode* r = (ListNode *) malloc(sizeof(ListNode));
  r->data = value;
  r->next = 0;
  return r;
}

// add to head
void addToList(LinkedList* pLst, int value) {
  ListNode * newHead = newListNode(value);
  newHead->next = pLst->head;
  pLst->head = newHead;
  pLst->size++;
}

//
ListNode* sortList(ListNode* head, unsigned size) {
  if (size < 2) return head;

  ListNode* mid = head;

  unsigned leftCnt = size/2+size%2;
  unsigned rightCnt = size - leftCnt;

  for(unsigned i=0; i<leftCnt; ++i) mid = mid->next;

  head = sortList(head, leftCnt);
  mid = sortList(mid, rightCnt);

  ListNode* left = head;
  ListNode* right = mid;

  head = 0;
  ListNode* cur = 0;
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
    cur->next = 0;
  }
  return head;
}

void sort(LinkedList * lst) {
  lst->head = sortList(lst->head, lst->size);
}

void freeList(LinkedList * lst) {
  lst->size = 0;
  while(lst->head) {
    ListNode * tmp = lst->head;
    lst->head = lst->head->next;
    free(tmp);
  }
}

// -1 - descending order
//  1 - ascending order (as default value for one-element list and for empty list)
//  0 - not sorted
int isSorted(const LinkedList * lst) {
  ListNode * cur = lst->head;

  unsigned cntAsc = 0;
  unsigned cntDesc = 0;

  while(cur->next) {

    if (cur->data < ((ListNode *)cur->next)->data) ++cntAsc;
    if (cur->data > ((ListNode *)cur->next)->data) ++cntDesc;
    cur = cur->next;
  }

  if (cntAsc && cntDesc) return 0;
  else if (cntDesc) return -1;
  else return 1;
}

unsigned copyList(const LinkedList * src, LinkedList * dst) {
  unsigned cnt = 0;
  freeList(dst);

  ListNode * cur = src->head;
  while (cur) {
    addToList(dst, cur->data);
    cur = cur->next;
  }
  return dst->size;
}

void printList(const LinkedList * lst) {
  printf("List size = %u, elements:", lst->size);

  ListNode * cur = lst->head;
  while (cur) {
    printf(" %d", cur->data);
    cur = cur->next;
  }
  printf("\n");
}

#endif // LIST_GB
