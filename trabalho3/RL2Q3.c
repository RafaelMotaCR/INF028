# include <stdio.h>
# include <stdlib.h>
# include <string.h>

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

    if(x!=NULL){
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


    return EXIT_SUCCESS;
}
