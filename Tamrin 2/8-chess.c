//403100043
#include<stdio.h>
#include<math.h>

int main() {
    long long unsigned n;
    // int a, b;
    // scanf("%d %d", &a, &b);
    // n = pow(2, a) + pow(2, b);

    scanf("%llu", &n);

    long long unsigned a1, a2, a3, a4, a5, a6, a7, a8;
    n = 18446744073709551615;

    long long int b1, b2, b3, b4, b5, b6, b7, b8;
    b1 = pow(2, 8);
    b2 = pow(2, 16);
    b3 = pow(2, 24);
    b4 = pow(2, 32);
    b5 = pow(2, 40);
    b6 = pow(2, 48);
    b7 = pow(2, 56);
    a1 = n / b7;
    a2 = n / b6;
    a3 = n / b5;
    a4 = n / b4;
    a5 = n / b3;
    a6 = n / b2;
    a7 = n / b1;
    a8 = n - a7 * b1;
    a7 -=  a6 * b1;
    a6 -=  a5 * b1;
    a5 -=  a4 * b1;
    a4 -=  a3 * b1;
    a3 -=  a2 * b1;
    a2 -=  a1 * b1;
    printf("%d \n", a1);
    printf("%d \n", a2);
    printf("%d \n", a3);
    printf("%d \n", a4);
    printf("%d \n", a5);
    printf("%d \n", a6);
    printf("%d \n", a7);
    printf("%d \n", a8);
    if (((a1 - 1) & a1) != 0 || ((a2 - 1) & a2) != 0 || ((a3 - 1) & a3) != 0 || ((a4 - 1) & a4) != 0 || ((a5 - 1) & a5) != 0 || ((a6 - 1) & a6) != 0 || ((a7 - 1) & a7) != 0 || ((a8 - 1) & a8) != 0)
    {
        printf("YES");
        }
        else
        {
            if (((a1 == a2 || a1 == a3 || a1 == a4 || a1 == a5 || a1 == a6 || a1 == a7 || a1 == a8) && (a1 != 0)) || ((a2 == a3 || a2 == a4 || a2 == a5 || a2 == a6 || a2 == a7 || a2 == a8) && (a2 != 0)) ||
                ((a3 == a4 || a3 == a5 || a3 == a6 || a3 == a7 || a3 == a8) && (a3 != 0)) || ((a4 == a5 || a4 == a6 || a4 == a7 || a4 == a8) && (a4 != 0)) || ((a5 == a6 || a5 == a7 || a5 == a8) && (a5 != 0)) ||
                ((a6 == a7 || (a6 == a8)) && (a6 != 0)) || ((a7 == a8) && (a7 != 0)))
            {
                printf("YES");
            }
            else
            {
                printf("NO");
            }
        }


    return 0;
}