#include"binsearchtree.h"

static int lastMaxTraverseDepth = 0;    // max leaf depth
static int lastMinTraverseDepth = 1e9;  // min leaf depth

#define max(a,b) (a > b ? a : b)

BSTree* makeBSTree(){
  BSTree* tree = (BSTree*) malloc(sizeof(BSTree));
  tree->root = 0;
  return tree;
}

BSTreeNode* makeBSTNode(int value) {
  BSTreeNode* node = (BSTreeNode*) malloc(sizeof(BSTreeNode));
  node->value = value;
  node->left = node->right = 0;
  node->cnt = 1;
  return node;
}

void freeBSTree(BSTree* tree) {
  if(tree == 0) return;
  freeBSTNode(tree->root);
  free(tree);
}
void freeBSTNode(BSTreeNode* node) {
  if (node == 0) return;
  freeBSTNode(node->left);
  freeBSTNode(node->right);
  free(node);
}

unsigned countBST(BSTreeNode* node) {
  if (!node) return 0;
  return node->cnt;
}

BSTreeNode* insertBST(BSTreeNode* node, int value) {
  if (node == 0) {
    BSTreeNode* newNode = makeBSTNode(value);
    return newNode;
  }
  if (value <= node->value) {
    node->left = insertBST(node->left, value);
  } else {
    node->right = insertBST(node->right, value);
  }
  node->cnt = countBST(node->left) + countBST(node->right) + 1;
  return node;
}

BSTreeNode* searchBST(BSTreeNode* node, int value) {
  if (node == 0) return 0;
  if (value == node->value) {
    return node;
  }
  if (value < node->value) {
    return searchBST(node->left, value);
  }
  return searchBST(node->right, value);
}

BSTreeNode* mergeBST(BSTreeNode* root1, BSTreeNode* root2) {
  if (root1 == 0) return root2;
  if (root2 == 0) return root1;

  if (root1->cnt >= root2->cnt) {
    root1->right = mergeBST(root1->right, root2);
    root1->cnt = countBST(root1->left) + countBST(root1->right) + 1;
    return root1;
  } else {
    root2->left = mergeBST(root1, root2->left);
    root2->cnt = countBST(root2->left) + countBST(root2->right) + 1;
    return root2;
  }
}

BSTreeNode* removeBST(BSTreeNode* node, int value) {
  if (node == 0) return 0;
  if (value == node->value) {
    BSTreeNode* tmp = node;
    node = mergeBST(node->left, node->right);
    free(tmp);
    node = removeBST(node, value); // multiply recursive delete
  } else {
    if (value < node->value) {
      node->left = removeBST(node->left, value);
    } else {
      node->right = removeBST(node->right, value);
    }
  }
  return node;
}

void initLastTraverse() {
  lastMaxTraverseDepth = 0;
  lastMinTraverseDepth = 1e9;
}

void depthUpdateCallback(BSTreeNode* node, int depth) {
  if (node == 0) return;
  if (node->left == 0 && node->right == 0) {
    if (depth > lastMaxTraverseDepth) lastMaxTraverseDepth = depth;
    if (depth < lastMinTraverseDepth) lastMinTraverseDepth = depth;
  }
}

unsigned heightBST(BSTreeNode* node) {
  if (node == 0) return 0;
  return max(heightBST(node->left), heightBST(node->right)) + 1;
}

int isBalanced(BSTreeNode* node) {
  return node == 0 ||
      isBalanced(node->left) &&
      isBalanced(node->right) &&
      abs(heightBST(node->left) - heightBST(node->right)) <= 1;
}

void leftTraverse(BSTreeNode* node, unsigned depth, CallbackTreeTraverse* fun) {
  if (node == 0) return;

  leftTraverse(node->left, depth+1, fun);
  fun(node, (int)depth);
  leftTraverse(node->right, depth+1, fun);
}

void midTraverse(BSTreeNode* node, unsigned depth, CallbackTreeTraverse* fun) {
  if (node == 0) return;

  fun(node, (int)depth);
  midTraverse(node->left, depth+1, fun);
  midTraverse(node->right, depth+1, fun);
}

void rightTraverse(BSTreeNode* node, unsigned depth, CallbackTreeTraverse* fun) {
  if (node == 0) return;

  rightTraverse(node->right, depth+1, fun);
  fun(node, (int)depth);
  rightTraverse(node->left, depth+1, fun);
}

void printNodeCallback(BSTreeNode* node, int depth) {
  if (node == 0) return;
  for(int i=0; i<depth; ++i) {
    printf("   ");
  }
  if (node->left == 0 && node->right == 0) {
    printf("{%02d\n",node->value); // leaf
  } else {
    printf("(%02d)\n",node->value);
  }
}

void print(BSTree* tree) {
  if(tree == 0) return;
  rightTraverse(tree->root, 0, printNodeCallback);
}

BSTree* createRandBST(unsigned size, unsigned mod) {
  BSTree* tree = makeBSTree();
  for(unsigned i=0; i<size; ++i) {
    tree->root = insertBST(tree->root, rand() % mod);
  }
  return tree;
}

BSTreeNode* insertBalanced(BSTreeNode* root, int left, int right) {
  if (left < right) {
    int mid = (left + right) / 2;
    root = insertBST(root, mid);
    root = insertBalanced(root, left, mid);
    root = insertBalanced(root, mid+1, right);
  }
  return root;
}

void setBalancedValues(BSTreeNode* node, int* arr) {
  if (node == 0) return;

  node->value = arr[node->value];
  setBalancedValues(node->left, arr);
  setBalancedValues(node->right, arr);
}

BSTree* createBalancedBST(unsigned size, unsigned mod) {
  int * arr = (int *) calloc(size, sizeof(int));
  for(unsigned i=0; i<size; ++i) {
    arr[i] = rand() % mod;
  }
  heapSort(arr, size);

  BSTree* tree = makeBSTree();
  tree->root = insertBalanced(tree->root, 0, size);
  setBalancedValues(tree->root, arr);
  free(arr);

  return tree;
}
