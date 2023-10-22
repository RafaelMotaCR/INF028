# include <stdio.h>
# include <stdlib.h>

typedef struct Node{
  int key;
  struct Node * next;
  struct Node * prev;
} Node;


typedef struct List{
  Node * head;
} List;


void initList(List * input){
  input -> head = NULL;
}


void insertAtEnd(List * L, int K){
  Node * newNode = malloc(sizeof(Node));
  newNode -> key = K;
  newNode -> next = NULL;
  Node * x = L -> head;
  if(L -> head == NULL){
    newNode -> prev = NULL;
    L -> head = newNode;
    return;
  }
  while(x -> next != NULL){
    x = x -> next;
  }
  x -> next = newNode;
  newNode -> prev = x;
}


void insertAtStart(List * L, int K){
  Node * newNode = malloc(sizeof(Node));
  newNode -> key = K;
  if(L -> head == NULL){
    newNode -> prev = NULL;
    newNode -> next = NULL;
    L -> head = newNode; 
  }
  else{
    newNode -> next = L -> head;
    newNode -> prev = NULL;
    L -> head -> prev = newNode;
    L -> head = newNode;
  }
}


Node * listSearch(List * L, int K){
  Node * x = L -> head;
  int finded = 0;
  while(x != NULL){
    if(x -> key == K){
      finded = 1; 
      break;
    }
    x = x -> next;
  }
  if(finded){
    printf("%s","> The item exists in the list\n");
  }
  else{
    printf("%s","> The item not exists in the list\n");
  }
  return x;
}


void removeNode(List * L, int K){
  Node * x = L -> head;
  int finded = 0;
  while(x != NULL){
    if(x -> key == K){
      x -> prev -> next = x -> next;
      x -> next -> prev = x -> prev;
      free(x);
      finded = 1; 
      break;
    }
    x = x -> next;
  }
  if(finded){
    printf("%s", "> Element removed\n");
  }
  else{
    printf("%s", "> Element not finded\n");
  }
}


void printList(List * L){
  Node * x = L->head;
  if(x == NULL){
    printf("> The list is empty");
  }
  else if(x->next == NULL){
    printf("%d.", x->key);
    return;
  }
  while(x != NULL){
    printf("%d, ", x->key);
    x = x->next;
  }
  printf("\n");
}


int main(){
  int exit = 0;
  int number;
  int option;
  List * mainList = malloc(sizeof(List));
  initList(mainList);
  while(!exit){
    printf("%s", "-----------------------\n");
    printf("%s", "0 - EXIT\n");
    printf("%s", "1 - INSERT AT THE END\n");
    printf("%s", "2 - INSERT AT THE START\n");
    printf("%s", "3 - PRINT LIST\n");
    printf("%s", "4 - REMOVE FROM THE END\n");
    printf("%s", "5 - REMOVE FROM THE START\n");
    printf("%s", "6 - REMOVE A NUMBER\n");
    printf("%s", "7 - SEARCH ON LIST\n");
    printf("%s", "-----------------------\n");
    printf("%s", "> Your chice: ");
    scanf("%d", & option);
    switch(option){
      case 0:{
        exit = 1;
        printf("%s", "Leaving...");
        break;
      }
      case 1:{
        printf("%s", "> Insert a number: ");
        scanf("%d", & number);
        insertAtEnd(mainList, number);
        break;
      }
      case 2:{
        printf("%s", "> Insert a number: ");
        scanf("%d", & number);
        insertAtStart(mainList, number);
        break;
      }
      case 3: {
        printList(mainList);
        break;
      }
      case 4:{
        // remove from the end
         break; 
      }
      case 5:{
        // remove from the start
      }
      case 6:{
        // remove a especified number
        break;
      }
      case 7:{
        printf("%s", "> Insert a number: ");
        scanf("%d", & number);
        listSearch(mainList, number);
        break;
      }
      default:{
        printf("%s", "INVALID OPTION!\n\n");
        break;
      }
    }
  }
  return 0;
}