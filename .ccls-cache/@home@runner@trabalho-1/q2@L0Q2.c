# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <math.h>
# define lineMaxSize 500
# define maxPoints 500

// A data structure that represents a "cartesian point"

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

int main(){
  





  return EXIT_SUCCESS;
}
