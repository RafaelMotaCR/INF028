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


// Function prototypes

node * createNode(int k);
int fileCreate (char * path);
int fileExists(char * path);
void freeTree(node * root);
tree * initTree();
node * insertTree(tree * T, int k);
node *treeMinimum(node *x);
node * treeSuccessor(node *x);
void saveToFile(FILE * fOut, node * n, int isLast);

// Main function

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

    // If both files exists, open them 

    FILE * fileIn = fopen("L2Q1.in", "r");
    FILE * fileOut = fopen("L2Q1.out", "w");

    // Uses " " (aka blank space) as separator
    // Uses line to read each line of the input
    // Uses "slice" to "broke" line in minor parts, separeted by "separator"

    char * separator = " ";
    char * slice;
    char * line = (char*) malloc(lineMaxSize * sizeof(char));

    // Main tree    
    tree * T = initTree();

    // Used to store the biggest num in the tree
    node * theBigOne; 

    // Used to temporaly store int numbers 
    int x; 

    fgets(line, lineMaxSize, fileIn);
    
    while(line != NULL)
    {

        /* Catches the first element, define them as the bigger
        and inserts it into the tree */

        slice = strtok(line, separator);
        x = atoi(slice);
        node * tmp = insertTree(T, x);
        fprintf(fileOut,"%d", tmp -> level);
        theBigOne = tmp;

        // Then, catches the next element

        slice = strtok(NULL, separator);

        while (slice != NULL)
        {

            fputc(32, fileOut); // Inserts a blank space between numbers in output
            int x = atoi(slice);
            tmp = insertTree(T, x); 

            /* If any number is greater than the "biggest" 
            Then it becomes the new "biggest" */

            if(tmp -> key > theBigOne -> key)
            {
                theBigOne = tmp;
            }

            // Saves the level of the last inserted number on the output file

            fprintf(fileOut,"%d", tmp -> level);

            // Goes to the next number

            slice = strtok(NULL, separator);

        }

        /*Tests whether the end of the file has been reached.
        If not, restart the tree and save the 
        data from the highest number.*/

        if(fgets(line, lineMaxSize, fileIn) != NULL)
        {

            saveToFile(fileOut, theBigOne, 0);
            freeTree(T -> root);
            theBigOne = NULL;
            T = initTree();

        }
        else{

            saveToFile(fileOut, theBigOne, 1);
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

node * createNode(int k)
{
    node * tmp = (node *) malloc(sizeof(node));

    if(tmp != NULL)
    {
        tmp -> key = k;
        tmp -> level = 0;
        tmp -> right = NULL;
        tmp -> left = NULL;
        tmp -> father = NULL;
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


void freeTree(node * root) {

    if (root == NULL) {
        return;
    }

    freeTree(root -> left);
    freeTree(root -> right);
    free(root);
}


tree * initTree()
{
    tree * T = (tree*) malloc(sizeof(tree));
    T -> root = NULL;
    return T;
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


void saveToFile(FILE * fOut, node * n, int isLast)
{
    node * x = treeSuccessor(n);
    if(x != NULL)
    {
        fprintf(fOut, " max %d alt %d pred %d", n -> key, n -> level, x -> key);
    }
    else
    {
        fprintf(fOut, " max %d alt %d pred NaN", n -> key, n -> level);
    }

    if(!isLast)
    {
        fputc('\n', fOut);
    }

}


node *treeMinimum(node *x) {
  return (x->left != NULL) ? treeMinimum(x->left) : x;
}


node *treeSuccessor(node *x) {
  if (x->left != NULL) {
    return treeMinimum(x->left);
  }
  node *y = x->father;
  while (y != NULL && x == y->left) {
    x = y;
    y = y->father;
  }
  return y;
}

