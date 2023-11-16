# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define lineMaxSize 500

typedef struct node
{
    struct node * left;
    struct node * right;
    struct node * father;
    int key;
    int level;
} node;


typedef struct tree
{
    node * root;
} tree;


node * createNode(int k)
{
    node * tmp = (node*) malloc(sizeof(node));

    if(tmp!= NULL)
    {
        tmp -> father = NULL;
        tmp -> left = NULL;
        tmp -> right = NULL;
        tmp -> key = k;
        tmp -> level = 0;
    }

    return tmp;

}

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
        if(new -> key >= x -> key)
        {
            x = x -> right;
        }
        else
        {
            x = x -> left;
        }
    }

    new -> father = y;
    new -> level = level;

    if(y == NULL)
    {
        T -> root = new;
    }
    else if(new -> key > y -> key)
    {
        y -> right = new;
    }
    else
    {
        y -> left = new;
    }
    return new;
}


node * treeMinimum(node * x) {
    return (x -> left != NULL) ? treeMinimum(x -> left) : x;
}



node * treeSearch(node * x, int k)
{

    if(x != NULL && x -> key != k)
    {
        if(k > x -> key)
        {
            return treeSearch(x -> right, k);
        }
        else
        {
            return treeSearch(x -> left, k);
        }

    }

    return x;

}


node * treeSuccessor(node * x){
    if(x -> right != NULL){
        return treeMinimum(x -> right);
    }
    node * y = x -> father; 
    while(y != NULL  && x == y -> right){
        x = y;
        y = y -> father;
    }
    return y;
}


void treeDelete(tree * T, int k)
{

    node * z = treeSearch(T -> root, k);
    node * y;
    node * x;

    if(z -> left == NULL || z -> right == NULL){
        y = z; 
    }  
    else{
        y = treeSuccessor(z);  
    } 

    if(y -> left != NULL){
        x = y -> left; 
    } 
    else{
        x = y -> right; 
    } 

    if(x != NULL){
        x -> father = y -> father; 
    } 

    if(y -> father == NULL){
      T -> root = x;
    } 
    else{
        if(y == y -> father -> left){
            y -> father -> left =  x;

        } 
        else{
            y -> father -> right = x; 
        }
    }
    if(y != z){
        z -> key = y -> key;
    } 
    free(y);
}


int main(){

    // Checking if both (input and output) files exists

    if(!fileExists("L2Q3.in"))
    {
        printf("> Creeper, ohh man!\n");
        return EXIT_FAILURE;

    }

    if(!fileExists("L2Q3.out"))
    {

        fileCreate("L2Q3.out");

    }

    // If both files exists, open them 

    FILE * fileIn = fopen("L2Q3.in", "r");
    FILE * fileOut = fopen("L2Q3.out", "w");

    // Uses " " (aka blank space) as separator
    // Uses line to read each line of the input
    // Uses "slice" to "broke" line in minor parts, separeted by "separator"

    char * separator = " ";
    char * slice;
    char * line = (char*) malloc(lineMaxSize * sizeof(char));

    tree * T = initTree();

    int x;

    fgets(line, lineMaxSize, fileIn);
    while(line != NULL)
    {

        slice = strtok(line, separator);

        while(slice != NULL)
        {
            printf(" %s ", slice);
            slice = strtok(NULL, separator);

        }

        if(fgets(line, lineMaxSize, fileIn) != NULL)
        {

        }
        else
        {
            break;
        }

    }

    return EXIT_SUCCESS;
}
