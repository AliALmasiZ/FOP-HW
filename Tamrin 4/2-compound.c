//403100043
#include <stdio.h>
#include <math.h>
/*
    0,0 0,1 | 0,2 0,3 | 0,4 0,5 0,6 0,7
    1,0 1,1 | 1,2 1,3 | 1,4 1,5 1,6 1,7
    --------|---------|----------------
    2,0 2,1 | 2,2 2,3 | 2,4 2,5 2,6 2,7
    3,0 3,1 | 3,2 3,3 | 3,4 3,5 3,6 3,7
    --------|---------|----------------
    4,0 4,1 | 4,2 4,3 | 4,4 4,5 4,6 4,7

*/

int matrix(long long a, long long b) {
    if (a == 0 && b == 0)
        return 0;
    if (a == 0 && b == 1)
        return 1;
    if (a == 1 && b == 0)
        return 2;
    if (a == 1 && b == 1)
        return 3;
    int blog = log2(b);
    int alog = log2(a);
    if (alog == blog)
        return matrix((1LL << (alog+1))-a-1,(1LL << (blog+1))-b-1);
    if (alog > blog) {
        return matrix((1LL << (alog+1))-a-1, b) - 1;
    }
    if (alog < blog) {
        return matrix(a,(1LL << (blog+1))-b-1) + 1;
    }
}
int main() {
        
    int n, m;
    long long i, j;
    scanf("%d %d", &n, &m);
    for(int k = 0; k < m; k++){
        
        scanf("%lld %lld",&i, &j);
        printf("%d ", matrix(i,j));
    }
    
    
    return 0;

}