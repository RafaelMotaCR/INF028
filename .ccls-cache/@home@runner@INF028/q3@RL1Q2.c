// Nome: L1Q2
// Objetivo: Empilhar na pilha principal, sempre a ordem alfabética
// e respeitando a politica LIFO (last in - First out)
// Criador: Rafael Mota

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define lineMaxSize 500

typedef struct node {
  struct node * prev;
  struct node * next;
  char * key;
} node;


typedef struct stack {
  node * head;
  node * tail;
} stack;


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


void init(stack * S) {
  S -> head =NULL;
  S -> tail = NULL;
}


void pop(stack * S) {
  if(S -> tail == NULL) {
    return;
  }
  node * temp = S -> tail -> prev;
  free(S -> tail -> key);
  free(S -> tail);
  S -> tail = temp;
  if(S -> tail != NULL) {
    S -> tail -> next = NULL;
  }
  if (S -> tail == NULL) {
    S -> head = NULL;
  }
}


void printStack(stack * S) {
  node * x = S -> tail;
  printf("%c", '[');
  while(x -> prev != NULL) {
    printf("%s%c%c", x -> key, ',', ' ');
    x = x -> prev;
  }
  printf("%s%c", x -> key, ']');
  printf("%s", "\n");
}


void push(stack * S, char * string) {
  node * newNode = (node *) malloc(sizeof(node));
  newNode -> key = (char *) malloc((strlen(string) + 1) * sizeof(char));
  strcpy(newNode -> key, string);
  if(S -> tail == NULL) {
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


int main() {

  if(!fileExists("L1Q2.in")) { // Se o arquivo de entrada não existir, para a execução
    printf("> Input file not found!");
    return EXIT_FAILURE;
  }

  if(!fileExists("L1Q2.out")) { // Se o arquvivo de saída não existir, o cria
    fileCreate("L1Q2.out");
  }

  stack * mainStack = malloc(sizeof(stack)); // Stack onde ficarão os elementos
  init(mainStack);
  stack * tmpStack = malloc(sizeof(stack)); // Stack auxiliar
  init(tmpStack);

  FILE * fileIn = fopen("L1Q2.in", "r");
  FILE * fileOut = fopen("L1Q2.out", "w");

  char * line = malloc(lineMaxSize * sizeof(char));
  char * slice;
  const char * separator = " ";  // Utiliza um espaço em branco commo separador

  int popT = 0;
  fgets(line, lineMaxSize, fileIn);
  while(line != NULL) { // Cada linha do arquivo é lida e armazenada em line
    slice = strtok(line, separator);
    push(mainStack, slice); // O primeiro elemento da pilha é inserido sem verificar a ordem
    fprintf(fileOut, "%s%s%c", "push-", slice, ' ');
    slice = strtok(NULL, separator); // Em seguida, passa para o próximo elemento, que será testado
    while(slice != NULL) { // Percorre cada elemento na linha atual
      char * strTmp = (char *) malloc((strlen(slice) + 1) * sizeof(char));
      strcpy(strTmp, slice);
      for(int i = 0; strTmp[i] != '\0'; i++ ) { // Se o elemento for o último da linha, retira o caractere \n
        if(strTmp[i] == '\n') {
          strTmp[i] = '\0';
          break;
        }
      }
      if(strcmp(strTmp, mainStack -> tail -> key) < 0) { // Verifica se o elemento atual vem antes do elemento no topo da piha
        node * x = malloc(sizeof(node)); // Cria um node temporário para percorrer a lista
        x = mainStack -> tail;
        char * strAux = (char *)malloc((strlen(strTmp) + 1) * sizeof(char));
        strcpy(strAux, strTmp); // Salva o elemento a ser inserido numa string auxiliar
        while(x != NULL) { // Percorre a lista retirando os elementos que vem depois do elemento a ser inserido e
          if((strcmp(strAux, x -> key) < 0)) {
            push(tmpStack, x -> key); // Cada elemento retirado é salvo numa pilha temporária para ser inserido novamente depois
            x = x -> prev;
            pop(mainStack);
            popT ++;
            continue;
          }
          break;
        }
        fprintf(fileOut, "%d%c%s%c", popT, 'x',"-pop",' '); // Reporta quantas operações pop realizou
        popT = 0;
        push(mainStack, strTmp); // Insere o elemento atual na  posição correta da pilha
        fprintf(fileOut, "%s%s%c", "push-", strTmp, ' ');
        x = tmpStack -> tail; // X é utilizado para percorrer a pilha secundária desde o final até o começo
        while(x != NULL) {
          fprintf(fileOut, "%s%s%c", "push-", x -> key, ' ');
          push(mainStack, x -> key); // Insere todos os elementos de volta na lista principal e os retira da secundária
          x = x -> prev;
          pop(tmpStack);
        }
        free(x); // Libera x e a string auxiliar
        free(strAux);
      } else { //Se o elemento estiver na posição correta, o insere na lista sem alterar os demais
        fprintf(fileOut, "%s%s%c", "push-", strTmp, ' ');
        push(mainStack, strTmp);
      }
      slice = strtok(NULL, separator);
      free(strTmp);
    }
    if(fgets(line, lineMaxSize, fileIn) != NULL) {
      fputc('\n', fileOut);
    } else {
      break;
    }
    while(mainStack -> tail != NULL) { // Libera todos os elementos da pilha principal
      pop(mainStack);
    }
  }

  // Libera todos os ponteiros e fecha os arquivos
  free(tmpStack);
  free(mainStack);
  fclose(fileIn);
  fclose(fileOut);
  return 0;
}