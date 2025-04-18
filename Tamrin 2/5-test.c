//403100043
#include <stdio.h>
#include <math.h>
int main() {
    double a, b, c, d;
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    double delta = 4*b*b - 12*a*c;
    //  printf("%0.2lf \n %0.2lf \n %0.2lf\n", b , delta,a);
    if(delta <= 0)
        printf("No Local Extrema Points");
    else {
        double x_1 = (-2 * b - sqrt(delta))/(6*a);
        double x_2 = (-2 * b + sqrt(delta))/(6*a);
        if (x_1 > x_2) {
            x_1 += x_2;
            x_2 = x_1 - x_2;
            x_1 = x_1 - x_2;
        }
        printf("%0.2lf, %0.2lf", x_1, x_2);
    }
    return 0;
}   