# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <math.h>
# define lineMaxSize 500
# define maxPoints 500

// A data structure that represents a "point"

typedef struct point{
  float x;
  float y;
  float euclidianDistance;
} point;


// My functions :)

float calcEuclidian(point point1, point point2){
	float euclidianDistance = 0.00f;
	euclidianDistance = sqrt(pow(point1.x - point2.x, 2.00) + pow(point1.y - point2.y, 2.00));
	return euclidianDistance;
}


int fileCreate(char path[]){
	FILE * fileCreate;
	fileCreate = fopen(path, "w");
	if(fileCreate == NULL){
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


void saveVector(point * input, int inputSize, FILE * fileIn){
  float shortcut = calcEuclidian(input[0], input[inputSize - 1]);
  float distance = 0.0f;

  
  for(int index = 1; index < inputSize; ++ index){
    distance += calcEuclidian(input[index - 1], input[index]);;
  }

  
  for(int i = 1; i < inputSize; i++ ){
    point key = input[i];
    int j = i - 1;
    while(j >= 0 && input[j].euclidianDistance > key.euclidianDistance){
      input[j + 1] =  input[j];
      j--;
    }
    input[j + 1] = key;
  }

  
  fprintf(fileIn, "points ");
  
  for(int index = 0; index < inputSize; index++){
    fprintf(fileIn, "(%g,%g)", input[index].x, input[index].y);
    fprintf(fileIn, " ");
  }
  
  fprintf(fileIn, "distance: %.2f ", distance);
  fprintf(fileIn, "shortcut: %.2f\n", shortcut);
}


int main(){
	
	// Checks if the input file exists
	// If not, close the program
	
	if(!fileExists("L0Q1.in")){
		printf("> Input file not found!");
		return EXIT_FAILURE;
	}
	
	// Checks if the output file exists
	// If not, create the file 
	
	if(!fileExists("L0Q1.out")){
		fileCreate("L0Q1.out");
	}
	
	// Open both files in diferent variables
	
	FILE * fileIn  = fopen("L0Q1.in", "r");
	FILE * fileOut = fopen("L0Q1.out", "w"); /* ovo escrever */
	
	// Declaration of variables
	
	char * line = malloc(lineMaxSize * sizeof(char));
	char * slice;
	int iteration = 0;
	int pointsNum = 0;
  	const char * separator = "(,)";
  	float shortcut = 0.0f;
  	float distance = 0.0f;
	
	// Read the input file line by line
	
	while(fgets(line, lineMaxSize, fileIn) != NULL){ // That is correct!
		slice = strtok(line, separator); // That is correct!
		point points[maxPoints];
		while(slice != NULL){ // That is correct!
			if(strcmp(slice, "points ") == 0){
				slice = strtok(NULL, separator); // That is correct!
				continue;
			}

			float temp = 0.0f;
			point zero;
			zero.x = 0.0f;
			zero.y = 0.0f;
			zero.euclidianDistance = 0.0f;
			
			// Test the numbers and save them
			
			if(temp = atof(slice) != 0){
				if(iteration == 0){
					points[pointsNum].x = atof(slice);
					slice = strtok(NULL, separator); // That is correct!
					iteration = 1;
				}
				if(iteration == 1){
					points[pointsNum].y = atof(slice);
					slice = strtok(NULL, separator); // That is correct!
					iteration = 0;
				}
			}
			points[pointsNum].euclidianDistance = calcEuclidian(points[pointsNum], zero);
			pointsNum ++;
			slice = strtok(NULL, separator); // That is correct!
		}
    saveVector(points, pointsNum, fileOut);
    pointsNum = 0;
	}
  
	fclose(fileIn);
	fclose(fileOut);
	free(line);

	return EXIT_SUCCESS;
}
