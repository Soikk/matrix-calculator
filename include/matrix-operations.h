#include <stdio.h>
#include <stdlib.h>


typedef enum errors{
	NOT_EQUAL,
	NOT_MULTIPLIABLE,
	NOT_SQUARE,
	ZERO_DET,
	UNKNOWN
} error_t;

typedef struct matrix{
	size_t rows;
	size_t columns;
	float **matrix;
} matrix_t;


// Handles all of the different possible errors
matrix_t matrixError(error_t error);

// Creates a rows x columns matrix;
matrix_t createMatrix(size_t rows, size_t columns);

// Fills the matrix with values provided by the user
void initializeMatrix(matrix_t *m);

// Returns true if the matrix is square, false otherwise
int isSquare(matrix_t m);

// Displays the given matrix
void displayMatrix(matrix_t m);

// Returns the identity matrix n x n
matrix_t identityMatrix(size_t n);

// Returns a matrix of the same size as "m" filled with the number "n"
matrix_t fillN(matrix_t m, float n);

// Adds a number to all the positions of the matrix and returns the result
matrix_t addN(matrix_t m, float n);

// Substracts a number from all the positions of the matrix and returns the result
matrix_t substractN(matrix_t m, float n);

// Adds two matrices together and returns the result
matrix_t addMatrices(matrix_t a, matrix_t b);

// Negates all of the positions of the matrix and returns the result
matrix_t negateMatrix(matrix_t m);

// Substracts matrix "b" from "a" and returns the result
matrix_t substractMatrices(matrix_t a, matrix_t b);

// Multiplies all of the positions of the matrix by "n" and returns the result
matrix_t multiplyByN(matrix_t m, float n);

// Divides all of the positions of the matrix by "n" and returns the result
matrix_t divideByN(matrix_t m, float n);

// Multiplies matrix "a" by "b" and returns the result
matrix_t multiplyMatrices(matrix_t a, matrix_t b);

// Divides matrix "a" by "b" and returns the result
matrix_t divideMatrices(matrix_t a, matrix_t b);

// Raises the matrix to the nth power and returns the result
matrix_t raiseMatrixToN(matrix_t m, int n);

// Creates a submatrix from "matrix" without the column "column" and row "row" of "matrix"
matrix_t createSubmatrix(matrix_t m, size_t row, size_t column);

// Returns the determinant of the given (square) matrix
int determinant(matrix_t m);

// Returns the cofactor matrix of the given matrix
matrix_t cofactor(matrix_t m);

// Returns the transpose matrix of the given matrix
matrix_t transpose(matrix_t m);

// Returns the adjugate matrix of the given matrix
matrix_t adjugate(matrix_t m);

// Returns the inverse matrix of the given matrix
matrix_t inverse(matrix_t m);