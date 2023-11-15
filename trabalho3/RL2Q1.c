# include <stdio.h>
# include <stdlib.h>
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


void insertTree(tree * T, int k)
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

    printf("level: %d\n", new -> level);

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

    char * slice;
    char * line = (char*) malloc(lineMaxSize * sizeof(char));

    tree * T = initTree();
    insertTree(T, 5);
    insertTree(T, 6);
    insertTree(T, 7);
    insertTree(T, 6);
    insertTree(T, 5);
    insertTree(T, 4);

}