#include <iostream>
#include <pthread.h>
#include <cstdlib>

// Constants defining matrix dimensions
const int MATRIX_A_ROWS = 3;   // Number of rows in matrix A
const int MATRIX_A_COLS = 4;   // Number of columns in matrix A
const int MATRIX_B_COLS = 3;   // Number of columns in matrix B **NOTE** the reason we don’t define the number of rows in matrix B is because for matrix multiplication to be possible the number of columns in the first matrix must be equal to the number of rows in the second matrix. So we will use the MATRIX_A_ROWS variable to define our matrix B

// Declaration and initialization of matrices
int matrixA[MATRIX_A_ROWS][MATRIX_A_COLS] = { {2, 4, 6, 8}, {10, 12, 14, 16}, {18, 20, 22, 24} }; // Matrix A
int matrixB[MATRIX_A_COLS][MATRIX_B_COLS] = { {20, 15, 10}, {18, 13, 8}, {16, 11, 6}, {14, 9, 4} }; // Matrix B
int MultipliedMatrix[MATRIX_A_ROWS][MATRIX_B_COLS] = { 0 }; // Result matrix after multiplication

// Struct to pass data to threads
struct ThreadData {
    int row; // Row index
};

// Function to perform multiplication in each thread
void* multiply(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int row = data->row;

    // Multiplying row of matrixA with matrixB
    for (int j = 0; j < MATRIX_B_COLS; j++) {
        MultipliedMatrix[row][j] = 0;
        for (int k = 0; k < MATRIX_A_COLS; k++) {
            // Performing the dot product of row 'row' from matrixA and column 'j' from matrixB
            MultipliedMatrix[row][j] += matrixA[row][k] * matrixB[k][j];
        }
    }
    return NULL;
}

int main() {
    pthread_t threads[MATRIX_A_ROWS]; // Array to hold thread IDs
    ThreadData threadData[MATRIX_A_ROWS]; // Array to hold thread data

    // Creating threads for matrix multiplication
    for (int i = 0; i < MATRIX_A_ROWS; i++) {
        threadData[i].row = i; // Setting row index for each thread
        // Creating thread to perform multiplication of a single row
        pthread_create(&threads[i], NULL, multiply, (void*)&threadData[i]);
    }

    // Waiting for all threads to finish
    for (int i = 0; i < MATRIX_A_ROWS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Printing Matrix 1 (matrixA)
    std::cout << "Matrix 1:\n";
    for (int i = 0; i < MATRIX_A_ROWS; i++) {
        for (int j = 0; j < MATRIX_A_COLS; j++) {
            std::cout << matrixA[i][j] << " "; // Output each element of matrixA
        }
        std::cout << "\n";
    }

    // Printing Matrix 2 (matrixB)
    std::cout << "\nMatrix 2:\n";
    for (int i = 0; i < MATRIX_A_COLS; i++) {
        for (int j = 0; j < MATRIX_B_COLS; j++) {
            std::cout << matrixB[i][j] << " "; // Output each element of matrixB
        }
        std::cout << "\n";
    }

    // Printing the multiplied matrix
    std::cout << "\nMultiplied Matrix:\n";
    for (int i = 0; i < MATRIX_A_ROWS; i++) {
        for (int j = 0; j < MATRIX_B_COLS; j++) {
            std::cout << MultipliedMatrix[i][j] << " "; // Output each element of the multiplied matrix
        }
        std::cout << "\n";
    }

    return 0;
}
