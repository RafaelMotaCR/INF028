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
};


node * createNode(int k)
{
    node * tmp = (node *) malloc(sizeof(node));
    if(tmp != NULL)
    {
        tmp -> key = k;
    }
    return tmp;
}


void insertTree(node * root, int k)
{

    node * y;
    node * x = root;
    node * new = createNode(k);

    while(x != NULL){
        y = x;
        if(k > x -> key){
            x = x -> left;
        }
        else{
            x = x -> right;
        }
    }

    new -> father = y;

    if(y == NULL){
        root = new;
    }
    else if(k > y -> key){
        y -> right = new;
    }
    else{
        y -> left = new;
    }



}

int main(){


}