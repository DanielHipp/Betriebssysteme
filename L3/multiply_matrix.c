#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>

#include "multiply_matrix.h"

/*struct for the pcreate_thread - command, because you cant give more than one Argument to this command*/
typedef struct {
	Matrix *a;
	Matrix *b;
	Matrix *result;
	int start;
	int number;
}threadargs;

/*initialise a matrix*/
double **init_matrix(int rows, int columns){
	double **matr = (double **) malloc (rows * sizeof(double*));
	for(int i = 0; i < rows; i++){
		matr[i] = (double *) malloc (columns * sizeof(double));
	}
	return matr;
}

/*initialise a thread*/
void *init_thread(void *args){
	threadargs *tmp = args;
	double result = 0;
	int startrow = tmp->start/tmp->result->rows;
	int startcolumn = tmp->start%tmp->result->rows;
	int numberOfCircles = tmp->number;
	int count = 0;
	for (int i = startrow; i < tmp->result->rows; i++)  {
        for (int j = startcolumn; j < tmp->result->columns; j++) {
            startcolumn = 0;
            if(count < numberOfCircles) {
                result = multiplyRowColumn(tmp->a, i, tmp->b, j);
                tmp->result->matrix[i][j] = result;
            }
            count++;
        }
    }

    return NULL;
}
/*read a matrix*/
Matrix *readMatrix(const char filename[]){
	Matrix *matr = (Matrix *) malloc(sizeof(Matrix));
	matr->rows = 0;
	matr->columns = 0;
	char * line = NULL;		//saves the String for a line
	char * t;				//needed for the funktion strtok
	ssize_t read;
	size_t length = 0;

	FILE *f = fopen(filename, "r");
	if(f == NULL){
		printf("File %s cant be opened!", filename);
		exit(1);
	}

	/*while-Circle to count the rows and columns of the matrix*/
	while((read = getline(&line, &length, f)) != -1){
		matr->rows++;
		if(matr->columns == 0){		//if the columns not null, you dont need to count them again
			t = strtok(line, " ");
			while(t != NULL){
				matr->columns++;
				t = strtok(NULL, " ");
			}
		}
	}
	/*initialise the matrix*/
	matr->matrix = init_matrix(matr->rows, matr->columns);

	fclose(f);						//close the file to read it again from begin
	f = fopen(filename, "r");
	int columnCounter = 0;
	int rowCounter = 0;
	double value;
	int check = 0;

	/*seconds while - Circle to fill the matrix with values*/
	while((read = getline(&line, &length, f)) != -1){
		t = strtok(line, " ");
		while(t != NULL && columnCounter < matr->columns){
			check = sscanf(t, "%lf", &value);						//read the value in t (the return Value from strtok)
			if(check == 0){
				printf("scanf failed! Cant read number in row %d, column %d in file %s!", (rowCounter + 1), (columnCounter + 1), filename);
				return NULL;
			}
			matr->matrix[rowCounter][columnCounter] = value;	//add the value
			columnCounter++;
			t = strtok(NULL, " ");
		}
		rowCounter++;
		columnCounter = 0;										
	}

	fclose(f);
	free(line);
	return matr;
}

/*calculate a result - matrix*/
Matrix *multiplyMatrix(Matrix *a, Matrix *b, int threads){
	Matrix *result = (Matrix *) malloc (sizeof(Matrix *));
	result->rows = a->rows;
	result->columns = a->columns;
	result->matrix = init_matrix(result->rows, result->columns);

	int rowsA = a->rows;
	int columnsA = a->columns; 
	int row = 0;
	int column = 0;
	double res = 0.0;
	/*if threads not allowed*/
	if(threads == 0){
		while(row < rowsA){
			while(column < columnsA){
				res = multiplyRowColumn(a, row, b, column);
				result->matrix[row][column] = res;
				column++;
			}
			row++;
			column = 0;
		}
	/*if threads allowed*/
	} else if(threads > 0) {
		pthread_t threadArray[threads];
		int threadCounter = 0;						//Count if the Threads are more or less or equal of the calculations (0 = equal, 1 = less, 2 = more)
		int check;
		int start;									//startpoint of the thread
		int number;									//Number of circles the threads must do
		threadargs *args[threads];					//the array with the pointer to a struct with the needed values for the threads
		if(threads > (a->rows * b->columns)){
			threadCounter = 2;

		} else if(threads < (a->rows * b->columns)){
			threadCounter = 1;
		}
		for(int i = 0; i < threads; i++){
			args[i] = malloc (sizeof(threadargs));
			args[i]->a = a;
			args[i]->b = b;
			args[i]->result = result;
			/*if there are less threads than needed Calculations*/
			if(threadCounter == 1){
				start = ((a->rows * b->columns) / threads) * i;
				int tmp = (a->rows * b->columns) / threads; 
				number = tmp;
				if((threads - i) == 1){
					number = tmp + ((a->rows * b->columns)%threads);
				}
			/*if there are more threads than needed Calculations*/
			} else if(threadCounter == 2){
				if(i <= (a->rows * b->columns)){
					start = i;
				} else {
					start = i - (a->rows * b ->columns);
				}
				number = 1;
			} else if(threadCounter == 0){
				start = i;
				number = 1;
			}
			args[i]->start = start;
			args[i]->number = number;
		}

		/*create all threads*/
		for (int i = 0; i < threads; i++){
			check = pthread_create(&threadArray[i], NULL, init_thread, (void *) args[i]);
			if(check != 0){
				printf("Error! coudnt create thread number %d! \n", (i+1));
				exit(-1);
			}
		}

		/*join all threads*/
		for(int i = 0; i < threads; i++){
			check = pthread_join(threadArray[i], NULL);
			if(check != 0){
				printf("Error! coudnt join thread number %d! \n", (i+1));
				exit(-1);
			}
			free (args[i]);
		}
	} else {
		printf("Only a positive amount of Threads greater 0!");
		return NULL;
	}

	return result;
}

double multiplyRowColumn(Matrix *a, int row, Matrix *b, int column){
	double vectorA[a->columns];
	double vectorB[b->rows];
	double result = 0;

	/*create vector from matrix a*/
	for(int i = 0; i < a->columns; i++){
		vectorA[i] = a->matrix[row][i];
	}

	/*create vector from matrix b*/
	for(int i = 0; i < b->rows; i++){
		vectorB[i] = b->matrix[i][column];
	}

	/*calculate the result of the multiplication*/
	for(int i = 0; i < a->columns; i++){
		result += vectorA[i] * vectorB[i];
	}

	return result;
}
