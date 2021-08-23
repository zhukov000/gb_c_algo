#include"binsearchtree.h"
#include<stdlib.h>

#define DEMO_BST_SIZE 15
#define BST_COUNT 50
#define BST_SIZE 10000

void task1() {
  BSTree* trees[BST_COUNT];
  for(int i=0; i<BST_COUNT; ++i) {
    if (rand() % 10 > 7) {
      trees[i] = createBalancedBST(BST_SIZE, BST_SIZE); // balanced with 20% chance
    } else {
      trees[i] = createRandBST(BST_SIZE, BST_SIZE);     // random tree
    }
  }

  unsigned cntBalanced = 0;
  for(int i=0; i<BST_COUNT; ++i) {
    if (isBalanced(trees[i]->root)) {
      cntBalanced ++;
    }
  }

  printf("Number of trees: %d\n", BST_COUNT);
  printf("Number of balanced: %d\n", cntBalanced);
  printf("Percent: %d%%\n\n", cntBalanced * 100 / BST_COUNT);

  for(int i=0; i<BST_COUNT; ++i) {
    freeBSTree(trees[i]);
  }
}

void task2() {
  BSTree* tree = makeBSTree();
  for(unsigned i=0; i<DEMO_BST_SIZE; ++i) {
    int v = rand() % DEMO_BST_SIZE;
    tree->root = insertBST(tree->root, v);
    printf("+%d ", v);
  }
  printf(" -> BST: \n");
  print(tree);
  printf("\n\nInput value for search: ");
  int v;
  scanf("%d", &v);
  BSTreeNode* res = searchBST(tree->root, v);
  if (res == 0) {
    printf("value %d not found in tree\n", v);
  } else {
    printf("value %d found in node: %d\n", v, res);
  }
  freeBSTree(tree);
}

void checkBSTree() {
  BSTree* tree = makeBSTree();

  // check insert
  for(unsigned i=0; i<DEMO_BST_SIZE; ++i) {
    int v = rand() % DEMO_BST_SIZE;
    tree->root = insertBST(tree->root, v);
    printf("+%d ", v);
  }
  printf(" -> BST: \n");
  print(tree);

  printf("\n");
  // check search
  for(unsigned i=0; i<DEMO_BST_SIZE; ++i) {
    int v = rand() % DEMO_BST_SIZE;
    BSTreeNode* res = searchBST(tree->root, v);
    if (res == 0) {
      printf("value %d not found\n", v);
    } else {
      printf("value %d found\n", v);
    }
  }
  printf("\n");
  // check remove
  for(unsigned i=0; i<DEMO_BST_SIZE; ++i) {
    int v = rand() % DEMO_BST_SIZE;
    tree->root = removeBST(tree->root, v);
    printf("-%d ", v);
  }
  printf(" -> BST: \n");
  print(tree);
  freeBSTree(tree);
  printf("\n");
  // check creation random BST
  tree = createRandBST(DEMO_BST_SIZE, 100);
  printf("random BST: \n");
  print(tree);
  printf("This tree %s balanced\n", isBalanced(tree->root) ? "is":"isn't");
  freeBSTree(tree);
  printf("\n");

  // check creation balanced BST
  tree = createBalancedBST(DEMO_BST_SIZE, 100);
  printf("balanced BST: \n");
  print(tree);
  printf("This tree %s balanced\n", isBalanced(tree->root) ? "is":"isn't");
  freeBSTree(tree);
  printf("\n");
}
