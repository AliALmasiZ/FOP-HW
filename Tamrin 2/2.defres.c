//403100043
#include<stdio.h>
#include <math.h>
int main() {
    unsigned m, n;
    scanf("%u %u", &m, &n);
    unsigned t = m ^ n;
    double res = 0;
    res += t % 2;
    t /= 2;
    res += t % 2;
    t /= 2;
    res += t % 2;
    t /= 2;
    res += t % 2;
    t /= 2;
    res += t % 2;
    t /= 2;
    res += t % 2;
    t /= 2;
    res += t % 2;
    t /= 2;
    res += t % 2;
    t /= 2;
    res = m + n * pow(-1, res);
    printf("%0.0f", res);
    return 0;
}