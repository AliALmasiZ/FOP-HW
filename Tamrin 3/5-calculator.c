//403100043
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n+1];
    for (int i = 1; i <= n;i++){
        scanf("%d",a+i);
    }
    while (1) {
        char c;
        int x, b,t;
        scanf("%c %d %d",&c,&x,&b);
        switch (c)
        {
        case 'r':
            for(int i =x;i<(b+x)/2;i++){
                t = a[i];
                a[i] = a[x+b-1-i];
                a[x+b-1-i] = t;
            }
            break;
        case 's':
            for(int i = x; i<b;i++){
                for(int j =i+1;j<b;j++){
                    if(a[i]>a[j]){
                        t = a[i];
                        a[i] = a[j];
                        a[j] = t;
                    }
                }
            }
            break;
        case 'd':
        for(int i=x ; i<b ; i++){
            a[i] *=2;
        }
            break;
        case 'e':
            for(int i = 1; i <= n; i++){
                printf("%d ",a[i]);
            }
            return 0;
            break;
        default:
            break;
        }
    }
}