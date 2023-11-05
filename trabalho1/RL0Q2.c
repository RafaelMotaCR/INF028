# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# define lineMaxSize 500
# define maxItems 100

/**
 * @brief a custom struct that represents a cartesian point.
 *
 * The struct 'point' is used to represents the coordinates
 * of a point in a cartesian plan, with the x and y coordinates.
 */

typedef struct point {
  float x;                 /** < x point coordinates */
  float y;                 /* < y point coordinates */
  float euclidianDistance; /** Euclidian distance from the origin*/
} point;

/**
 * @brief a custom struct that saves data of the file.
 *
 * The 'data' struct is used for store several kind of data
 * thats include integer numbers, floating points numbers,
 * strings, and points on a cartesian plan.
 */

typedef struct data {
	
  struct {
    int totalFloats; /** < Total number of floating points numbers stored. */
    float floatList[maxItems]; /** < list of floating points values. */
  } typeFloat;

  struct {
    int totalInts;         /** < Total number of integer numbers stored. */
    int intList[maxItems]; /** < list of integer points values. */
  } typeInt;

  struct {
    int totalStrings; /** < Total number of strings numbers stored. */
    char stringList[100][maxItems]; /** < list of strings */
  } typeString;

  struct {
    int totalPoints; /** < Total number of cartesian points stored. */
    point pointList[maxItems]; /** < list of points on a cartesian plan */
  } typePoint;

} data;

// Functions headers

float calcEuclidian(point point1, point point2);
int fileCreate(char path[]);
int fileExists(char path[]);
int isAlfa(char *input);
int isAlfaNum(char *input);
int isFloat(char *input);
int isInt(char *input);
int isPoint(char *input);
void saveToFile(data * input, FILE * fileOut);
point strToPoint(char * input);
int typeOf(char *input);

/**
 * @brief Calculates the euclidian distance between two cartesian points.
 *
 * This function receives two cartesian points 'point' and calculates
 * the euclidian distance between them.
 *
 * @param 'point1' the first cartesian point.
 * @param 'point2' the secund cartesian point.
 * @return the euclidian distance between the points.
 *
 * Exemple of use:
 * @code
 * float distance = calcEuclidian((2, -1), (8,6));
 * // The result will be 12.21.
 * @endcode
 */

float calcEuclidian(point point1, point point2) {
	float euclidianDistance = 0.00f;
	euclidianDistance = sqrt(pow(point1.x - point2.x, 2.00) + pow(point1.y - point2.y, 2.00));
	return euclidianDistance;
}

/**
 * @brief Create a file on the especified path.
 *
 * This function receives the path where should create the file
 * then trys to create it and returns sucesses or failure.
 *
 * @param 'path' indicates the path where the file should be created.
 * @return 1 if creates the file without trouble or 0 else.
 *
 * Exemple of use:
 * @code
 * char * paht = "l0Q1.out";
 * fileCreate(path);
 * FILE fileOut = fopen(path, "w");
 * // if the file was created with sucess, returns 1, else returns 0.
 * @endcode
 */

int fileCreate(char path[]) {
	FILE * fileCreate;
	fileCreate = fopen(path, "w");
	if (fileCreate == NULL) {
		return 0;
	}
	fclose(fileCreate);
	return 1;
}

/**
 * @brief Checks whether exists a file on the specified path.
 *
 * This function receives the path where should have a file
 * then trys to open it and returns sucess or failure.
 *
 * @param 'path' indicates the path where the file should exists.
 * @return 1 if open the file without trouble or 0 else.
 *
 * Exemple of use:
 * @code
 * char * paht = "l0Q1.out";
 * int test = fileExists(path);
 * FILE fileOut = fopen(path, "w");
 * // if the file was open with sucess, returns 1, else returns 0.
 * @endcode
 */

int fileExists(char path[]) {
	FILE * fileTest;
	fileTest = fopen(path, "r");
	if (fileTest == NULL) {
		return 0;
	}
	fclose(fileTest);
	return 1;
}

