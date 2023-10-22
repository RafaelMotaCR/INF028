# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct node{
  struct node * prev;
  struct node * next;
  char * key;
} node;


typedef struct stack{
  node * head;
  node * tail;
  int tan;
} stack;


void init(stack * S){
  S -> head =NULL;
  S -> tail = NULL;
  S -> tan = 0;
}


void push(stack * S, char * string){
  S -> tan ++;
  node * newNode = (node *) malloc(sizeof(node));
  newNode -> key = (char *) malloc((strlen(string) + 1) * sizeof(char));
  strcpy(newNode -> key, string);
  if(S -> tail == NULL){
    newNode -> next = NULL;
    newNode -> prev = NULL;
    S -> head = newNode;
    S -> tail = newNode;
    return;
  }
  S -> tail -> next = newNode;
  newNode -> prev = S -> tail; 
  newNode -> next = NULL;
  S -> tail = newNode;
}


void pop(stack * S){
  if(S -> tail == NULL){
    return;
  }
  if(S -> tail -> prev != NULL){
    S -> tail = S -> tail -> prev;
    free(S -> tail);
    S->tail->next = NULL;
    S -> tan --;
    return;
  }
  free(S -> tail);
  S -> head = NULL;
  S -> tail = NULL;
}


void printStack(stack * S){
  node * x = S -> tail;
  printf("%c", '[');
  while(x -> prev != NULL){
    printf("%s%c%c", x -> key, ',', ' ');
    x = x -> prev;
  }
  printf("%s%c", x -> key, ']');
}


int main() {
    stack * myStack = malloc(sizeof(stack));
    push(myStack, "Ana Paula");
    push(myStack, "Ricardo Felix");
  printStack(myStack);
    push(myStack, "Pedro Sampaio");
    pop(myStack);
    printStack(myStack);
    free(myStack);
    return 0;
}