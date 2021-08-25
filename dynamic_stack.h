#ifndef DYNAMIC_STACK_GB
#define DYNAMIC_STACK_GB

#include"malloc.h"
#include"assert.h"

#define STACK_DATA_NULL 0

typedef unsigned StackData;

typedef struct {
  StackData data;
  struct StackFrame* prev;
} StackFrame;

typedef struct {
  StackFrame* top;
  unsigned stackSize;
} Stack;


Stack*      initStack();
void        pushStack(Stack* stack, StackData val);
StackData   topStack(Stack* stack);
StackData   popStack(Stack* stack);
void        freeStack(Stack* stack);

#endif // DYNAMIC_STACK_GB
