# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define lineMaxSize 500

typedef struct node
{
    struct node * right;
    struct node * left;
    struct node * father;
    int key;
    int level;
} node;


typedef struct tree
{
    node * root;
} tree;


int fileCreate (char * path) 
{
  FILE * fileTest;
  fileTest = fopen(path, "w");

  if(fileTest == NULL) 
  {
    return 0;
  }

  fclose(fileTest);
  return 1;
}


int fileExists(char * path) 
{
  FILE * fileTest;
  fileTest = fopen(path, "r");

  if(fileTest == NULL) 
  {
    return 0;
  }

  fclose(fileTest);
  return 1;
}


tree * initTree()
{
    tree * T = (tree*) malloc(sizeof(tree));
    T -> root = NULL;
    return T;
}


node * createNode(int k)
{
    node * tmp = (node *) malloc(sizeof(node));
    if(tmp != NULL)
    {
        tmp -> key = k;
        tmp -> level = 0;
    }
    return tmp;
}


node * insertTree(tree * T, int k)
{

    node * y = NULL;
    node * x = T -> root;
    node * new = createNode(k);
    int treeLvl = 0;

    while(x != NULL)
    {
        y = x;
        if(k >= x -> key)
        {
            x = x -> right;
        }
        else
        {
            x = x -> left;
        }
        treeLvl = treeLvl + 1;
    }

    new -> father = y;
    new -> level = treeLvl;

    if(y == NULL)
    {
        T -> root = new;
    }
    else if(k > y -> key)
    {
        y -> right = new;
    }
    else
    {
        y -> left = new;
    }

   return new;

}


void inorder_tree_walk(node * x){
    if( x!= NULL){
        inorder_tree_walk(x->left);
        printf(" %d ", x->key);
        inorder_tree_walk(x->right);
    }
}


void printTree(node* root, int space) {
    // Base case
    if (root == NULL) {
        return;
    }

    // Increase distance between levels
    space += 5;

    // Process right child first
    printTree(root->right, space);

    // Print current node after space
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->key);

    // Process left child
    printTree(root->left, space);
}


void freeNode(node * x) {
    if (x != NULL) {
        freeNode(x->left);
        freeNode(x->right);
        free(x);
    }
}


void freeTree(tree * T) {
    freeNode(T->root);
    free(T);
}


int main()
{
    // Checking if both (input and output) files exists

    if(!fileExists("L2Q1.in"))
    {

        printf("> Creeper, ohh man!\n");
        return EXIT_FAILURE;

    }

    if(!fileExists("L2Q1.out"))
    {

        fileCreate("L2Q1.out");

    }

    FILE * fileIn = fopen("L2Q1.in", "r");
    FILE * fileOut = fopen("L2Q1.out", "w");

    char * separator = " ";
    char * slice;
    char * line = (char*) malloc(lineMaxSize * sizeof(char));

    tree * T = initTree();

    fgets(line, lineMaxSize, fileIn);
    while(line != NULL)
    {
        slice = strtok(line, separator);
        while (slice != NULL)
        {
            int tmp = atoi(slice);    
            printf("%d ", insertTree(T, tmp) -> level);
            slice = strtok(NULL, separator);

        }
        if(fgets(line, lineMaxSize, fileIn) != NULL)
        {
            freeTree(T);
            T = initTree();
            printf("\n");
        }
        else{
            freeTree(T);
            T = initTree();
            printf("\n> I'm at the last line, buddy!\n");
            break;
        }
        T = initTree();

    }

}