# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>

# define MAX_SIZE 100

typedef struct Queue{
  float * Q;
  int head;
  int tail;
} Queue;

void __init__(Queue * q);
void enqueue(Queue * q, float x);
void printQueue(Queue * q);

void __init__(Queue * q){
  q->head = q->tail = 0;
  q->Q = malloc(MAX_SIZE * sizeof(float));
}


void enqueue(Queue * q, float x){
  q->Q[q->tail] = x;
  if(q->tail == MAX_SIZE){
    q->tail = 0;
  }
  else{
    q->tail = q->tail = q->tail + 1;
  }
}


void printQueue(Queue * q){
  int i = q->head;
  int j = q->tail;
  printf("%c", '[');
  while(i != j){
    if(i == j - 1){
      printf("%.2f", q->Q[i]);
    }
    else{
     printf("%.2f, ", q->Q[i]);
    }
      i = (i + 1) % MAX_SIZE;
  }
  printf("%c\n", ']');
}


int main(){
  Queue * f = malloc(sizeof(Queue));
  __init__(f);
  enqueue(f, 3.4f);
  enqueue(f, 8.2f);
  enqueue(f, 9.5f);
  printQueue(f);
  return EXIT_SUCCESS;
}