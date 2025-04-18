//403100043
#include <stdio.h>
#include <math.h>

const double PI = 3.14159265358979323846;
int main() {
    int n;
    scanf("%d", &n);
    double a, b, c;
    switch (n)
    {
    case 1:
        scanf("%lf", &a);
        printf("Perimeter: %0.2lf \nArea: %0.2lf", 4 * a, a*a);

        break;
    case 2 :
        scanf("%lf %lf", &a, &b);
        printf("Perimeter: %0.2lf \nArea: %0.2lf" , 2*(a+b), a*b);
        
        break;
    case 3 :
        scanf("%lf", &a);
        printf("Perimeter: %0.2lf \nArea: %0.2lf", a*2*PI, a*a*PI);
        break;
    case 4 :
        scanf("%lf %lf %lf", &a, &b, &c);
        double p = a + b + c;
        p /= 2;
        double s = sqrt(p*(p-a)*(p-b)*(p-c));
        if (a<b) {
                a = a + b;
                b = a - b;
                a = a - b; 
        }
        if (a<c){
            a = a + c;
            c = a - c;
            a = a - c;
        }
        double a2 = pow(a, 2);
        double sum2 = pow(b, 2) + pow(c, 2);
        if(a2 == sum2){
        printf("Perimeter: %0.2lf \nArea: %0.2lf \nType: %s",2*p,s,"Right");

        }
        else if(a2 > sum2){
        printf("Perimeter: %0.2lf \nArea: %0.2lf \nType: %s",2*p,s,"Obtuse");
            
        }
        else {
        printf("Perimeter: %0.2lf \nArea: %0.2lf \nType: %s",2*p,s,"Acute");

        }
        break;
    default:
        break;
    }
}