#include "dynamic_stack.h"

Stack* initStack() {
  Stack* st = (Stack*)malloc(sizeof(Stack));
  st->stackSize = 0;
  st->top = 0;
  return st;
}

void pushStack(Stack* stack, StackData val) {
  StackFrame* newFrame = (StackFrame*)malloc(sizeof(StackFrame));
  newFrame->data = val;
  newFrame->prev = stack->top;
  stack->top = newFrame;
  stack->stackSize++;
}

StackData topStack(Stack* stack) {
  if (stack->top == 0) return STACK_DATA_NULL;
  return stack->top->data;
}

StackData popStack(Stack* stack) {
  if (stack->top == 0) return STACK_DATA_NULL;

  StackData retValue = topStack(stack);
  stack->stackSize--;
  StackFrame * tmp = stack->top;
  stack->top = stack->top->prev;
  free(tmp);

  return retValue;
}

void freeStack(Stack* stack) {
  while (stack->top) {
    popStack(stack);
  }
}


