# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define lineMaxSize 500
# define MAX_LISTS 50
# define MAX_NUMBERS 100

typedef struct{
  int sum;
  int index;
  int numberList[MAX_NUMBERS];
} list;


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


void insertionSort(list * input, int listSize) {
    for (int i = 1; i < listSize; i++) {
        list key = input[i];
        int j = i - 1; 

        while (j >= 0 && key.sum < input[j].sum) {
            input[j + 1] = input[j];
            j--; 
        }

        input[j + 1] = key;
    }
}


void megaInsertion(list * input){
  for (int i = 1; i < input->index; i++) {
        int key = input->numberList[i];
        int j = i - 1; 
        while (j >= 0 && key < input->numberList[j]) {
            input->numberList[j + 1] = input->numberList[j];
            j--; 
        }
        input->numberList[j + 1] = key;
    }
}


void saveToFile(list * input, int listSize, FILE * fileOut, int isLast){
  insertionSort(input, listSize);
  for(int i = 0; i < listSize; i++){
    fprintf(fileOut, "%s", "start ");
    megaInsertion(&input[i]);
    for(int j = 0; j < input[i].index; j++){
      fprintf(fileOut, "%d ", input[i].numberList[j]);
    }
  }
  if(!isLast){
    fputc('\n', fileOut);
  }
}


int main(){
  if(!fileExists("L1Q1.in")){
    printf("> Input file not found!");
    return EXIT_FAILURE;
  }
  if(!fileExists("L1Q1.out")){
    fileCreate("L1Q1.out");
  }
  FILE * fileIn = fopen("L1Q1.in", "r");
  FILE * fileOut = fopen("L1Q1.out", "w");

  char * line = malloc(lineMaxSize * sizeof(char));
  char * slice;
  const char * separator = " ";
  int totalLists = 0;
  fgets(line, lineMaxSize, fileIn);
  while(line != NULL){
    slice = strtok(line, separator);
    list lineList[MAX_LISTS] = {0};
    while(slice != NULL){
      if(strcmp(slice, "start") == 0){
        slice = strtok(NULL, separator);
        while(strcmp(slice, "start") != 0){
          lineList[totalLists].numberList[lineList[totalLists].index] = atoi(slice);
          lineList[totalLists].sum += lineList[totalLists].numberList[lineList[totalLists].index] ;
          lineList[totalLists].index ++;
          slice = strtok(NULL, separator);
          if(slice == NULL){
            break;
          }
        }
        totalLists ++;
      }
    }
    if(fgets(line, lineMaxSize, fileIn) != NULL){
      saveToFile(lineList, totalLists, fileOut, 0);		
    }
    else{
      saveToFile(lineList, totalLists, fileOut, 1);	
      break;
    }
    totalLists = 0;
  }
  free(line);
  fclose(fileIn);
  fclose(fileOut);
  return EXIT_SUCCESS;
}
