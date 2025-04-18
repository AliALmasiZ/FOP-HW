//403100043
#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    // printf("%d", n);
    int a[n];
    for (int i = 0; i < n;i++)scanf("%d", &a[i]);
    for (int i = 0; i < n; i++)
    {
        int k, t=0 , temp;
        // printf("%d", a[i]);
        temp = a[i];
        k = log10(a[i]) + 1;
        while (temp > 0)
        {
            t += pow(temp % 10, k);
            temp /= 10;
        }
        if (a[i] == t)
            printf("\n%d is Armstrong", t);
        else
            printf("\n%d is Not Armstrong", a[i]);
    }

    return 0;
}