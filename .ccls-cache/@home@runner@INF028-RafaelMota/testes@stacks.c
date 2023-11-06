# include <stdio.h>
# include <stdlib.h>
# define MAX 10
# include <stdbool.h>

typedef struct Stack{
  int * S;
  int top;
} Stack;


void init(Stack * stack){
  stack->S = malloc(MAX * sizeof(int));
  stack->top = -1;
}


bool stack_full(Stack * s){
  return s->top + 1 == MAX;
}

bool stack_empty(Stack * s){
  return s->top == -1;
}


void push(Stack * s, int x){
  if(!stack_full(s)){
    s->top = s->top + 1;
    s->S[s->top] = x;
  }
  else{
    printf("%s\n", "stack overflow!");
  }

}


int pop (Stack * s){
  if(!stack_empty(s)){
    s->top = s->top - 1;
    return s->S[s->top + 1];
  }
  else{
    printf("%s\n", "Stack underflow");
  }
}


void print_stack(Stack * s){
  printf("%s\n", "Your stack: ");
  for(int i = s->top; i >= 0; i++){
    printf("");
  }
}


int main(){
  printf("> Char: %d.\n", sizeof(char));
  printf("> Float: %d.\n", sizeof(float));
  printf("> Int: %d.\n", sizeof(int));
  printf("> Unsigned Int: %d.\n", sizeof(unsigned int));
  printf("> Short Int: %d.\n", sizeof(short int));
  printf("> Long Long Int: %d.\n", sizeof(long long int));
  printf("> Double: %d.\n", sizeof(double));
  printf("> Long Double: %d.\n", sizeof(long double));
  printf("> Bool: %d.\n", sizeof(bool));
  printf("> Null: %d.\n", sizeof(NULL));
  printf("> Pointer: %d.\n", sizeof(void *));
  return EXIT_SUCCESS;
}