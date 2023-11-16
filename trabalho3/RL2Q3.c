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

node * insertTree(tree * T, int k){



}

int main(){


    return EXIT_SUCCESS;
}
