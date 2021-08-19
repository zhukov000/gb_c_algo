#ifndef LESSON10_GB
#define LESSON10_GB

#define LIST_SIZE 10

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"dynamic_stack.h"
#include"linkedlist.h"

int isCorrect(char* sequence) {
  int result = 1;

  initStack();
  for(unsigned i=0; sequence[i]; ++i) {
    if (sequence[i] == '(') pushStack(')');
    else if (sequence[i] == '[') pushStack(']');
    else if (sequence[i] == '{') pushStack('}');
    else if (sequence[i] == ')' || sequence[i] == ']' || sequence[i] == '}') {
      if ( !stackSize || popStack() != sequence[i] ) {
        result = 0;
        break;
      }
    }
    else {
      printf("\nERROR: Restricted character in input sequence (input only brackets)\n");
      result = 0;
      break;
    }
  }
  if (stackSize) result = 0;
  freeStack();

  return result;
}

void listProcessing() {
  printf("\nList processing:\n");
  printf("create empty list A\n");
  LinkedList A; initList(&A);

  printf("add %d random numbers to A: ", LIST_SIZE);
  for(unsigned i=0; i<LIST_SIZE; ++i) {
    addToList(&A, rand() % 10);
  }
  printList(&A);

  LinkedList B; initList(&B);
  unsigned k = copyList(&A, &B);
  printf("create list B as copy list A: %d elements were copy\n", k);
  printf("sort list B by ascending value\n"); sort(&B);

  printf("A:"); printList(&A);
  printf("B:"); printList(&B);

  printf("check sort A %d\n", isSorted(&A));
  printf("check sort B %d\n", isSorted(&B));

  // free
  freeList(&A);
  freeList(&B);
}

void checkStack() {
  initStack();
  pushStack('a');
  pushStack('b');
  pushStack('c');

  while(stackTop) {
    printf("%c", popStack());
  }
  freeStack();
}
#endif // LESSON10_GB
