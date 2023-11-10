# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct Node{
  int key;
  struct Node * left; // Son of left 
  struct Node * right; // Son of right
  struct Node * m; // Mother 
} Node;


typedef struct Tree{
  Node * root; // Struct that save the root of the three
}Tree;


Node * create_node(int Key){
  Node * node = (Node*)malloc(sizeof(node));
  node -> key = Key;
  return node;
}


int main(){
  printf("%s", "Hi! I'm Beginning this project right now, and it will take some time to get complet");
}
