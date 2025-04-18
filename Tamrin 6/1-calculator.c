//403100043
#include<stdio.h>
#include<string.h>

#define MAX_SIZE 200000
int romChar_to_num(char c) {
    if(c == 'I') {
        return 1;
    }
    if(c == 'V') {
        return 5;
    }
    if(c == 'X') {
        return 10;
    }
    if(c == 'L') {
        return 50;
    }
    if(c == 'C') {
        return 100;
    }
    if(c == 'D') {
        return 500;
    }
    if(c == 'M') {
        return 1000;
    }
    return 0;
}
int roman_to_num(char* c , int n) {
    int res = 0;
    for(int i = 0; i < n; i++) {
        int first = romChar_to_num(c[i]);
        int next =(i + 1 < n) ? romChar_to_num(c[i + 1]) : 0;
        if(first < next) {
            res += (next - first);
            i++;
        }else {
            res += first;
        }
    }
    return res;
}
int main() {
    int number = 0;
    scanf("%d", &number);
    for(int i = 0; i < number; i++) {
        int res = 0, num1, num2;
        char a[MAX_SIZE], op[15], b[MAX_SIZE], temp[12];
        scanf("%s %s", a, op);
        if(strcmp(op, "divided") == 0) {
            scanf("%s %s", temp, b);
        }
        else {
            scanf("%s", b);
        }
        num1 = roman_to_num(a, strlen(a));
        num2 = roman_to_num(b, strlen(b));
        if(strcmp(op, "plus") == 0) {
            res = num1 + num2;
        }
        else if (strcmp(op, "minus") == 0) {
            res = num1 - num2;
        }
        else if (strcmp(op, "times") == 0) {
            res = num1 * num2;
        }
        else if (strcmp(op, "divided") == 0) {
            res = num1 / num2;
        }
        else if (strcmp(op, "mod") == 0) {
            res = num1 % num2;
        }
        printf("%d\n", res);
    }
}