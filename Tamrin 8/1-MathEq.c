//403100043
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 10000

int calculator(char *str, int start, int initial) {
    int res = initial;
    int temp = 0;
    int op_index = 0;
    temp = 0;
    op_index = start > 0 ? start - 1 : op_index;
    int i = start;
    while (1) {
        if(isdigit(str[i])) {
            temp *=10;
            temp += str[i] - '0';
        }
        else {
            if(str[op_index] == '/') {
                res /= temp;
                op_index = i;
            }
            else if(str[op_index] == '*') {
                res *= temp;
                op_index = i;
            }
            else if(str[op_index] == '+') {
                return calculator(str, i + 1, temp) + res;
            }
            else if(str[op_index] == '-') {
                temp *= -1;
                return calculator(str, i + 1, temp) + res;
            }
            else {
                return res;
            }
            temp = 0;
            if(str[i] == '\0') break;
        }
        i++;
    }
    return res;
}
// "1-5*3/2+1*2"

int main() {
    FILE *file;
    file = fopen("in.txt", "r");
    FILE *out;
    out = fopen("out.txt", "w");
    char temp[2] = {};
    char str[MAX_SIZE];
    int flag = 0;
    char *endptr;
    // fgets(str, MAX_SIZE, file);
    while ((temp[0] = getc(file)) != EOF) {
        if(temp[0] == ' ') continue;
        if(temp[0] == '0') {
            if(str[strlen(str) - 1] == '/') {
                flag = 1;
            }
        }
        strcat(str, temp);
    }
    if(flag) {
        strcat(str, "=Error");

    }
    else {
        int temp = 0;
        for(int i = 0; str[i] != '\0'; i++) {
            if(isdigit(str[i])) {
                temp *=10;
                temp += str[i] - '0';
            }
            else {
                temp = calculator(str, i + 1, temp);
                break;
            }
        }
        char tempstr[5];
        sprintf(tempstr, "=%d", temp);
        strcat(str, tempstr);
    }
    printf("%s", str);
    fputs(str, out);
    // printf("%ld", strtol(str, &endptr, 10));??
    fclose(file);
    fclose(out);
    
}

