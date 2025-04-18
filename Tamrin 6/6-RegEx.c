//403100043
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 111111

char str[MAX], regex[MAX];
int pluschecker[2] = {};
int isint(char c) {
    if(c < '0' || c > '9')
        return 0;
    return 1;
}

int chex(int reg, int pos) {
    int backslash = 0;
    int p[2];
    int temp1 = (reg), temp2 = (pos);
    if(!backslash && (regex[temp1] == '$' || regex[temp1] == EOF || regex[temp1] == '\n')) {
        if (str[temp2] == EOF || str[temp2] == '\0' || str[temp2] == '\n')
            return 1;
        return 0;
    }
    if(!backslash && regex[temp1] == '^') {
        return chex(temp1 + 1, temp2);
    }
    if(regex[temp1] == '\\' && regex[(temp1) + 1] != 'd' && !backslash) {
        backslash = 1;
        (temp1)++;
    }
    if(regex[temp1] == '\\' && !backslash) {
        (temp1)++;
        if(regex[temp1] == 'd') {
            if(regex[(temp1) + 1] == '+') {
                if(pluschecker[0]-- > 0 && isint(pluschecker[1])) {
                    (temp1) += 2;
                    return chex(temp1, temp2);
                }
                if (!isint(str[temp2])) {
                    return 0;
                }
                pluschecker[1] = regex[temp1];
                pluschecker[0] = 0;
                while (isint(str[temp2])) {
                    pluschecker[0]++;
                    (temp2)++;
                }
                pluschecker[0]--;
                (temp1) += 2;
                return chex(temp1, temp2);
            }
            else if(regex[(temp1) + 1] == '*') {
                p[1] = pluschecker[1];
                p[0] = pluschecker[0];
                if(chex(temp1 + 2, temp2) == 1) {
                    return 1;
                }
                pluschecker[0] = p[0];
                pluschecker[1] = p[1];
                if(isint(pluschecker[1]) && pluschecker[0] > 0) {
                    (temp1) += 2;
                    return chex(temp1, temp2);
                }
                if(!isint(str[temp2])) {
                    (temp1) += 2;
                    return chex(temp1, temp2);
                }
                pluschecker[1] = regex[temp1];
                pluschecker[0] = 0;
                while (isint(str[temp2])) {
                    pluschecker[0]++;
                    (temp2)++;
                    p[1] = pluschecker[1];
                    p[0] = pluschecker[0];
                    if(chex(temp1 + 2, temp2) == 1) {
                        return 1;
                    }
                    pluschecker[0] = p[0];
                    pluschecker[1] = p[1];
                }
                (temp1) += 2;
                return chex(temp1, temp2);


            }
            else if(regex[(temp1) + 1] == '?') {
                p[1] = pluschecker[1];
                p[0] = pluschecker[0];
                if(chex(temp1 + 2, temp2) == 1) {
                    return 1;
                }
                pluschecker[0] = p[0];
                pluschecker[1] = p[1];

                if(isint(pluschecker[1]) && pluschecker[0] > 0) {
                    (temp1) += 2;
                    return chex(temp1, temp2);
                }
                if(!isint(str[temp2])) {
                    (temp1) += 2;
                    return chex(temp1, temp2);
                }
                pluschecker[1] = regex[temp1];
                pluschecker[0]--;
                if(pluschecker[0] < 0) {
                    pluschecker[0] = 0;
                }
                (temp2)++;
                
                (temp1) += 2;
                return chex(temp1, temp2);
            }
            else {
                if(isint(str[temp2])) {
                    temp1++;
                    temp2++;
                    return chex(temp1, temp2);
                }
                return 0;
                
            }
        }
    }

    if(regex[(temp1) + 1] == '+' || regex[(temp1) + 1] == '*' || regex[(temp1) + 1] == '?') {
        backslash = 0;
        if(regex[(temp1) + 1] == '+') {
            if(pluschecker[0]-- > 0 && pluschecker[1] == regex[(temp1)]) {
                (temp1) += 2;
                return chex(temp1, temp2);
            }
            if (regex[temp1] != str[temp2]) {
                return 0;
            }
            pluschecker[1] = regex[temp1];
            pluschecker[0] = 0;
            while (pluschecker[1] == str[temp2]) {
                pluschecker[0]++;
                (temp2)++;
            }
            pluschecker[0]--;
            (temp1) += 2;
            return chex(temp1, temp2);
        }
        else if(regex[(temp1) + 1] == '*') {
            p[1] = pluschecker[1];
            p[0] = pluschecker[0];
            if(chex(temp1 + 2, temp2) == 1) {
                return 1;
            }
            pluschecker[0] = p[0];
            pluschecker[1] = p[1];

            if(pluschecker[1] == regex[temp1] && pluschecker[0] > 0) {
                (temp1) += 2;
                return chex(temp1, temp2);
            }
            if(regex[temp1] != str[temp2]) {
                (temp1) += 2;
                return chex(temp1, temp2);
            }
            pluschecker[1] = regex[temp1];
            pluschecker[0] = 0;
            while (pluschecker[1] == str[temp2]) {
                pluschecker[0]++;
                (temp2)++;
                p[1] = pluschecker[1];
                p[0] = pluschecker[0];
                if(chex(temp1 + 2, temp2) == 1) {
                    return 1;
                }
                pluschecker[0] = p[0];
                pluschecker[1] = p[1];
            }
            (temp1) += 2;
            return chex(temp1, temp2);


        }
        else if(regex[(temp1) + 1] == '?') {
            p[1] = pluschecker[1];
            p[0] = pluschecker[0];
            if(chex(temp1 + 2, temp2) == 1) {
                return 1;
            }
            pluschecker[0] = p[0];
            pluschecker[1] = p[1];

            if(regex[temp1] != str[temp2]) {
                (temp1) += 2;
                return chex(temp1, temp2);
            }
            pluschecker[1] = regex[temp1];
            pluschecker[0]--;
            if(pluschecker[0] < 0) {
                pluschecker[0] = 0;
            }
            (temp2)++;
            (temp1) += 2;
            return chex(temp1, temp2);
        }
        return 1;
    }

    else {
        backslash = 0;
        if(str[(temp2)++] != regex[(temp1)++]) {
            return 0;
        }
        return chex(temp1, temp2);
    }
    return 1;
}



int main() {
    fgets(str, MAX, stdin);
    fgets(regex, MAX, stdin);
    int test = chex(0, 0);
    if(test == 0) {
        printf("No\n");
        return 0;
    }
    if(test == 1) {
        printf("Yes\n");
        return 0;
    }

}