//403100043
#include <stdio.h>

int main() {
    long long int x1, x2, y1, y2, r1, r2;
    scanf("%lld %lld %lld %lld %lld %lld", &x1, &y1, &r1, &x2, &y2, &r2);
    long long int distance2 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    long long int rSum2 = (r1+r2)*(r1+r2);
    long long int rdis =  (r1 - r2) * (r1 - r2);
    
    if(rSum2 > distance2 && rdis < distance2) {
        printf("2");
    }else if(rSum2 == distance2 || rdis == distance2){
        printf("1");
    }else{
        printf("0");
    }
}