/**
 * @brief Checks wheter a string contains only alfabetic caracters.
 *
 * This function receives the a pointer to a string and cheks wheter
 * it contains only alfabetic caracters. The function will travel through
 * the intire string until enconter '\0' or a invalide caractter
 * then, returns 0 or 1.
 *
 * @param 'input' a pointer to a chain of caracters.
 * @return 1 if not encouters invalid caraters or 0 else.
 *
 * Exemple of use:
 * @code
 * char * string = "Rafael Mota";
 * isAlfa(string); // return 1
 *
 * @endcode
 */

int isAlfa(char * input) {
	for (int index = 0; input[index] != '\0' && input[index] != '\n'; index++) {
		if (!((input[index] >= 'a' && input[index] <= 'z') || input[index] >= 'A' && input[index] <= 'Z')) {
			return 0;
		}
	}
return 1;
}

/**
 * @brief Checks wheter a string contains only alfabetic caracters and numbers.
 *
 * This function receives the a pointer to a string and cheks wheter
 * it contains only alfabetic caracters and numbers. The function will travel
 * through the intire string until enconter '\0' or a invalide caractter then,
 * returns 0 or 1.
 *
 * @param 'input' a pointer to a chain of caracters.
 * @return 1 if not encouters invalid caraters or 0 else.
 *
 * Exemple of use:
 * @code
 * char * string = "Rafael Mota";
 * isAlfaNUm(string); // return 0
 *
 * @endcode
 */

int isAlfaNum(char * input) {
	if (isAlfa(input) || isInt(input)) {
		return 0;
	}
	for (int index = 0; input[index] != '\0' && input[index] != '\n'; index++) {
		if (!((input[index] >= 'a' && input[index] <= 'z') || (input[index] >= 'A' && input[index] <= 'Z') || (input[index] >= '0' && input[index] <= '9'))) {
			return 0;
		}
	}
	return 1;
}


void insertionForFloat(data * input){
	for(int i = 1; i <  input->typeFloat.totalFloats; i++){
		int j = i - 1;
		float key = input->typeFloat.floatList[i];
		while(j >= 0 && key < input->typeFloat.floatList[j]){
			input->typeFloat.floatList[j + 1] = input->typeFloat.floatList[j];
			j--;
		}
		input->typeFloat.floatList[j + 1] = key;
	}
}


void insertionForInt(data * input){
	for(int i = 1; i < input->typeInt.totalInts; i ++){
		int j = i - 1;
		int key = input->typeInt.intList[i];
		while(j >= 0 && key < input->typeInt.intList[j]){
			input->typeInt.intList[j + 1] = input->typeInt.intList[j];
			j--;
		}
		input->typeInt.intList[j + 1] = key;
	}
}


void insertionForPoint(data * input){
	for(int i = 1; i < input->typePoint.totalPoints; i++ ){
		int j = i - 1;
		point key = input->typePoint.pointList[i];
		while(j >= 0 && key.euclidianDistance < input->typePoint.pointList[j].euclidianDistance){
			input->typePoint.pointList[j + 1] = input->typePoint.pointList[j];
			j--;
		}
		input->typePoint.pointList[j + 1] = key; 
	}
}


void insertionForString(data * input){
	for(int i = 1; i < input->typeString.totalStrings; i++){
		int j = i - 1;
		char key[50];
		strcpy(key, input->typeString.stringList[i]);
		while(j >= 0 && (strcmp(input->typeString.stringList[j], key) > 0)){
			strcpy(input->typeString.stringList[j + 1], input->typeString.stringList[j]);
			j--;
		}
		strcpy(input->typeString.stringList[j + 1], key);
	}
}


/**
 * @brief Checks wheter a string represents a floating point number.
 *
 * This function receives the a pointer to a string and cheks wheter
 * it contains only dots, commas and numbers. The function will travel through
 * the intire string until enconter '\0' or a invalide caractter
 * then, returns 0 or 1. Furthermore, the function acepts '-' and '+' caracters
 * as well acepts dots.
 *
 * @param 'input' a pointer to a chain of caracters.
 * @return 1 if not encouters invalid caraters or 0 else.
 *
 * Exemple of use:
 * @code
 * char * string = "1.227";
 * isFloat(string); // return 1
 *
 * @endcode
 */

