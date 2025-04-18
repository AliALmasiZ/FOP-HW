//403100043
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n;i++) {
        for (int j = 0; j < n - i;j++) printf(" ");
        for (int k = 1; k <= i;k++) printf("%d ", k);
        printf("\n");
    }
    for (int i = n-1; i >0;i--) {
        for (int j = 0; j < n - i;j++) printf(" ");
        for (int k = 1; k <= i;k++) printf("%d ", k);
        printf("\n");
    }
}