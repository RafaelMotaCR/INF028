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


void inorder(node * x)
{
    if(x != NULL)
    {
        inorder(x -> left);
        printf("%d ", x -> key);
        inorder(x -> right);
    }
}


int main(){
    int input = 1;
    tree * T = initTree();
    while(input){
        printf("> Enter a num: ");
        scanf("%d", & input);
        printf("Level: %d.\n", insertTree(T, input) -> level);
        insertTree(T, input);
    }
    inorder(T -> root);
    return EXIT_SUCCESS;
}
