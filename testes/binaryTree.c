# include <stdio.h> 
# include <stdlib.h>

typedef struct node{
    struct node * left;
    struct node * right;
    struct node * father;
    int key;
} node;


typedef struct tree{
    node * root;
} tree;


node * createNode(int k){
    node * tmp = (node *) malloc(sizeof(node));
    if(tmp != NULL){
        tmp -> key = k;
    }
    return tmp;

}


void treeInsert(tree * T, int k){

    node * newNode = createNode(k);

    node * x = T -> root;
    node * y = NULL;

    while(x != NULL){

        y = x;

        if(newNode -> key > x -> key){
            x = x -> right;
        }
        else{
            x = x -> left;
        }

    }

    if(y == NULL){
        T -> root = newNode;
    }
    else if(newNode -> key > y -> key){
        y -> right = newNode;
    }
    else{
        y -> left = newNode;
    }

}


node * treeSearch(node * x, int k){
    if(x == NULL  || x -> key == k){
        return x;
    }
    if(k < x -> key){
        return treeSearch(x -> left, k);
    }
    else{
        return treeSearch(x -> right, k);
    }

}


node * treeMinimum(node * x){
    if(x -> left == NULL) {
        return x;
    }
    else{  
        return treeMinimum (x->left);
    }
}


void printTree(node * root, int space) {
    // Base case
    if (root == NULL) {
        return;
    }

    // Increase distance between levels
    space += 5;

    // Process right child first
    printTree(root->right, space);

    // Print current node after space
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->key);

    // Process left child
    printTree(root->left, space);
}


void inorderTreeWalk(node * x){

    if(x != NULL){

        inorderTreeWalk(x -> left);
        printf(" %d ", x -> key);
        inorderTreeWalk(x -> right);

    }

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


void treeDelete(tree * T, int k){ 
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
    tree * T = (tree*) malloc(sizeof(tree));
    int input = 1;
    while (input)
    {
        printf("> Enter a num: ");
        scanf("%d", & input);
        treeInsert(T, input);
    }

    printTree(T -> root, 2);
}
