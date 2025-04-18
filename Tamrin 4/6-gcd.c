//403100043
#include <stdio.h>
#define l_l long long unsigned
l_l gcd(l_l a, l_l b) {
    if(a == 0 || b == 0)
        return a + b;
    if (a>b) {
        a = a + b;
        b = a - b;
        a = a - b;
    }
    return gcd(a, b % a);
}
int main() {
    l_l a, b;
    scanf("%llu %llu", &a, &b);
    printf("%llu", gcd(a, b));
    return 0;
}