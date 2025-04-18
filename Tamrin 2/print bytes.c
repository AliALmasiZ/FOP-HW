#include<stdio.h>
void print_byte(unsigned char val ) {
    for (int i; i < 8;i++) {
        printf("%d ", val >> 7);
        val <<= 1;
    }
}
void print_bytes(void *val , int len){
    for (int i = len - 1; i >= 0;i--){
        print_byte(*(char *)(val + 1));
    }
    printf("\n")
}