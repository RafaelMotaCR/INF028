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
        tmp -> right = NULL;
        tmp -> left = NULL;
        tmp -> father = NULL;
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


void freeTree(node * root) {

    if (root == NULL) 
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}


void saveToFile(FILE * fOut, node * n, int isLast)
{
    if(n -> father != NULL)
    {
        fprintf(fOut, " max %d alt %d pred %d", n -> key, n -> level, n -> father -> key);
    }
    else
    {
        fprintf(fOut, " max %d alt %d pred NaN", n -> key, n -> level);
    }
    if(!isLast)
    {
        fputc('\n',fOut);
    }
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
    node * theBigOne;

    fgets(line, lineMaxSize, fileIn);
    
    while(line != NULL)
    {

        slice = strtok(line, separator);
        int x = atoi(slice);
        node * tmp = insertTree(T, x);
        fprintf(fileOut,"%d", tmp -> level);
        theBigOne = tmp;
        slice = strtok(NULL, separator);

        while (slice != NULL)
        {
            fputc(32, fileOut);
            x = atoi(slice);
            tmp = insertTree(T, x); 
            if(tmp -> key > theBigOne -> key)
            {
                theBigOne = tmp;
            }
            fprintf(fileOut,"%d", tmp -> level);
            slice = strtok(NULL, separator);

        }

        if(fgets(line, lineMaxSize, fileIn) != NULL)
        {
            saveToFile(fileOut, theBigOne, 0);
            freeTree(T -> root);
            T = initTree();
        }
        else{
            saveToFile(fileOut, theBigOne, 1);
            freeTree(T -> root);
            break;
        }

    }

}
