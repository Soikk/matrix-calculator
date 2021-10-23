#include <stdio.h>
#include <stdlib.h>
#include "matrix-operations.h"


matrix_t matrices[3];

typedef enum operations{
	DISPLAY_MATRIX = 1,
	CREATE_MATRIX, CREATE_IDENTITY_MATRIX,

	IS_SQUARE, NEGATE, CREATE_SUBMATRIX, CALCULATE_DETERMINANT, CALCULATE_COFACTOR,
		CALCULATE_TRANSPOSE, CALCULATE_ADJUGATE, CALCULATE_INVERSE,

	FILL, ADD_N, SUBSTRACT_N, MULTIPLY_N, DIVIDE_N, RAISE_TO_N,

	ADD_M, SUBSTRACT_M, MULTIPLY_M, DIVIDE_M
} operation;

int handleInput(){
	int input = 0, s = 0;
	do{
		printf("Select operation\n");
		printf("\t0. Exit.\n");
		printf("\t1. Display matrix\n");
		printf("\t2. Create matrix\n");
		printf("\t3. Operations with a single matrix\n");
		printf("\t4. Operations with a matrix and a scalar\n");
		printf("\t5. Operations between 2 matrices\n");
		printf("\n");
		scanf("%d", &input);
		printf("\n");
		switch(input){
			case 0:
				return 0;
				break;
			case 1:
				printf("Display matrix\n");
				printf("Which matrix would you like to display?\n");
				do{
					printf("Matrix A (0), B (1) or C (2)? ");
					scanf("%d", &s);
				}while(s < 0 || s > 2);
				displayMatrix(matrices[s]);
				break;
			case 2:
				do{
					printf("Create matrix\n");
					printf("\t0. Go back\n");
					printf("\t1. Create custom matrix\n");
					printf("\t2. Create identity matrix\n");
					scanf("%d", &input);
					switch(input){
						case 1:
							return CREATE_MATRIX;
							break;
						case 2:
							return CREATE_IDENTITY_MATRIX;
							break;
					}
				}while(input);
				break;
			case 3:
				do{
					printf("Operations with a single matrix\n");
					printf("\t0. Go back\n");
					printf("\t1. Check if matrix is square\n");
					printf("\t2. Negate a matrix\n");
					printf("\t3. Create a submatrix out of a matrix\n");
					printf("\t4. Calculate the determinant of a matrix\n");
					printf("\t5. Calculate the cofactor matrix of a matrix\n");
					printf("\t6. Calculate the transpose matrix of a matrix\n");
					printf("\t7. Calculate the adjugate matrix of a matrix\n");
					printf("\t8. Calculate the inverse of a matrix\n");
					scanf("%d", &input);
					switch(input){
						case 1:
							return IS_SQUARE;
							break;
						case 2:
							return NEGATE;
							break;
						case 3:
							return CREATE_SUBMATRIX;
							break;
						case 4:
							return CALCULATE_DETERMINANT;
							break;
						case 5:
							return CALCULATE_COFACTOR;
							break;
						case 6:
							return CALCULATE_TRANSPOSE;
							break;
						case 7:
							return CALCULATE_ADJUGATE;
							break;
						case 8:
							return CALCULATE_INVERSE;
							break;
					}
				}while(input);
				break;
			case 4:
				do{
					printf("Operations with a matrix and a scalar\n");
					printf("\t0. Go back\n");
					printf("\t1. Fill matrix with a number\n");
					printf("\t2. Add a number to a matrix\n");
					printf("\t3. Substract a number from a matrix\n");
					printf("\t4. Multiply matrix by a number\n");
					printf("\t5. Divide matrix by a number\n");
					printf("\t6. Raise matrix to the power of a number\n");
					scanf("%d", &input);
					switch(input){
						case 1:
							return FILL;
							break;
						case 2:
							return ADD_N;
							break;
						case 3:
							return SUBSTRACT_N;
							break;
						case 4:
							return MULTIPLY_N;
							break;
						case 5:
							return DIVIDE_N;
							break;
						case 6:
							return RAISE_TO_N;
							break;
					}
				}while(input);
				break;
			case 5:
				do{
					printf("Operations between 2 matrices\n");
					printf("\t0. Go back\n");
					printf("\t1. Add two matrices together\n");
					printf("\t2. Substract one matrix from another\n");
					printf("\t3. Multiply two matrices\n");
					printf("\t4. Divide two matrices\n");
					scanf("%d", &input);
					switch(input){
						case 1:
							return ADD_M;
							break;
						case 2:
							return SUBSTRACT_M;
							break;
						case 3:
							return MULTIPLY_M;
							break;
						case 4:
							return DIVIDE_M;
							break;
					}
				}while(input);
				break;
		}
		printf("\n");
		if(!input)
			input = -1;
	}while(input);
}

