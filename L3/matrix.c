#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

#include "multiply_matrix.h"

void printHelper(){
	printf("\n>>>Helper<<<\n");
	printf("-a Filename: Filename of matrix a\n");
	printf("-b Filename: Filename of matrix b\n"); 
	printf("-c Filename: Filename for the Output from the result\n");
	printf("-p: activates the work with threads\n");
	printf("-t Number: Number of Threads to create (WITHOUT -p the Threads will NOT created!)\n");
    printf("-v: \'verbose\', activates extra Output\n");
    printf("-h: activates this Helper\n");
    printf("./matrix -a [File] -b [File] -c [File] are neccessary!");
    printf("Programm ends now\n\n");
    exit(0);
}

void free_matrix(Matrix *tmp){
	for(int i = 0; i < tmp->rows; i++){
		free(tmp->matrix[i]);
	}
	free(tmp->matrix);
}

int main(int argc, char *argv[]){
	char *matrixA = NULL, *matrixB = NULL, *result = NULL;
	Matrix *matr1 = NULL;
	Matrix *matr2 = NULL;
	Matrix *res = NULL;
	FILE *output = NULL;
	int NumberOfThreads = 1;
	int read = 0;
	int verbose = 0;
	int threadactivate = 0;

	if(argc < 7){
		printHelper();
	}

	/*read the arguments*/
	while((read = getopt(argc, argv, "a:b:c:t:vhp")) != -1){
		switch(read){
			char *end = NULL;
			int l;
			case 'h':
				printHelper();
				break;
			case 'a':
				matrixA = optarg;
				break;
			case 'b':
				matrixB = optarg;
				break;
			case 'c':
				result = optarg;
				if(result != NULL){
					output = fopen(result, "r");
					if(output == NULL){
						printf("Creating file %s\n", result);
						output = fopen(result, "w");
						if(output == NULL){
							printf("Cant open file: %s!\n", result);
							printHelper();
						}
					} else {
						printf("Overwrite file %s\n", result);
						output = fopen(result, "w");
						if(output == NULL){
							printf("Cant open file: %s!\n", result);
							printHelper();
						}
					}
				}
				break;
			case 't':
				if((l = (int)strtol(optarg, &end, 10))){
					if(l < 0){
						printf("Please only positive Values greater 0!\n");
						printHelper();
					}
					NumberOfThreads = l;
				} else {
					printf("-t needs a Number (greater 0)!\n");
					printHelper();
				}
				break;
			case 'v':
				verbose = 1;
				break;
			case 'p':
				threadactivate = 1;
				break;
			default:
				printHelper();
		}
	}

	if(matrixA != NULL & matrixB != NULL){
		matr1 = readMatrix(matrixA);
		matr2 = readMatrix(matrixB);
		if(verbose == 1){
			printf("MatrixA and B readed!\n");
		}
		if(matr1 == NULL || matr2 == NULL){
			printf("Error! Coudnt read the Matrix!\n");
			printHelper();
		}

		if(matr1->columns != matr2->rows){
			printf("Cant multiply the Matrix!\n");
			printf("The columns from MatrixA must be the same like the Rows from Matrix2!\n");
			printHelper();		}
	}

	/*if the threads not activated*/
	if(threadactivate != 1){
		if(verbose == 1){
			printf("Threads not activated!\n");
		}
		NumberOfThreads = 0;
	}

	/*calculate it*/
	res = multiplyMatrix (matr1, matr2, NumberOfThreads);
	if(output != NULL){
		for(int i = 0; i < res->rows; i++){
			for (int j = 0; j < res->columns; j++){
				fprintf(output, "%.3f ", res->matrix[i][j]);
				if(verbose == 1){
					printf("%.3f ", res->matrix[i][j]);
				}
			}
			fprintf(output,"\n");
			if(verbose == 1){
				printf("\n");
			}
		}
	} else if(verbose == 1){
		printf("There isnt a file to write in!\n");
		printf("The Result: \n");
		for(int i = 0; i < res->rows; i++){
			for (int j = 0; j < res->columns; j++){
				printf("%.3f ", res->matrix[i][j]);
			}
			printf("\n");
		}
	}

	/*free all*/
	free_matrix(matr1);
	free_matrix(matr2);
	free_matrix(res);
	free(matr1);
	free(matr2);
	free(res);
	return 0;
}
