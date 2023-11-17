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
} node;


typedef struct tree
{
    node * root;
} tree;

// Function prototypes

int calcSum(node * x);
node * createNode(int k);
int fileCreate (char * path);
int fileExists(char * path);
void freeTree(node * root);
tree * initTree();
void inorderTreeSave(FILE * fOut, node * x, int isLast);
node * insertTree(tree * T, int k);
int totalLR(node * x);

// Main function


int main(){
    // Checking if both (input and output) files exists

    if(!fileExists("L2Q2.in"))
    {
        printf("> Creeper, ohh man!\n");
        return EXIT_FAILURE;

    }

    if(!fileExists("L2Q2.out"))
    {

        fileCreate("L2Q2.out");

    }

    // If both files exists, open them 

    FILE * fileIn = fopen("L2Q2.in", "r");
    FILE * fileOut = fopen("L2Q2.out", "w");

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
            x = atoi(slice);
            insertTree(T, x);
            slice = strtok(NULL, separator);
        }
        if(fgets(line, lineMaxSize, fileIn) != NULL)
        {
            inorderTreeSave(fileOut, T -> root, 0);
            freeTree(T -> root);
            T = initTree();
        }
        else
        {
            inorderTreeSave(fileOut, T -> root, 1);
            freeTree(T -> root);
            break;
        }

    }

    fclose(fileIn);
    fclose(fileOut);
    free(T);
    free(line);
    return EXIT_SUCCESS;
}

// Functions

int calcSum(node * x)
{
    int sumLeft = totalLR(x -> left);
    int sumRight = totalLR(x -> right);
    int total = sumRight - sumLeft;
    return total;
}


node * createNode(int k){
    node * tmp = (node*) malloc(sizeof(node));
    if(tmp!= NULL)
    {
        tmp -> key = k;
        tmp -> father = NULL;
        tmp -> left = NULL;
        tmp -> right = NULL;
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


void freeTree(node * root)
{

    if (root == NULL)
    {
        return;
    }

    freeTree(root -> left);
    freeTree(root -> right);
    free(root);
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


void inorderTreeSave(FILE * fOut, node * x, int isLast) 
{
    if (x == NULL) 
    {
        return;
    }

    node * current = x;
    node * stack[100];  // Assuming a maximum of 100 nodes in the stack
    int top = - 1;  // Initialize top of stack

    while (current != NULL || top != - 1) 
    {
        // Traverse to the leftmost leaf
        while (current != NULL) 
        {
            stack[++top] = current;
            current = current -> left;
        }

        // Visit the top of the stack

        current = stack[top--];
        int total = calcSum(current);
        fprintf(fOut, "%d", current -> key);
        fprintf(fOut, " (%d)" , total);

        // Move to the right subtree
        
        current = current -> right;

        if(!(top == - 1 && current == NULL))
        {
            fputc(32, fOut);
        }
    }
    if(!isLast){
        fputc(10, fOut);
    }
}


node * insertTree(tree * T, int k)
{
    node * x = T -> root;
    node * y = NULL;
    node * new = createNode(k);
    while(x != NULL)
    {
        y = x;
        if(k == x -> key){
            free(new);
            return NULL;
        }
        else if(k > x -> key)
        {
            x = x -> right;
        }
        else
        {
            x = x -> left;
        }
    }
    
    new -> father = y;
    
    if(y == NULL){
        T -> root = new;
    }
    else if(new -> key > y -> key)
    {
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
