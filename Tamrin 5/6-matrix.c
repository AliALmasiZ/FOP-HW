#include <stdio.h>
#include <stdlib.h>

int n, size = 1;
int* dims;

// Function to input the n-dimensional matrix
void* matrix_input(int m) {
    // Allocate memory for the current level of the matrix
    void *a = malloc(*(dims + n - m) * sizeof(void*));
    void **b = (void**)a;

    if (m == 1) {
        // Base case: when we reach the last dimension, read values
        for (int i = 0; i < *(dims + n - m); i++) {
            scanf("%d", (int *)(a) + i);
        }
        return a;
    }

    // Recursively fill the matrix for each dimension
    for (int i = 0; i < *(dims + n - m); i++) {
        *(b + i) = matrix_input(m - 1);
    }

    return a;
}

// Function to print the n-dimensional matrix
void print_matrix(void *mat, int m, int *arr) {
    if (m == 1) {
        // Base case: print the values at the last dimension
        for (int i = 0; i < *(dims + n - m); i++) {
            printf("%d ", *((int*)mat + i));
        }
        printf("\n");
        return;
    }

    void **temp = (void**)mat;
    for (int i = 0; i < *(dims + n - m); i++) {
        arr[m - 1] = i;
        print_matrix(*(temp + i), m - 1, arr);
    }
}

int main() {
    // Input the number of dimensions
    scanf("%d", &n); 

    // Input the sizes of each dimension
    dims = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", dims + i);
        size *= *(dims + i); // Calculate total number of elements
    }

    // Allocate memory for the n-dimensional matrix
    void *m1 = matrix_input(n);

    // Create an array to track indices during printing
    int *arr = (int*)calloc(n, sizeof(int));
    
    // Print the matrix
    print_matrix(m1, n, arr);

    // Free allocated memory
    free(dims);
    free(arr);
    free(m1);
    
    return 0;
}
