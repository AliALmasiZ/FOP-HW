//403100043
#include <stdio.h>
long long unsigned r[1001], n;
int counter = 0, b[1001], m, a[1001] ;


int ragham(int x) {
    int res = 1;
    while(x) {
        x /= 10;
        res *= 10;
    } 
    return res;
}
int finder() {
    long long unsigned n_copy = n;
    int x = 0;
    for(int i = x; (i < m); i++) {
        	if (n % r[i] == a[i]) {
            	b[counter++] = i;
            	n /= r[i];
                if (finder() == 0) {
                    counter--;
                    n = n_copy;
                }
                else {
                    return 1;
                }
        	}
    	}
    if (n == 0)
        return 1;
    return 0;
}
int main() {
    int x = 0;
    scanf("%llu %d", &n, &m);
    for(int i = 0; i < m; i++) {
        scanf("%d", &a[i]);
	r[i] = ragham(a[i]);
    }
    if (finder() == 0) {
        printf("-1");
    }else {
        for(int i = --counter; i >=0; i--) {
            printf("%d ", b[i]);
        }
    }
    
    return 0;
}