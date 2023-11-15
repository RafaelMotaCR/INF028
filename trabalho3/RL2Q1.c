# include <stdio.h>
# include <stdlib.h>

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
        if(k > x -> key)
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


int main(){
    tree * T = initTree();
    insertTree(T, 5);
    insertTree(T, 8);
    insertTree(T, -1);
    insertTree(T, 4);
    insertTree(T, 6);
    insertTree(T, 9);
    insertTree(T, 11);
    insertTree(T, 15);

}