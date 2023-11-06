# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# define lineMaxSize 500


typedef struct simpleNode {
  struct simpleNode * next;
  float key;
} simpleNode;


typedef struct circularList {
  simpleNode * head;
  simpleNode * tail;
} circularList;


typedef struct node {
  struct node * next;
  struct node * prev;
  circularList * key;
  float range;
} node;


typedef struct linkedList {
  node * head;
  node * tail;
} linkedList;


int fileCreate(char path[]);
int fileExists(char path[]);
void freeCL(circularList * L);
void freeLists(linkedList * L);
void initCL(circularList * L);
void initLL(linkedList * L);
void insertCL(circularList * L, float X);
void insertKey(linkedList * L, float X);
void insertLL(linkedList * L, float X);
void saveToFile(linkedList * L, FILE * fileOut, int isLast);


int fileCreate(char path[]) {
  FILE * fileCreate;
  fileCreate = fopen(path, "w");
  if(fileCreate == NULL) {
    return 0;
  }
  fclose(fileCreate);
  return 1;
}


int fileExists(char path[]) {
  FILE * fileTest;
  fileTest = fopen(path, "r");
  if(fileTest == NULL) {
    return 0;
  }
  fclose(fileTest);
  return 1;
}


void freeCL(circularList * L) {
  if (L == NULL) {
    return; // Se a lista for nula, não há nada a ser liberado
  }
  simpleNode * current = L -> head;
  simpleNode * temp;
  while (current != NULL) {
    temp = current;
    current = current -> next;
    free(temp);
    if (current == L -> head) {
      break; // Para evitar um loop infinito se a lista for circular
    }
  }
  L -> head = NULL; // Define o ponteiro da lista como NULL no final da função
  L -> tail = NULL;
}


void freeLists(linkedList * L) {
  node * current = L -> tail;
  node * temp;
  while (current != NULL) {
    temp = current;
    freeCL(temp -> key);
    current = current -> prev;
    free(temp);
  }
  L -> head = NULL;
  L -> tail = NULL;
}


void initCL(circularList * L) {
  L -> head = NULL;
  L -> tail = NULL;
}


void initLL(linkedList * L) {
  L -> head = NULL;
  L -> tail = NULL;
}


void insertCL(circularList * L, float X) {
  simpleNode * newNode = (simpleNode *)malloc(sizeof(simpleNode));
  newNode -> key = X;
  simpleNode * tmp = L -> head;
  if(tmp == NULL) {
    L -> head = newNode;
    L -> tail = newNode;
    newNode -> next = newNode;
  } else {
    if(X < tmp -> key) {
      newNode -> next = tmp;
      L -> head = newNode;
      L -> tail -> next = newNode;
    } else {
      while (tmp != L -> tail && X > tmp -> next -> key) {
        tmp = tmp -> next;
      }
      newNode -> next = tmp -> next;
      tmp -> next = newNode;
      if (tmp == L -> tail) {
        L -> tail = newNode;
      }
    }
  }
}


void insertKey(linkedList * L, float X) {
  node * tmp = L -> head;
  if(tmp == NULL) {
    return;
  }
  while(tmp != NULL) {
    float difference = 0.0f;
    if((X - tmp -> range) <= 0.99f &&  X > tmp -> range - 1) {
      insertCL(tmp -> key, X);
      break;
    }
    else if((tmp -> range - X) <= 0.99f && X > tmp -> range - 1 && X < tmp -> range + 1){
      insertCL(tmp -> key, X);
      break;
    }
    tmp = tmp -> next;
  }
}


