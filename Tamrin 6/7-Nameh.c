//403100043
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 11111
int space(char c) {
    if(c == ' ' || c == '\t' || c == '\n') 
        return 1;
    return 0;
}
void remove_space(char *s) {
    int i = 0, j = 0;
    while(space(s[i])){i++;}
    while (s[j] != '\0') {
        s[j++] = s[i++];
    }
    while(space(s[j]) || s[j] == '\0') {
        j--;
    }
    s[j + 1] = '\0';
}
unsigned char str[MAX_SIZE] = {};
int cursor = 0;
void process(char *op) {
    int len = strlen((char*)str) - 1;
    int num1, num2;
    int cursor_move = 0;
    char temp[MAX_SIZE], temp2[MAX_SIZE], temp3[MAX_SIZE];
    sscanf(op, "%s", temp);
    if(!strcmp(temp, "move")) {
        sscanf(op, "%s %d", temp, &cursor_move);
    }
    else if(!strcmp(temp, "position")) {
        cursor_move = 0;
        printf("%d\n", cursor);
    }
    else if(!strcmp(temp, "shift")) {
        sscanf(op, "%s %d %d", temp, &num1, &num2);
        num2 %= 'z' - 'a' + 1;
        cursor_move = num1;
        if(cursor + num1 >= len || cursor + num1 < 0){
            printf("Not enough characters.\n");
            return;
        }
        if (num1 > 0) {
            for(int i = 0; i < num1; i++) {
                if(str[cursor + i] >= 'a' && str[cursor + i] <= 'z') {
                    str[cursor + i] += num2;
                    while(str[cursor + i] > 'z') {
                        str[cursor + i] -= 'z' - 'a' + 1;
                    }
                    while(str[cursor + i] < 'a') {
                        str[cursor + i] += 'z' - 'a' + 1;
                    }
                }
                else if(str[cursor + i] >= 'A' && str[cursor + i] <= 'Z') {
                    str[cursor + i] = num2 + str[cursor + i];
                    while(str[cursor + i] > 'Z') {
                        str[cursor + i] -= 'z' - 'a' + 1;
                    }
                    while(str[cursor + i] < 'A') {
                        str[cursor + i] += 'z' - 'a' + 1;
                    }
                }
            }
        }
        else {
            for(int i = 0; i < -num1; i++) {
                if(str[cursor - i] >= 'a' && str[cursor - i] <= 'z') {
                    str[cursor - i] += num2;
                    while(str[cursor - i] > 'z') {
                        str[cursor - i] -= 'z' - 'a' + 1;
                    }
                    while(str[cursor - i] < 'a') {
                        str[cursor - i] += 'z' - 'a' + 1;
                    }
                }
                else if(str[cursor - i] >= 'A' && str[cursor - i] <= 'Z') {
                    str[cursor - i] = num2 + str[cursor - i];
                    while(str[cursor - i] > 'Z') {
                        str[cursor - i] -= 'z' - 'a' + 1;
                    }
                    while(str[cursor - i] < 'A') {
                        str[cursor - i] += 'z' - 'a' + 1;
                    }
                }
            }
        }
    }
    else if(!strcmp(temp, "upper")) {
        sscanf(op, "%s %d", temp, &num1);
        cursor_move = num1;
        if(cursor + num1 >= len || cursor + num1 < 0){
            printf("Not enough characters.\n");
            return;
        }
        if(num1 > 0){
            for(int i = 0; i < num1; i++) {
                if(str[cursor + i] >= 'a' && str[cursor + i] <= 'z') {
                    str[cursor + i] += 'A' - 'a';
                }
            }
        }
        else{
            for(int i = 0; i < -num1; i++) {
                if(str[cursor - i] >= 'a' && str[cursor - i] <= 'z') {
                    str[cursor - i] += 'A' - 'a';
                }
            }
        }
                
    }
    else if(!strcmp(temp, "lower")) {
        sscanf(op, "%s %d", temp, &num1);
        cursor_move = num1;
        if(cursor + num1 >= len || cursor + num1 < 0){
            printf("Not enough characters.\n");
            return;
        }
        if(num1 > 0){
            for(int i = 0; i < num1; i++) {
                if(str[cursor + i] >= 'A' && str[cursor + i] <= 'Z') {
                    str[cursor + i] -= 'A' - 'a';
                }
            }
        }
        else {
            for(int i = 0; i < -num1; i++) {
            if(str[cursor - i] >= 'A' && str[cursor - i] <= 'Z') {
                str[cursor - i] -= 'A' - 'a';
            }
        }
        }
    }
    else if(!strcmp(temp, "count")) {
        sscanf(op, "%s %s", temp, temp2);
        char *copy = (char*)calloc(MAX_SIZE, sizeof(char));
        strcpy(copy, (char*)str);
        int counter = 0;
        while ((copy = strstr(copy, temp2)) != NULL) {
            counter++;
            copy++;
        }   
        printf("%d\n", counter);
        return;
    }
    else if(!strcmp(temp, "replace")) {
        sscanf(op, "%s %s %s", temp, temp2, temp3);
        int len2 = strlen(temp3);
        int len1 = strlen(temp2);
        char *copy = (char*)calloc(MAX_SIZE, sizeof(char));
        strcpy(copy, (char*)str);
        char *test = copy;
        while((test = strstr(test, temp2)) != NULL) {
            int index = test - copy;
            strcpy((char*)str + index + len2, test + len1);
            for(int i = 0; i < len2; i++) {
                str[i + index] = temp3[i];
            }
            strcpy(copy, (char*)str);
            len = strlen((char*)str) - 1;
            test += len2;
            if (index + len1 >= len)
                break;
        }
        free(copy);
        cursor = 0;
        return;
            
        
    }
    else if(!strcmp(temp, "translate")) {
        sscanf(op, "%s %s", temp, temp2);
        int u = 0;
        if(!strcmp(temp2, "Hindi")) {

            while(str[u] != '\0'){
                
                if(str[u] == 't' || str[u] == 'T') {
                    str[u] += 'd' - 't';
                }
                u++;
            }
            return;
        }
        else if(!strcmp(temp2, "French")) {
            while(str[u] != '\0'){
                if(str[u] == 'r' || str[u] == 'R') {
                    str[u] += 'q' - 'r';
                }
                u++;
            }
            return;
        }
        
    }
    else if(!strcmp(temp, "keke")) {
        printf("%d {%s}\n", cursor, str);
    }
    cursor += cursor_move;
    if (cursor >= len || cursor < 0) {
        printf("Not enough characters.\n");
        cursor -= cursor_move;
    }

    return;
}


int main() {
    
    fgets((char*)str, MAX_SIZE, stdin);
    // remove_space((char*)str);
    char operation[MAX_SIZE];
    do {
        fgets(operation, MAX_SIZE, stdin);
        process(operation);
    } while(strncmp(operation, "&&", 2));
    printf("%s\n", (char*)str);
}