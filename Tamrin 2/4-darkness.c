//403100043
#include <stdio.h>
int main() {
    int a, b, c, x, y;
    scanf("%d %d %d", &a, &b, &c);
    if(a == 8)
        scanf("%o", &x);
    else if (a==16)
        scanf("%x",&x);
    else
        scanf("%d", &x);
    if(b == 8)
        scanf("%o", &y);
    else if (b==16)
        scanf("%x",&y);
    else
        scanf("%d", &y);
    if(c == 8)
        printf("%o", x+y);
    else if (c==16)
        printf("%x",x+y);
    else
        printf("%d", x+y);
}