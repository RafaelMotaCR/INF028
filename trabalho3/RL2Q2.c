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


node * createNode(int k){
    node * tmp = (node*) malloc(sizeof(node));
    if(tmp!= NULL)
    {
        tmp -> key = k;
        tmp -> level = 0;
        tmp -> father = NULL;
        tmp -> left = NULL;
        tmp -> right = NULL;
    }
    return tmp;
}


tree * initTree()
{
    tree * tmp = (tree*)malloc(sizeof(node));

    if(tmp != NULL)
    {
        tmp -> root = NULL;
    }

    return tmp;
}


node * insertTree(tree * T, int k)
{
    node * x = T -> root;
    node * y = NULL;
    node * new = createNode(k);
    int level = 0;
    while(x != NULL)
    {
        y = x;
        level = level + 1;
        if(k == x -> key){
            free(new);
            node * flag = (node*) malloc(sizeof(node));
            flag -> level = 99;
            return flag;
        }
        else if(k > x -> key)
        {
            x = x -> right;
        }
        else{
            x = x -> left;
        }
    }
    
    new -> father = y;
    new -> level = level;
    
    if(y == NULL){
        T -> root = new;
    }
    else if(new -> key > y -> key){
        y -> right = new;
    }
    else{
        y -> left = new;
    }
    return new;
}


int totalLR(node * x)
{
    if(x == NULL){
        return 0;
    }

    int sum = x -> key;
    sum += totalLR(x -> left);
    sum += totalLR(x -> right);
    return sum;
}


void inorder(tree * T, node * x)
{
    if(x != NULL)
    {
        inorder(T, x -> left);
        printf("%d ", x -> key);
        printf("(%d) ", totalLR(x -> right) - totalLR(x -> left));
        inorder(T, x -> right);
    }
}


int main(){
    tree * T = initTree();
    insertTree(T,15);
    insertTree(T,2);
    insertTree(T,5);
    insertTree(T,19);
    insertTree(T,2);
    insertTree(T,22);
    insertTree(T,4);
    insertTree(T,9);
    insertTree(T,0);
    insertTree(T,3);
    insertTree(T,4);
    insertTree(T,5);
    inorder(T, T -> root);
    return EXIT_SUCCESS;
}
