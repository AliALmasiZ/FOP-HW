#include <stdio.h>
#include <stdlib.h>

// TODO: Your Includes and Defines Here

//403100043
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 10000
// TODO: Your Functions Here
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
int main(int argc, char *argv[]) {
    FILE *inputFile;  
    inputFile = fopen("input.txt", "r");

    FILE *outputfile;
    outputfile = fopen("output.txt", "w");

    // TODO: Your Code Here
    char temp[2] = {};
    char str[MAX_SIZE];
    int flag = 0;
    char *endptr;
    while ((temp[0] = getc(inputFile)) != EOF) {
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

    fputs(str, outputfile);
    // printf("%ld", strtol(str, &endptr, 10));??
    fclose(inputFile);
    fclose(outputfile);

    return 0;
}
