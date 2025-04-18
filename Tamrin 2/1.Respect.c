//403100043
#include<stdio.h>

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    if (a>b){
        if(a>c){
            if(b > c){
                a = a + b;
                b = a - b;
                a = a - b;
            }
            else{
                a = a + c;
                c = a - c;
                a = a - c;
            }
        }
    }else if (a < c){
        if(b>c) {
            a = a + c;
            c = a - c;
            a = a - c;
        }

        else{
            a = a + b;
            b = a - b;
            a = a - b;
        }
    }

    printf("%d", a);
    return 0;
}