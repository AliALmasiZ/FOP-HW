//403100043
#include <stdio.h>

int main() {
    int a, b,x[3],n=0;
    scanf("%d %d %d %d %d", &a, &b, &x[0], &x[1], &x[2]);
    unsigned t = a ^ b;
    
    while(t>0){
        n += t%2;
        t /=2 ;
    }
    for (int i = 0; i < 3;i++){
        if(x[i]<n || (x[i]%2 != n%2))
            printf("\nNO");
        else
            printf("\nYES");
    }
}