//403100043
#include <stdio.h>

int main() {
    int n;
    scanf("%d" , &n);
    long long int a[100000];
    for(int i=0;i < n ; i++){
        scanf("%lld",&a[i]);
    }
    while(n>=3)
    {
        n-=1;
        if(a[n] < a[n-1]+a[n-2]) {
            printf("%lld", a[n]+a[n-1]+a[n-2]);
            return 0;    
        }
    }
    printf("-1");
}