void matrixCalculator(int input){
	int s = 0, r = 0, c = 0, d = 0, f = 0;
	float n;
	switch(input){
		case CREATE_MATRIX:
			printf("Creating a new matrix\n");
			printf("Insert the rows of the matrix: ");
			scanf("%d", &r);
			printf("Insert the columns of the matrix: ");
			scanf("%d", &c);
			printf("Where do you want to store the newly created matrix?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			matrices[s] = createMatrix(r, c);
			initializeMatrix(&matrices[s]);
			break;
		case CREATE_IDENTITY_MATRIX:
			printf("Creating a new identity matrix\n");
			printf("Insert the dimensions of the matrix: ");
			scanf("%d", &d);
			printf("Where do you want to store the newly created matrix?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			matrices[s] = identityMatrix(d);
			break;

		case IS_SQUARE:
			printf("Which matrix do you want to check if it is square?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			printf("Is matrix %s square? %s\n",
				(s==0)?"A":(s==1)?"B":"C", (isSquare(matrices[s])?"Yes":"No"));
			break;
		case NEGATE:
			printf("Which matrix do you wanna negate?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			negateMatrix(matrices[s]);
			break;
		case CREATE_SUBMATRIX:
			printf("Out of which matrix would you like to create a submatrix?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			// TODO: not remove any
			printf("Which row would you like to remove? From 0 to %d\n", matrices[s].rows-1);
			scanf("%d", &r);
			printf("Which columns would you like to remove? From 0 to %d\n", matrices[s].columns-1);
			scanf("%d", &c);
			matrices[s] = createSubmatrix(matrices[s], r, c);
			break;
		case CALCULATE_DETERMINANT:
			printf("Of which matrix would you like to calculate the determinant of?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			printf("Determinant of matrix %s: %d\n",
				(s==0)?"A":(s==1)?"B":"C", determinant(matrices[s]));
			break;
		case CALCULATE_COFACTOR:
			printf("Of which matrix would you like to calculate the cofactor matrix of?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			printf("Where would you like to store the resulting cofactor matrix?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &d);
			}while(d < 0 || d > 2);
			matrices[d] = cofactor(matrices[s]);
			break;
		case CALCULATE_TRANSPOSE:
			printf("Of which matrix would you like to calculate the transpose matrix of?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			printf("Where would you like to store the resulting transpose matrix?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &d);
			}while(d < 0 || d > 2);
			matrices[d] = transpose(matrices[s]);
			break;
		case CALCULATE_ADJUGATE:
			printf("Of which matrix would you like to calculate the adjugate matrix of?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			printf("Where would you like to store the resulting adjugate matrix?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &d);
			}while(d < 0 || d > 2);
			matrices[d] = adjugate(matrices[s]);
			break;
		case CALCULATE_INVERSE:
			printf("Of which matrix would you like to calculate the inverse matrix of?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			printf("Where would you like to store the resulting inverse matrix?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &d);
			}while(d < 0 || d > 2);
			matrices[d] = inverse(matrices[s]);
			break;

		case FILL:
			printf("What matrix would you like to fill with a number?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			printf("With which number would you like to fill matrix %s?\n",
				(s==0)?"A":(s==1)?"B":"C");
			scanf("%f", &n);
			matrices[s] = fillN(matrices[s], n);
			break;
		case ADD_N:
			printf("What matrix would you like to add a number to?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			printf("With which number would you like to add to matrix %s?\n",
				(s==0)?"A":(s==1)?"B":"C");
			scanf("%f", &n);
			matrices[s] = addN(matrices[s], n);
			break;
		case SUBSTRACT_N:
			printf("What matrix would you like to substract a number from?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			printf("With which number would you like to substract from matrix %s?\n",
				(s==0)?"A":(s==1)?"B":"C");
			scanf("%f", &n);
			matrices[s] = substractN(matrices[s], n);
			break;
		case MULTIPLY_N:
			printf("What matrix would you like to multiply by a number?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			printf("With which number would you like to multiply matrix %s by?\n",
				(s==0)?"A":(s==1)?"B":"C");
			scanf("%f", &n);
			matrices[s] = multiplyByN(matrices[s], n);
			break;
		case DIVIDE_N:
			printf("What matrix would you like to fill divide by a number?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			printf("With which number would you like to divide matrix %s by?\n",
				(s==0)?"A":(s==1)?"B":"C");
			scanf("%f", &n);
			matrices[s] = divideByN(matrices[s], n);
			break;
		case RAISE_TO_N:
			printf("What matrix would you like to raise to the power of a number?\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			printf("With which number would you like to raise matrix %s to?\n",
				(s==0)?"A":(s==1)?"B":"C");
			scanf("%f", &n);
			matrices[s] = raiseMatrixToN(matrices[s], n);
			break;

		case ADD_M:
			printf("Which two matrices would you like to add up?\n");
			printf("1st matrix\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &d);
			}while(d < 0 || d > 2);
			printf("2nd matrix\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &f);
			}while(f < 0 || f > 2);
			printf("In what matrix would you like to store the resulting matrix of adding up matrices %s and %s?\n",
				(d==0)?"A":(d==1)?"B":"C", (f==0)?"A":(f==1)?"B":"C");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			matrices[s] = addMatrices(matrices[d], matrices[f]);
			break;
		case SUBSTRACT_M:
			printf("Which two matrices would you like to substract?\n");
			printf("1st matrix\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &d);
			}while(d < 0 || d > 2);
			printf("2nd matrix\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &f);
			}while(f < 0 || f > 2);
			printf("In what matrix would you like to store the resulting matrix of substracting matrices %s and %s?\n",
				(d==0)?"A":(d==1)?"B":"C", (f==0)?"A":(f==1)?"B":"C");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			matrices[s] = substractMatrices(matrices[d], matrices[f]);
			break;
		case MULTIPLY_M:
			printf("Which two matrices would you like to multiply?\n");
			printf("1st matrix\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &d);
			}while(d < 0 || d > 2);
			printf("2nd matrix\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &f);
			}while(f < 0 || f > 2);
			printf("In what matrix would you like to store the resulting matrix of multiplying matrices %s and %s?\n",
				(d==0)?"A":(d==1)?"B":"C", (f==0)?"A":(f==1)?"B":"C");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			matrices[s] = multiplyMatrices(matrices[d], matrices[f]);
			break;
		case DIVIDE_M:
			printf("Which two matrices would you like to divide?\n");
			printf("1st matrix\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &d);
			}while(d < 0 || d > 2);
			printf("2nd matrix\n");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &f);
			}while(f < 0 || f > 2);
			printf("In what matrix would you like to store the resulting matrix of dividing matrices %s and %s?\n",
				(d==0)?"A":(d==1)?"B":"C", (f==0)?"A":(f==1)?"B":"C");
			do{
				printf("Matrix A (0), B (1) or C (2)? ");
				scanf("%d", &s);
			}while(s < 0 || s > 2);
			matrices[s] = divideMatrices(matrices[d], matrices[f]);
			break;
	}
	printf("Matrix %s:\n", (s==0)?"A":(s==1)?"B":"C");
	displayMatrix(matrices[s]);
	printf("\n");
}

int main(){

	for(int i = 0; i < 3; i++)
		matrices[i] = createMatrix(1, 1);

	int input = 0;
	do{
		input = handleInput();
		matrixCalculator(input);
	}while(input);

	return 0;
}