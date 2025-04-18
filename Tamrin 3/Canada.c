//403100043
#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    long long int a[n];
    for (int i = 0; i < n;i++)
        scanf("%lld", &a[i]);
    for (int i = 0; i < n; i++)
    {
        long long int t = 0,x = (a[i]/10);
        for (int j = 2; j < 11;j++){
            t += j * (x % 10);
            x /= 10;    
        }
        int r = t % 11;
        if (r<2) {
            if(r == a[i]%10)
                printf("\nYES");
            else
                printf("\nNO");
        }else{
            if (11 -r == a[i]%10)
                printf("\nYES");
            else
                printf("\nNO");
        }
    }
    
}