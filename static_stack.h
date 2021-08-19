#ifndef STATIC_STACK
#define STATIC_STACK

#include<assert.h>

#define MAX_ST_SIZE 1000000

int staticStack[MAX_ST_SIZE];
int cntStack;

void initStack() {
  cntStack = 0;
}

int stackIsEmpty() {
  return cntStack == 0;
}

void stackPush(int value) {
  assert(cntStack < MAX_ST_SIZE && "Stack overflow");
  staticStack[cntStack++] = value;
}

int stackTop() {
  assert(cntStack > 0 && "Stack empty");
  return staticStack[cntStack-1];
}

int stackPop() {
  int v = stackTop();
  cntStack--;
  return v;
}

#endif // STATIC_STACK
