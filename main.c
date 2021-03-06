#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct matrix {

    double* m;
    int cols;
    int rows;

} matrix_t;


// Allocate a double type matrix

void alloc_matrix(matrix_t* mat) {
    mat->m = (double*)malloc(mat->rows * mat->cols * sizeof(double));

    if(mat->m == NULL) {
        fprintf(stderr,"Matrix allocation error!\n");
        exit(-1);
    }
}

// Read a matrix from a WHITESPACE separated ASCII infile

void read_matrix(char* file, matrix_t mat){

    FILE *fp = fopen(file, "r");

    for (int i = 0; i < mat.rows; i++){
        for (int j = 0; j < mat.cols; j++){
            fscanf(fp, "%lf", &mat.m[i * mat.cols + j]);
        }
    }
}

void print_matrix(matrix_t mat, const char *name){

    printf("\n");
    printf("%s:\n", name);
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            printf("%f ", mat.m[mat.cols * i + j]);
        }
        printf("\n");
    }
}


matrix_t mult(matrix_t m1, matrix_t m2) {

    matrix_t temp;
    temp.rows = m1.rows;
    temp.cols = m2.cols;

    alloc_matrix(&temp);

    for(int i = 0; i < temp.rows; ++i) {
        for(int j = 0; j < temp.rows; ++j) {
            for(int k = 0; k < m1.cols; ++k){

                temp.m[temp.cols*i + j] += m1.m[m1.cols*i + k] * m2.m[m2.cols*k + j];
            }
        }
    }
    return temp;
}


void main(int argc, char *argv[]){

    //char* filename;
    

    if (argc != 5) {
        fprintf(stderr,
                "Usage: matrixMultiplication <matrixfile1> <matrixfile2> <rows> <cols>\n");
        exit(-1);
    }

    
    //filename = argv[1], argv[2];
    int rows, cols;

    rows = atoi(argv[3]);
    cols = atoi(argv[4]);
    
    if(rows != cols) {
        printf("Matrix multiplication error. \n");
        exit(-1);
    }
    matrix_t mat1;
  
    mat1.rows = rows;
    mat1.cols = cols;
    alloc_matrix(&mat1);
    read_matrix(argv[1], mat1);
    print_matrix(mat1, "matrix1");

    matrix_t mat2;
    
    mat2.rows = rows;
    mat2.cols = cols;
    alloc_matrix(&mat2);
    read_matrix(argv[2], mat2);
    print_matrix(mat2, "matrix2");

    matrix_t res;
    res = mult(mat1, mat2);
    print_matrix(res, "Solution");
    
    free(mat1.m);
    free(mat2.m);
    free(res.m);
}