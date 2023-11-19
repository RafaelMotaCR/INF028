#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define lineMaxSize 500

typedef struct node {
  struct node *left;
  struct node *right;
  struct node *father;
  int key;
  int level;
} node;

typedef struct tree {
  node *root;
} tree;

node *createNode(int k);
int fileCreate(char *path);
int fileCreate(char *path);
void freeTree(node *root);
tree *initTree();
void inorderTreeSave(FILE *fOut, node *x, int isLast);
node *insertTree(tree *T, int k);
void levelCorrector(node * x);
void modifyTree(tree *T, char *slice, int command);
void treeDelete(tree *T, int k);
node *treeMinimum(node *x);
node *treeSearch(node *x, int k);
node *treeSuccessor(node *x);
node *treeSuccessor(node *x);


int main() {

  // Checking if both (input and output) files exists

  if (!fileExists("L2Q3.in")) {
    printf("> Creeper, ohh man!\n");
    return EXIT_FAILURE;
  }

  if (!fileExists("L2Q3.out")) {

    fileCreate("L2Q3.out");
  }

  // If both files exists, open them

  FILE *fileIn = fopen("L2Q3.in", "r");
  FILE *fileOut = fopen("L2Q3.out", "w");

  // Uses " " (aka blank space) as separator
  // Uses line to read each line of the input
  // Uses "slice" to "broke" line in minor parts, separeted by "separator"

  char *separator = " ";
  char *slice;
  char *line = (char *)malloc(lineMaxSize * sizeof(char));

  tree *T = initTree();

  fgets(line, lineMaxSize, fileIn);

  while (line != NULL) {

    slice = strtok(line, separator);

    while (slice != NULL) {
      if (strcmp(slice, "a") == 0) {

        slice = strtok(NULL, separator);
        modifyTree(T, slice, 1);

      } else if (strcmp(slice, "r") == 0) {

        slice = strtok(NULL, separator);
        modifyTree(T, slice, 0);
      }
      slice = strtok(NULL, separator);
    }
    if (fgets(line, lineMaxSize, fileIn) != NULL) {
      inorderTreeSave(fileOut, T->root, 0);
      freeTree(T->root);
      T = initTree();
    } else {
      inorderTreeSave(fileOut, T->root, 1);
      freeTree(T->root);
      break;
    }
  }
  free(T);
  free(line);
  fclose(fileOut);
  fclose(fileIn);
  return EXIT_SUCCESS;
}

node *createNode(int k) {
  node *tmp = (node *)malloc(sizeof(node));

  if (tmp != NULL) {
    tmp->father = NULL;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->key = k;
    tmp->level = 0;
  }

  return tmp;
}

int fileCreate(char *path) {
  FILE *fileTest;
  fileTest = fopen(path, "w");

  if (fileTest == NULL) {
    return 0;
  }

  fclose(fileTest);
  return 1;
}

int fileExists(char *path) {
  FILE *fileTest;
  fileTest = fopen(path, "r");

  if (fileTest == NULL) {
    return 0;
  }

  fclose(fileTest);
  return 1;
}

void freeTree(node *root) {

  if (root == NULL) {
    return;
  }

  freeTree(root->left);
  freeTree(root->right);
  free(root);
}

tree *initTree() {

  tree *T = (tree *)malloc(sizeof(tree));
  T->root = NULL;
  return T;
}


void inorderTreeSave(FILE *fOut, node *x, int isLast) {
  if (x == NULL) {
    return;
  }

  node *current = x;
  node *stack[100]; // Assuming a maximum of 100 nodes in the stack
  int top = -1;     // Initialize top of stack

  while (current != NULL || top != -1) {
    // Traverse to the leftmost leaf
    while (current != NULL) {
      stack[++top] = current;
      current = current->left;
    }

    // Visit the top of the stack

    current = stack[top--];

    fprintf(fOut, "%d", current->key);
    fprintf(fOut, " (%d)", current->level);

    // Move to the right subtree

    current = current->right;

    if (!(top == -1 && current == NULL)) {
      fputc(32, fOut);
    }
  }
  if (!isLast) {
    fputc(10, fOut);
  }
}


node *insertTree(tree *T, int k) {

  node *x = T->root;
  node *y = NULL;
  node *new = createNode(k);
  int treeLvl = 0;

  while (x != NULL) {
    y = x;
    if (new->key >= x->key) {
      x = x -> right;
    } else {
      x = x -> left;
    }
    treeLvl = treeLvl + 1;
  }

  new -> father = y;
  new -> level = treeLvl;

  if (y == NULL) {
    T -> root = new;
  } else if (new -> key > y -> key) {
    y -> right = new;
  } else {
    y -> left = new;
  }
  return new;
}


void levelCorrector(node * x){

    if(x != NULL){

        levelCorrector(x -> left);
        x -> level = x -> level - 1; 
        levelCorrector(x -> right);

    }

}


void modifyTree(tree *T, char *slice, int command) {
  if (slice == NULL) {
    return;
  }
  int tmp = atoi(slice);

  if (command) {
    insertTree(T, tmp);
  } else {
    if (treeSearch(T->root, tmp) == NULL) {
      insertTree(T, tmp);
    } else {
      treeDelete(T, tmp);
    }
  }
}


void treeDelete(tree * T, int k) {

  node * z = treeSearch(T -> root, k);
  node * y;
  node * x;

  if (z -> left == NULL || z -> right == NULL) {
    y = z;
  } else {
    y = treeSuccessor(z);
  }

  if (y->left != NULL) {
    x = y -> left;
  } else {
    x = y -> right;
  }

  if (x != NULL) {
    x -> father = y -> father;
    levelCorrector(x);
  }

  if (y->father == NULL) {

    T->root = x;

  } else {
    if (y == y -> father -> left) {
      y -> father -> left = x;

    } else {
      y -> father -> right = x;
    }
  }
  if (y != z) {
    z -> key = y -> key;
  }
  free(y);
}


node *treeMinimum(node *x) {
  return (x->left != NULL) ? treeMinimum(x->left) : x;
}

node *treeSearch(node *x, int k) {

  if (x != NULL && x->key != k) {
    if (k > x->key) {
      return treeSearch(x->right, k);
    } else {
      return treeSearch(x->left, k);
    }
  }

  return x;
}


node *treeSuccessor(node *x) {
  if (x->right != NULL) {
    return treeMinimum(x->right);
  }
  node *y = x->father;
  while (y != NULL && x == y->right) {
    x = y;
    y = y->father;
  }
  return y;
}

