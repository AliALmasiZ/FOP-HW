//403100043
#include<stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    if (n < 1e4){
        int a=0, b=0, c=0;
        c = n % 100;
        n /= 100;
        b = n % 10;
        n /= 10;
        a = n;
        if((a+b)==c && b!=0 && c>=10 ){
            
            printf("%d+%d=%d", a, b, c);
        }else{
            printf("No Equation Found");
        }
    }else if(n<1e5){
        int c = n % 100;
        n /= 100;
        int b = n % 100;
        int a = n / 100;
        if(a+b==c && c>=10 && b>=10){
            printf("%d+%d=%d", a, b, c);
        }else {
            b = n % 10;
            a = n / 10;

            if(a+b==c && b>0){
            printf("%d+%d=%d", a, b, c);

            }else{
            printf("No Equation Found");
            }
        }
    }else {
        
        int c = n % 100;
        int b = n/100 % 100;
        int a = n / 10000;
        if(a+b==c && c>=10 && b>=10){
            printf("%d+%d=%d", a, b, c);
        }else{
            c = n % 1000;
            b = n / 1000 % 100;
            a = n / 100000;
            if(a+b==c&& c>=100 && b>=10){
            printf("%d+%d=%d", a, b, c);

            }else{
                c = n % 1000;
                b = n / 1000 % 10;
                a = n / 10000;
                if(a+b==c && c>=100 && b>0){
                printf("%d+%d=%d", a, b, c);

                }else{
                    printf("No Equation Found");
                    
                }
            
            }
    }
}}