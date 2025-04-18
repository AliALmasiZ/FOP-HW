//403100043
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** str ;
int size[100000] = {};
int main() {
    int n;
    scanf("%d", &n);
    char temp, temp2;
    temp2 = getchar();
    str = (char **)malloc(100000 * sizeof(char*));
    int x = 0;
    int i = 0;
    while(1) {
        *(str + x) = (char*)realloc(*(str + x), (i + 1) * sizeof(char)) ;
        temp = getchar();
        if(temp  == EOF || temp == '\n') {
            size[x] = i;
            x++;
            *(str + x) = (char*)realloc(*(str + x), sizeof(char)) ;
            str[x][0] = '\0';
            break;
        }
        else if(temp == ' ') {
            if(i > n) {
                printf("can not be aligned");
                return 0;
            }
            size[x] = i;
            if(i != 0) x++;
            size[x] = 1;
            *(str + x) = (char*)realloc(*(str + x), sizeof(char)) ;
            str[x][0] = temp;
            x++;
            i = 0;
        }
        else if(temp == '\\') {
            temp2 = getchar();
            if(temp2 == 'n') {
                if(i > n) {
                    printf("can not be aligned");
                    return 0;
                }
                size[x] = i;
                if(i != 0) {
                    x++;
                }
                size[x] = 1;
                *(str + x) = (char*)realloc(*(str + x), sizeof(char)) ;
                str[x][0] = '\n';
                x++;
                i = 0;
            }
            else {
                *(str + x) = (char*)realloc(*(str + x), (i + 2) * sizeof(char)) ;
                str[x][i] = temp;
                str[x][i + 1] = temp2;
                i++;
                i++;
            }
        }
        else {
            str[x][i] = temp;
            i++;
        }
    }
    int y = 0;
    for(int i = 0; i < x; i++) {
        y += size[i];
        if(y > n) {
            y = size[i];
            printf("\n");
        }
        for(int j = 0; j < size[i]; j++) {
            printf("%c", str[i][j]);
            if(str[i][j] == '\n') {
                y = 0;
            }
        }
        free(str[i]);
    }
    free(str);
}