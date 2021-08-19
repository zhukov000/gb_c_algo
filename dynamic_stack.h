#ifndef DYNAMIC_STACK_GB
#define DYNAMIC_STACK_GB

#include"malloc.h"
#include"assert.h"

typedef char StackData;

typedef struct {
  StackData data;
  struct StackFrame* prev;
} StackFrame;

StackFrame* stackTop;
unsigned stackSize;

void initStack() {
  stackSize = 0;
  stackTop = 0;
}

void pushStack(StackData val) {
  StackFrame* newFrame = (StackFrame *)malloc(sizeof(StackFrame));
  newFrame->data = val;
  newFrame->prev = stackTop;
  stackTop = newFrame;
  stackSize++;
}

StackData topStack() {
  assert(stackSize && "Stack is empty, buddy");
  return stackTop->data;
}

StackData popStack() {
  StackData retValue = topStack();
  stackSize--;
  StackFrame * tmp = stackTop;
  stackTop = stackTop->prev;
  free(tmp);
  return retValue;
}

void freeStack() {
  while (stackTop) {
    popStack();
  }
}

#endif // DYNAMIC_STACK_GB
