#include "matrix-operations.h"


matrix_t matrixError(error_t error){
	switch(error){
		case NOT_EQUAL:
			perror("Matrices are not of the same dimensions\n");
			break;
		case NOT_MULTIPLIABLE:
			perror("Matrix A's number of columns is different to matrix B's number of rows\n");
			break;
		case NOT_SQUARE:
			perror("Matrix is not square");
			break;
		case ZERO_DET:
			perror("Determinant of the matrix should be 0\n");
			break;
		case UNKNOWN:
		default:
			perror("Unknown error\n");
	}
	return createMatrix(0, 0);
}
// Creates a rows x columns matrix;
matrix_t createMatrix(size_t rows, size_t columns){
	matrix_t newmatrix;
	newmatrix.rows = rows;
	newmatrix.columns = columns;
	newmatrix.matrix = malloc(rows*sizeof(float*));
	for(size_t i = 0; i < rows; ++i)
		newmatrix.matrix[i] = calloc(columns,sizeof(float));
	return newmatrix;
}

// Fills the matrix with values provided by the user
void initializeMatrix(matrix_t *m){
	printf("Initializing %dx%d matrix\n", m->rows, m->columns);
	for(size_t r = 0; r < m->rows; ++r){
		printf("Please insert %d numbers for each of the columns of the %d%s row\n",
			m->columns, r+1, (r+1==1)?("st"):((r+1==2)?("nd"):((r+1==3)?("rd"):("th"))));
		for(size_t c = 0; c < m->columns; ++c){
			scanf("%f", &m->matrix[r][c]);
		}
	}
}

// Returns true if the matrix is square, false otherwise
int isSquare(matrix_t m){
	return m.rows == m.columns;
}

// Displays the given matrix
void displayMatrix(matrix_t m){
	for(size_t r = 0; r < m.rows; ++r){
		for(size_t c = 0; c < m.columns; ++c)
			printf("%3.3g ", m.matrix[r][c]);
		printf("\n");
	}
}

// Returns the identity matrix n x n
matrix_t identityMatrix(size_t n){
	matrix_t identityMatrix = createMatrix(n, n);
	for(size_t r = 0; r < n; ++r)
		for(size_t c = 0; c < n; ++c)
			if(r == c)
				identityMatrix.matrix[r][c] = 1;
	return identityMatrix; 
}

// Returns a matrix of the same size as "m" filled with the number "n"
matrix_t fillN(matrix_t m, float n){
	matrix_t filledmatrix = createMatrix(m.rows, m.columns);
	for(size_t r = 0; r < m.rows; ++r)
		for(size_t c = 0; c < m.columns; ++c)
			filledmatrix.matrix[r][c] = n;
	return filledmatrix;
}

// Adds a number to all the positions of the matrix and returns the result
matrix_t addN(matrix_t m, float n){
	matrix_t addedmatrix = createMatrix(m.rows, m.columns);
	for(size_t r = 0; r < m.rows; ++r)
		for(size_t c = 0; c < m.columns; ++c)
			addedmatrix.matrix[r][c] = m.matrix[r][c]+n;
	return addedmatrix;
}

// Substracts a number from all the positions of the matrix and returns the result
matrix_t substractN(matrix_t m, float n){
	matrix_t substractedmatrix = createMatrix(m.rows, m.columns);
	for(size_t r = 0; r < m.rows; ++r)
		for(size_t c = 0; c < m.columns; ++c)
			substractedmatrix.matrix[r][c] = m.matrix[r][c]-n;
	return substractedmatrix;
}

// Adds two matrices together and returns the result
matrix_t addMatrices(matrix_t a, matrix_t b){
	if(a.rows != b.rows || a.columns != b.columns)
		return matrixError(NOT_EQUAL);
	matrix_t addedmatrices = createMatrix(a.rows, b.columns);
	for(size_t r = 0; r < a.rows; ++r)
		for(size_t c = 0; c < a.columns; ++c)
			addedmatrices.matrix[r][c] = a.matrix[r][c] + b.matrix[r][c];
	return addedmatrices;
}

// Negates all of the positions of the matrix and returns the result
matrix_t negateMatrix(matrix_t m){
	matrix_t negatedmatrix = createMatrix(m.rows, m.columns);
	for(size_t r = 0; r < m.rows; ++r)
		for(size_t c = 0; c < m.columns; ++c)
			negatedmatrix.matrix[r][c] = -m.matrix[r][c];
	return negatedmatrix;
}

// Substracts matrix "b" from "a" and returns the result
matrix_t substractMatrices(matrix_t a, matrix_t b){
	return addMatrices(a, negateMatrix(b));
}

