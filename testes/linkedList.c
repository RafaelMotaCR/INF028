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


void insert(List * L, int K){
  Node * x = L -> head;

}

Node * listSearch(List * L, int K){
  Node * x = L -> head;
  while(x -> next != NULL && x -> key != K){
    x = x -> next;
  }
  return x;
}


void printList(List * L){
  Node * x = L->head;
  if(x == NULL){
    printf("> The list is empty");
  }
  while(x->next != NULL){
    printf("%d, ", x->key);
    x = x->next;
  }
}


int main(){
  int exit = 0;
  int option;
  while(!exit){
    printf("%s", "0 - EXIT\n");
    printf("%s", "1 - INSERT ON LIST\n");
    printf("%s", "2 - REMOVE FROM LIST\n");
    printf("%s", "3 - SEARCH ON LIST\n");
    printf("%s", "> Your chice: ");
    scanf("%d", & option);
    switch(option){
      case 0:{
        exit = 1;
        printf("%s", "Leaving...");
        break;
      }
      case 1:{
        //insertion
        break;
      }
      case 2:{
        //remove
        break;
      }
      case 3: {
        //search
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