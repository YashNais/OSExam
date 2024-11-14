
/*Implement multithreading for Matrix Operations using Pthreads.*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX 100

int matA[MAX][MAX], matB[MAX][MAX], result[MAX][MAX];
int rowA, colA, rowB, colB;

void* multiply(void* arg);
void* add(void* arg);
void* subtract(void* arg);
void* transposeA(void* arg);
void* transposeB(void* arg);


void* multiply(void* arg) {
    intptr_t row = (intptr_t)arg;  
    for (int i = 0; i < colB; i++) 
    {
        result[row][i] = 0;
        for (int j = 0; j < colA; j++) {
            result[row][i] += matA[row][j] * matB[j][i];
        }
    }
    pthread_exit(0);
}

void* add(void* arg) {
    intptr_t row = (intptr_t)arg; 
    for (int i = 0; i < colA; i++) {
        result[row][i] = matA[row][i] + matB[row][i];
    }
    pthread_exit(0);
}

void* subtract(void* arg) {
    intptr_t row = (intptr_t)arg;  
    for (int i = 0; i < colA; i++) {
        result[row][i] = matA[row][i] - matB[row][i];
    }
    pthread_exit(0);
}


void* transposeA(void* arg) {
    intptr_t row = (intptr_t)arg;  
    for (int i = 0; i < colA; i++) {
        result[i][row] = matA[row][i];
    }
    pthread_exit(0);
}

void* transposeB(void* arg) {
    intptr_t row = (intptr_t)arg;  
    for (int i = 0; i < colB; i++) {
        result[i][row] = matB[row][i];
    }
    pthread_exit(0);
}

void create_threads(void* (*operation)(void*), int rows) {
    pthread_t threads[MAX];

    for (int i = 0; i < rows; i++) {
        pthread_create(&threads[i], NULL, operation, (void*)(intptr_t)i);
    }

    for (int i = 0; i < rows; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main() {
    int choice;

    printf("Enter the number of rows and columns for matrix A: ");
    scanf("%d %d", &rowA, &colA);

    printf("Enter the elements of matrix A:\n");
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colA; j++) {
            scanf("%d", &matA[i][j]);
        }
    }

    printf("Enter the number of rows and columns for matrix B: ");
    scanf("%d %d", &rowB, &colB);

    if (colA != colB || rowA != rowB) {
        printf("For addition, subtraction, and transpose, matrices must have the same dimensions.\n");
        return -1;
    }

    printf("Enter the elements of matrix B:\n");
    for (int i = 0; i < rowB; i++) {
        for (int j = 0; j < colB; j++) {
            scanf("%d", &matB[i][j]);
        }
    }

    while (1) {

        printf("\nChoose the matrix operation:\n");
        printf("1. Matrix Multiplication\n");
        printf("2. Matrix Addition\n");
        printf("3. Matrix Subtraction\n");
        printf("4. Transpose of Matrix A\n");
        printf("5. Transpose of Matrix B\n");
        printf("0. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (colA != rowB) {
                    printf("Matrix multiplication not possible, invalid dimensions.\n");
                    break;
                }
                create_threads(multiply, rowA);
                break;

            case 2:
                create_threads(add, rowA);
                break;

            case 3:
                create_threads(subtract, rowA);
                break;

            case 4:
                create_threads(transposeA, rowA);
                break;

            case 5:
                create_threads(transposeB, rowB);
                break;

            case 0:
                printf("Exiting...\n");
                return 0;  

            default:
                printf("Invalid choice.\n");
        }

        printf("Resultant matrix:\n");
        for (int i = 0; i < rowA; i++) {
            for (int j = 0; j < colB; j++) {
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}

