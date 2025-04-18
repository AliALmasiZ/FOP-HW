//403100043
#include <stdio.h>
#include <stdlib.h>

int main() {
    int x;
    long long y;
    float z;
    char* s = (char*)malloc(1000 * sizeof(char));
    scanf("%s", s);
    for(int i = 0; *(s + i) != '!'; i++) {
        int var = *(s + i) % 16;
        int test = *(s + i) >> 4;
        if(test == 3) { //load
            if(var == 1) {
                x = *((int*)(s + i + 1));
                i += 4;
            }else if(var == 2) {
                y = *((long long*)(s + i + 1));
                i += 8;
            }else if(var == 4) {
                z = *((float*)(s + i + 1));
                i += 4;
            }
        }else if (test == 4) { //add
            if(var == 1) {
                x += *((int*)(s + i + 1));
                i += 4;
            }else if(var == 2) {
                y += *((long long*)(s + i + 1));
                i += 8;
            }else if(var == 4) {
                z += *((float*)(s + i + 1));
                i += 4;
            }
        }else if(test == 5) { //print
            if(var == 1) {
                printf("%d\n", x);
            }else if(var == 2) {
                printf("%lld\n", y);
            }else if(var == 4) {
                printf("%.3f\n", z);
            }
        }
    }

    return 0;
}
