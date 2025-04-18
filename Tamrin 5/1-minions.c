//403100043
#include <stdio.h>
#include <stdlib.h>
int number, b;


void printAns(int** a) {
    for(int i = 0; i < number; i++) {
        for(int j = 0; j < i + 1; j++) {
            printf("%d ", *(*(a + i) + j));
        }
        printf("\n");
    }
}
int main() {
    scanf("%d", &number);
    int **a =(int **) malloc(500 * sizeof(int*));
    for(int i = 0; i < 500; i++) {
        *(a + i) = (int *)malloc(500 * sizeof(int));  
    }
    
    for (int i = 0; i < number; i++) {
        for(int j = 0; j < i + 1; j++) {
            scanf("%d", *(a + i) + j);
        }
    }
    while(1) {
        char s;
        scanf("%c", &s);    
        if(s == '#')
            break;
        if(s == 'a') {
            scanf("%d", &b);
            if(b > number + 1 || b < 1) {
                printf("Invalid row number\n");
                continue;
            }
            for(int i = number - 1; i >= b - 1; i--) {
                int* temp;

                temp = *(a + i + 1);
                *(a + i + 1) = *(a + i);
                *(a + i) = temp;
            }
            number++;
            for(int i = 0; i < b; i++) {
                scanf("%d", *(a + b - 1) + i);
            }
            for(int i = 0; i < number - b; i++) {
                scanf("%d", *(a + b + i) + b + i);
            }
            continue;
        }
        if (s == 'd') {
            scanf("%d", &b);
            if(b > number || b < 1) {
                printf("Invalid row number\n");
                continue;
            }
            for(int i = b - 1; i < number; i++) {
                int* temp;

                temp = *(a + i);
                *(a + i) = *(a + i + 1);
                *(a + i + 1) = temp;
            }
            number--;
            continue;
        }
    }

    printAns(a);
    for(int i = 0; i < 500; i++) {
        free(*(a + i));
    }
    free(a);


    return 0;
}