void insertLL(linkedList * L, float X) {
  node * newNode = (node *)malloc(sizeof(node));
  newNode -> range = X;
  newNode -> key = (circularList*)malloc(sizeof(circularList));
  initCL(newNode -> key);
  node * tmp = L -> head;
  if(tmp == NULL) {
    newNode -> prev = NULL;
    newNode -> next = NULL;
    L -> head = newNode;
    L -> tail = newNode;
  } else {
    if(X < tmp -> range) {
      newNode -> next = tmp;
      newNode -> prev = NULL;
      tmp -> prev = newNode;
      L -> head = newNode;
    } else {
      while(X > tmp -> range && tmp -> next != NULL) {
        if(tmp -> range == X) {
          free(newNode -> key);
          free(newNode);
          return;
        }
        tmp = tmp -> next;
      }
      newNode -> next = tmp;
      newNode -> prev = tmp -> prev;
      if(tmp -> next == NULL) {
        newNode -> prev = tmp;
        newNode -> next = NULL;
        tmp -> next = newNode;
      } else {
        tmp -> prev -> next = newNode;
        tmp -> prev = newNode;
      }
    }
  }
}


void saveToFile(linkedList * L, FILE * fileOut, int isLast) {
  node * tmp = L -> head;
  simpleNode * end;
  fprintf(fileOut, "[");
  while(tmp != NULL) {
    fprintf(fileOut, "%.0f", tmp -> range );
    simpleNode * X = tmp -> key -> head;
    fputc('(',fileOut);
    if(tmp -> key -> head != NULL) {
      while (X -> next != tmp -> key -> head) {
        fprintf(fileOut, "%g->", X -> key);
        X = X -> next;
      }
      fprintf(fileOut, "%g)", X -> key);
    } else {
      fprintf(fileOut, ")");
    }
    tmp = tmp -> next;
    if(tmp != NULL) {
      fprintf(fileOut, "->");
    }
  }
  if(!isLast) {
    fprintf(fileOut, "]\n");
  } else {
    fprintf(fileOut, "]");
  }
}


float limitarCasasDecimais(char* str, int casas) {
    float number = atof(str); // converter a string para um número de ponto flutuante
    float potencia = 1;
    for (int i = 0; i < casas; i++) {
        potencia *= 10;
    }
    return ((int)(number * potencia)) / potencia;
}


int main() {
  if(!fileExists("L1Q3.in")) { // Se o arquivo de entrada não existir, para a execução
    printf("> Input file not found!");
    return EXIT_FAILURE;
  }

  if(!fileExists("L1Q3.out")) { // Se o arquvivo de saída não existir, o cria
    fileCreate("L1Q3.out");
  }

  FILE * fileIn = fopen("L1Q3.in", "r");
  FILE * fileOut = fopen("L1Q3.out", "w");
  char * line = (char*) malloc(lineMaxSize * (sizeof(char)));
  char * separator = " ";
  char * slice;

  linkedList * main = malloc(sizeof(linkedList));
  initLL(main);
  fgets(line, lineMaxSize, fileIn);
  while(line != NULL) {
    slice = strtok(line, separator);
    while(slice != NULL) {
      if(strcmp(slice, "LE") == 0) {
        slice = strtok(NULL, separator);
        while((strcmp(slice, "LI") != 0) && slice != NULL) {
          float tmp = limitarCasasDecimais(slice, 2);
          insertLL(main, tmp);
          slice = strtok(NULL, separator);
        }
      }
      if(strcmp(slice, "LI") == 0) {
        slice = strtok(NULL, separator);
        while((strcmp(slice, "LE") != 0)) {
          float tmp = limitarCasasDecimais(slice, 2);
          insertKey(main, tmp);
          slice = strtok(NULL, separator);
          if(slice == NULL) {
            break;
          }
        }
      }
      slice = strtok(NULL, separator);
    }
    if(fgets(line, lineMaxSize, fileIn) != NULL) {
      saveToFile(main, fileOut, 0);
      freeLists(main);
    } else {
      saveToFile(main, fileOut, 1);
      freeLists(main);
      break;
    }
  }
  fclose(fileIn);
  fclose(fileOut);
  free(line);
  free(main);
  return EXIT_SUCCESS;
}