int isFloat(char * input) {
	int contPoint = 0;
	for (int index = 0; input[index] != '\0' && input[index] != '\n'; index++) {
		if (input[index] == '.') {
			contPoint++;
			continue;
		}
		if ((input[index] == '-') || (input[index] == '+')) {
			continue;
		}
		if ((!(input[index] >= '0' && input[index] <= '9')) || contPoint > 1) {
			return 0;
		}
	}
return 1;
}

/**
 * @brief Checks wheter a string represents a integer number.
 *
 * This function receives the a pointer to a string and cheks wheter
 * it contains only num caracters. The function will travel through
 * the intire string until enconter '\0' or a invalide caractter
 * then, returns 0 or 1. Furthermore, the function acepts '-' and '+' caracters.
 *
 * @param 'input' a pointer to a chain of caracters.
 * @return 1 if not encouters invalid caraters or 0 else.
 *
 * Exemple of use:
 * @code
 * char * string = "7745";
 * isIn(string); // return 1
 *
 * @endcode
 */

int isInt(char * input) {
	for (int index = 0; input[index] != '\0' && input[index] != '\n'; index++) {
		if ((input[index] == '-') || (input[index] == '+')) {
			continue;
		}
		if (!((input[index] >= '0' && input[index] <= '9'))) {
			return 0;
		}
	}
	return 1;
}

/**
 * Checks whether a string represents the coordinates of a point on a Cartesian
 * plane.
 *
 * This function checks whether the string contains only integer or floating
 * point numbers, along with special characters that can be used to represent
 * points, as parentheses, period or comma.
 *
 * @param input The string to be checked.
 * @return 1 if the string represents a valid point, 0 otherwise.
 *
 * Exemple of use:
 * @code
 * char * string = "(-7.547,-9874)";
 * isPoint(string); // return 1
 *
 * @endcode
 */

int isPoint(char * input) {
	for (int index = 0; input[index] != '\0' && input[index] != '\n'; index++) {
		if ((input[index] == 40) || (input[index] == 41) || (input[index] == '.') ||(input[index] == ',') || (input[index] == '+') ||(input[index] == '-')) {
			continue;
			}
		if (!((input[index] >= '0' && input[index] <= '9'))) {
			return 0;
		}
	}
	return 1;
}


void saveToFile(data * input, FILE * fileOut){
	
	insertionForFloat(input);
	insertionForInt(input);
	insertionForPoint(input);
	insertionForString(input);

  if(input->typeString.totalStrings > 0){
  	fprintf(fileOut, "%s", "str : ");
  	for(int index = 0; index < input->typeString.totalStrings; index++){
  		fprintf(fileOut, "%s", input->typeString.stringList[index]);
  		fputc(' ', fileOut);
  	}
  }

  if(input->typeInt.totalInts > 0){
  	fprintf(fileOut, "%s", "int : ");
  	for(int index = 0; index < input->typeInt.totalInts; index++){
  		fprintf(fileOut, "%d", input->typeInt.intList[index]);
  		fputc(' ', fileOut);
  	}
  }

  if(input->typeFloat.totalFloats > 0){
  	fprintf(fileOut, "%s", "float : ");
  	for(int index = 0; index < input->typeFloat.totalFloats; index++){
  		fprintf(fileOut, "%g", input->typeFloat.floatList[index]);
  		fputc(' ', fileOut);
  	}	
  }

  if(input->typePoint.totalPoints > 0){
  	fprintf(fileOut, "%s", "p : ");
  	for(int index = 0; index < input->typePoint.totalPoints; index++){
  		fprintf(fileOut, "(%g,%g)", input->typePoint.pointList[index].x, input->typePoint.pointList[index].y);
  		fputc( ' ', fileOut);
  	}	
  	fputc('\n', fileOut);
  }
  
}


