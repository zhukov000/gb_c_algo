#ifndef BIN_SEARCH_TREE
#define BIN_SEARCH_TREE

#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>
#include "heap_sort.h"

typedef struct {
  int value;
  unsigned cnt;

  struct BSTNode * left;
  struct BSTNode * right;
} BSTreeNode;

typedef struct {
  BSTreeNode * root;
} BSTree;

// callback function type, first - current node, second - current depth
typedef void (CallbackTreeTraverse)(BSTreeNode*, int);

BSTree*       makeBSTree();
BSTreeNode*   makeBSTNode(int);

void          freeBSTree(BSTree*);
void          freeBSTNode(BSTreeNode*);
void          print(BSTree*);

BSTreeNode*   insertBST(BSTreeNode*, int); // insert value to binary search tree
BSTreeNode*   searchBST(BSTreeNode*, int); // return pointer or 0 (if not found)
BSTreeNode*   removeBST(BSTreeNode*, int); // delete ALL nodes with value

int           isBalanced(BSTreeNode*);     // 1 if balanced, else 0
unsigned      countBST(BSTreeNode*);       // count of children
unsigned      heightBST(BSTreeNode*);      // height of tree (max depth)

void          leftTraverse(BSTreeNode*, unsigned, CallbackTreeTraverse*);
void          midTraverse(BSTreeNode*, unsigned, CallbackTreeTraverse*);
void          rightTraverse(BSTreeNode*, unsigned, CallbackTreeTraverse*);

BSTree*       createRandBST(unsigned, unsigned);
BSTree*       createBalancedBST(unsigned, unsigned);

#endif // BIN_SEARCH_TREE
