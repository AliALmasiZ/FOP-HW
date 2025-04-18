#include <stdio.h>
#include <stdlib.h>
int n, k, size = 1;
void *m1,*m2;
int* dims, *shape;
void* matrix_input(int  m) {
    void *a = calloc(*(dims + n - m) , sizeof(void*));
    void **b = (void**)a;
    if (m == 1) {
        for(int i = 0; i < *(dims + n - m); i++){
            scanf("%lld", (long long *)(a) + i);
        }
        return a;
    }
    for (int i = 0; i < *(dims + n - m); i++) {
        *(b + i) = matrix_input(m - 1);
    }
    return a;
}
void linear(int who, long long alpha, long long beta) {
    int *arr = calloc(n, sizeof(int));
    for(int i = 0; i < size; i++) {
        long long** tmp1 = (long long**) m1;
        long long** tmp2 = (long long**) m2;
        for(int j = 0; j < n - 1; j++){
            tmp1 = (long long**)*(tmp1 + *(arr + j));
            tmp2 = (long long**)*(tmp2 + *(arr + j));
        }
        // long long* m11 = (long long*)(*(tmp1 + *(arr + n - 2)));
        // long long* m21 = (long long*)(*(tmp2 + *(arr + n - 2)));


        
        if(who == 1) {
            // printf("----%lld----\n", *((long long*)(tmp1) + *(arr + n - 1)));
            *((long long*)(tmp1) + *(arr + n - 1)) = (((alpha % 100) * (*((long long*)(tmp1) + *(arr + n - 1))) + (beta % 100) * (*((long long*)(tmp2) + *(arr + n - 1))))%100);            
        }else if(who == 2){
            *((long long*)(tmp2) + *(arr + n - 1)) = (((alpha % 100) * (*((long long*)(tmp1) + *(arr + n - 1))) + (beta % 100) * (*((long long*)(tmp2) + *(arr + n - 1))))%100);
        }
        // printf("((%lld, %lld))\n", (long long)m12, (long long)m22);
        (*(arr + n - 1))++;
        for(int j = n - 1; j >= 0; j--) {
            if(*(arr + j) == *(dims + j)) {
                *(arr + j) = 0;
                (*(arr + j - 1))++;
            }
        }
    }

}
void print_matrix(void *mat, int who) {
    int *arr = calloc(n, sizeof(int));
    int *a = calloc(k, sizeof(int));
    if(who == 1) {
        printf("Matrix 1:\n");
    }else {
        printf("Matrix 2:\n");
    }
    for(int i = 0; i < size; i++) {
        void **temp = (void**) mat;
        printf("(");
        for(int j = 0; j < n; j++) {
            temp = (void**)*(temp + *(arr + j));
        }
        for(int j = 0; j < k; j++) {
            printf("%d", *(a + j) + 1);
            if(j != k - 1) {
                printf(",");
            }
        }
        printf("): %lld\n", (long long)temp);
        (*(arr + n - 1))++;
        (*(a + k - 1))++;
        for(int j = n - 1; j >= 0; j--) {
            if(*(arr + j) == *(dims + j)) {
                *(arr + j) = 0;
                (*(arr + j - 1))++;
            }
        }
        for(int j = k - 1; j >= 0; j--) {
            if(*(a + j) == *(shape + j)) {
                *(a + j) = 0;
                (*(a + j - 1))++;
            }
        }
    }
}
int main() {
    scanf("%d", &n); 
    k = n;
    dims = (int*)malloc(n * sizeof(int));
    shape = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        scanf("%d", dims + i);
        size *= *(dims + i);
        *(shape + i)= *(dims + i);
    }
    m1 = matrix_input(n);
    m2 = matrix_input(n);
    int temp;
    scanf("%d", &temp);
    for(int i = 0; i < temp; i++){
        char c;
        scanf(" %c", &c);
        if(c == 'T') {
            int tmp = *(shape + 1);
            *(shape + 1) = *(shape);
            *(shape) = tmp;
        }
        else if (c == 'L') {
            int who;
            long long alpha, beta;
            scanf("%d %lld %lld", &who, &alpha, &beta);
            linear(who, alpha, beta);
        }
        else if (c == 'R') {
            free(shape);
            scanf("%d", &k);
            shape = (int*)malloc(k * sizeof(int));
            for(int i = 0; i < k; i++) {
                scanf("%d", shape + i);
            }
        }
    }


    print_matrix(m1, 1);
    print_matrix(m2, 2);
    
}