//403100043
#include <stdio.h>

long long segment_counter(long long t){
    long long ans = 0;
    if(t == 0)
        ans += 6;
    if(t==1)
        ans += 2;
    if (t==2) 
        ans += 5;
    if (t==3) 
        ans += 5;
    if (t==4) 
        ans += 4;
    if (t==5) 
        ans += 5;
    if (t==6) 
        ans += 6;
    if (t==7) 
        ans += 3;
    if (t==8) 
        ans += 7;
    if (t==9) 
        ans += 6;
    return ans;
    
}
long long javab( long long a,  long long n,  long long b){
    long long pow = 1,m = 0;
    while(n > 0){
        m+=(n%10)*pow;
        n/=10;
        pow*=a;
    }
    long long t = 0;
    long long x;
    t+=segment_counter(m%b);

    m/=b;
    while(m > 0) {
        x = m % b;
        t+=segment_counter(x);
        m /= b;
    }
    return t;
}

int main()
{
     long long a, b;
     long long n;
    scanf("%lld %lld %lld", &n, &a, &b);
    printf("%lld",javab(a, n, b));
    return 0;
}