point strToPoint(char * input){
	char * n1 = malloc((strlen(input) + 1));
	char * n2 = malloc((strlen(input) + 1));
	
	point convertedPoint = {0.0f};
	point zero = {0.0f};
	
	int index, index2, j, k;
	
	for(index = 1, j = 0; input[index] != ','; index++, j++){
		n1[j] = input[index];
	}
	n1[j] = '\0';
	
	for(index2 = index + 1, k = 0; input[index2] != 41; index2++, k++){
		n2[k] = input[index2];
	}
	n2[k] = '\0';
	
	if(!(isInt(n1) || isFloat(n1))){
		return zero;
	}
	
	if(!(isInt(n2) || isFloat(n2))){
		return zero;
	}
	
	convertedPoint.x = atof(n1);
	convertedPoint.y = atof(n2);
	convertedPoint.euclidianDistance = calcEuclidian(convertedPoint, zero);
	
	free(n1);
	free(n2);
	
	return convertedPoint;
}


/**
 * Checks the type of a string.
 *
 * This function checks the typeof a string and returns a integer number that
 * represents that or 0 if the type couldn't be find;
 *
 * @param input The string to be checked.
 * @return 1 if the string contains only alfabetic caracters.
 * @return 2 if the string contains only alfabetic caracters and numbers.
 * @return 3 if the string contains a integer number.
 * @return 4 if the string contains a floating point number.
 * @return 5 if the string represents point on a cartesian plan.
 * @return 0 if couldn't finde the type of the string.
 *
 * Exemple of use:
 * @code
 * char * string = "(-7.547,-9874)";
 * isPoint(string); // return 5;
 *
 * @endcode
 *
 * @endcode
 */

int typeOf(char *input) {
	if (isAlfa(input)) {
		return 1;
	}
	else if (isAlfaNum(input)) {
		return 2;
	}
	else if (isInt(input)) {
		return 3;
	}
	else if (isFloat(input)) {
		return 4;
	}
	else if (isPoint(input)) {
		return 5;
	}
	else {
		return 0;
	}
}


int main() {
	
	// Checks if the input file exists
	// If not, close the program
	
	if(!fileExists("L0Q2.in")) {
	printf("> Input file not found!");
	return EXIT_FAILURE;
	}
	
	// Checks if the output file exists
	// If not, create the file 
	
	if(!fileExists("L0Q2.out")) {
	fileCreate("L0Q2.out");
	}
	
	// Open both files in diferent variables
	
	FILE * fileIn = fopen("L0Q2.in", "r");
	FILE * fileOut = fopen("L0Q2.out", "w");
	
	// Declaration of variables
	
	char * line = malloc(lineMaxSize * sizeof(char));
	char * slice;
	const char * separator = " ";
	// Read the input file line by line
	
	while (fgets(line, lineMaxSize, fileIn) != NULL) { 
	    slice = strtok(line, separator);                
	    data saveData = {0};
	    while (slice != NULL) {
	    	switch (typeOf(slice)) {
	    		case 1: {
	        		strcpy(saveData.typeString.stringList[saveData.typeString.totalStrings], slice);
	        		saveData.typeString.totalStrings++;
				    break;
	      		}
				case 3: {
					saveData.typeInt.intList[saveData.typeInt.totalInts] = atoi(slice);
					saveData.typeInt.totalInts++;
					break;
				}
				case 4: {
					saveData.typeFloat.floatList[saveData.typeFloat.totalFloats] = atof(slice);
					saveData.typeFloat.totalFloats++;
					break;
	     		}
				case 5: {
					saveData.typePoint.pointList[saveData.typePoint.totalPoints] = strToPoint(slice);
					saveData.typePoint.totalPoints++;
					break;
				}
				default: {
					printf("ERROR");
					return EXIT_FAILURE;
					break;
	     		}	
	      	}
	      slice = strtok(NULL, separator);
		}
		saveToFile(&saveData, fileOut);
	}
	
	fclose(fileIn);
	fclose(fileOut);
	free(line);

  return EXIT_SUCCESS;
}
