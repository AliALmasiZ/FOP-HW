//403100043
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    long long** a = (long long **)malloc(n * sizeof(long long*));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            *(a + j) = realloc(*(a + j), (i + 1) * sizeof(long long));
            scanf("%lld", *(a + j) + i);
        }
        *(a + i) = realloc(*(a + i), (i + 1) * sizeof(long long));
        for(int j = 0; j < i + 1; j++) {
            scanf("%lld", *(a + i) + j);
        }
        for(int j = 0; j < i + 1; j++) {
            for(int k = 0; k < i + 1; k++) {
                printf("%lld ", *(*(a + j) + k));
            }
            printf("\n");
        }
        printf("----\n");
    }
    return 0;
}