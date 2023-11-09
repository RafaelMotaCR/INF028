# include <stdio.h>
# include <stdlib.h>

typedef struct Node{
  int key;
  struct Node * left;
  struct Node * right;
  struct Node * m;
} Node;

typedef struct Tree{
  Node * root;
}Tree;


Node * create_node(int Key){
  Node * node = (Node*)malloc(sizeof(node));
  node -> key = Key;
  return node;
}


void inorder_tree_walk(Node * x){
  if(x != NULL){
    inorder_tree_walk(x->left);
    printf(" %d ", x -> key);
    inorder_tree_walk(x->right);
  }
}


void tree_insert(Tree * T, Node * z){
  Node * y = NULL;
  Node * x = T -> root;
  while(x != NULL){
    y = x;
    if(z -> key < x -> key){
      x = x -> left;
    }
    else{
      x = x -> right;
    }
  }
  x -> m = y;
  if(y == NULL){
    T -> root = z;
  }
  else if(z -> key < y -> key){
    y -> left = x;
  }
  else{
    y -> right = z;
  }
}
int main(){
  Tree * years = malloc(sizeof(Tree));
  Node * n1 = create_node(1960);
  Node * n2 = create_node(2001);
  Node * n3 = create_node(1939);
  years -> root = n1;
  n1 -> m = NULL;
  n1 -> left = n3;
  n1 -> right = n2;
  n2 -> m = n1;
  n2 -> left = NULL;
  n2 -> left = NULL;
  n3 -> m = n1;
  n3 -> left = NULL;
  n3 -> left = NULL;
  inorder_tree_walk(years -> root);
  return EXIT_SUCCESS;
}