// Multiplies all of the positions of the matrix by "n" and returns the result
matrix_t multiplyByN(matrix_t m, float n){
	matrix_t multipliedmatrix = createMatrix(m.rows, m.columns);
	for(size_t r = 0; r < m.rows; ++r)
		for(size_t c = 0; c < m.columns; ++c)
			multipliedmatrix.matrix[r][c] = m.matrix[r][c]*n;
	return multipliedmatrix;
}

// Divides all of the positions of the matrix by "n" and returns the result
matrix_t divideByN(matrix_t m, float n){
	return multiplyByN(m, (float)1/n);
}

// Multiplies matrix "a" by "b" and returns the result
matrix_t multiplyMatrices(matrix_t a, matrix_t b){
	if(a.columns != b.rows)
		return matrixError(NOT_MULTIPLIABLE);
	matrix_t multipliedmatrices = createMatrix(a.rows, b.columns);
	for(size_t r = 0; r < multipliedmatrices.rows; ++r)
		for(size_t c = 0; c < multipliedmatrices.columns; ++c)
			for(size_t n = 0; n < a.columns; ++n)
				multipliedmatrices.matrix[r][c] += a.matrix[r][n]*b.matrix[n][c];
	return multipliedmatrices;
}

// Divides matrix "a" by "b" and returns the result
matrix_t divideMatrices(matrix_t a, matrix_t b){
	return multiplyMatrices(a, inverse(b));
}

// Raises the matrix to the nth power and returns the result
matrix_t raiseMatrixToN(matrix_t m, int n){
	if(!isSquare(m))
		return matrixError(NOT_SQUARE);
	// TODO: only accepts positive values of n
	matrix_t raisedmatrix = identityMatrix(m.rows);
	for(int i = 0; i < n; ++i)
		raisedmatrix = multiplyMatrices(raisedmatrix, m);
	return raisedmatrix;
}

// Creates a submatrix from "matrix" without the column "column" and row "row" of "matrix"
matrix_t createSubmatrix(matrix_t m, size_t row, size_t column){
	int mod = m.rows, nmod = mod-1, sr = 0, sc = 0;
	matrix_t submatrix = createMatrix(nmod, nmod);
	for(size_t r = 0; r < mod; ++r){
		sc = 0;
		if(r != row){
			for(size_t c = 0; c < mod; ++c){
				if(c != column){
					submatrix.matrix[sr][sc] = m.matrix[r][c];
					++sc;
				}	
			}
			++sr;
		}
	}
	return submatrix;
}

// Returns the determinant of the given (square) matrix
int determinant(matrix_t m){
	if(!isSquare(m)){
		matrixError(NOT_SQUARE);
		return (int)NULL;
	}
	int det = 0;
	if(m.rows == 1)
		return m.matrix[0][0];
	else{
		int count = 0, nmod = m.rows-1;
		for(size_t r = 0; r < m.rows; ++r){
			matrix_t submatrix = createSubmatrix(m, 0, r);
			int subdeterminant = determinant(submatrix);
			int step = m.matrix[0][r]*subdeterminant;
			if((count++)%2 == 0)
				det += step;
			else
				det -= step;
		}
		return det;
	}
}

// Returns the cofactor matrix of the given matrix
matrix_t cofactor(matrix_t m){
	if(!isSquare(m))
		return matrixError(NOT_SQUARE);
	matrix_t cofactormatrix = createMatrix(m.rows, m.columns);
	for(size_t r = 0; r < m.rows; ++r){
		for(size_t c = 0; c < m.columns; ++c){
			matrix_t submatrix = createSubmatrix(m, r, c);
			int d = determinant(submatrix);
			cofactormatrix.matrix[r][c] = (r+c)%2?-d:d;
		}
	}
	return cofactormatrix;
}

// Returns the transpose matrix of the given matrix
matrix_t transpose(matrix_t m){
	matrix_t transposematrix = createMatrix(m.columns, m.rows);
	for(size_t r = 0; r < m.columns; ++r)
		for(size_t c = 0; c < m.rows; ++c)
			transposematrix.matrix[r][c] = m.matrix[c][r];
	return transposematrix;
}

// Returns the adjugate matrix of the given matrix
matrix_t adjugate(matrix_t m){
	return transpose(cofactor(m));
}

// Returns the inverse matrix of the given matrix
matrix_t inverse(matrix_t m){
	int det = determinant(m);
	if(det == 0)
		return matrixError(ZERO_DET);
	return multiplyByN(adjugate(m), (float)1/det);
}