//403100043
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int firster(char* a, char* b) {
    
    for(int i = 0; *(a + i) * *(b + i); i++) {
        int num1 = *(a + i), num2 = *(b + i);
        // if()
        if(num1 > num2) {
            return 1;
        }
        if(num1 < num2) {
            return -1;
        }

    }
}

int main() {
    int n;
    scanf("%d", &n);
    char str[1111];
    char* folders[1001];
    for(int i = 0; i < 1001; i++) {
        folders[i] = (char*)malloc(1111 * sizeof(char));
    }
    folders[1000][1000] = getc(stdin);
    int filler = 0;
    for (int i = 0; i < n; i++) {
        fgets(str, 1111, stdin);
        char *temp_ptr = (char *)malloc(1001), *temp_ptr2 = (char*)malloc(1001);
        temp_ptr = strtok(str, "/");

        while ((temp_ptr2 = strtok(NULL, "/")) != NULL) {
            int bool = 1;
            int j = 0;
            for(j; j < filler; j++) {
                if(strcmp(temp_ptr, folders[j]) == 0) {
                    bool = 0;
                    // temp_ptr = temp_ptr2;
                    strcpy(temp_ptr, temp_ptr2);
                    break;
                }
                if(strcasecmp(temp_ptr, folders[j]) < 0) {
                    
                    break;
                }
            }
            if(bool) {
                filler++;
                for(int k = filler; k > j; k--) {
                        // folders[k] = folders[k - 1];
                        strcpy(folders[k], folders[k - 1]);
                }
                // folders[j] = temp_ptr;
                strcpy(folders[j], temp_ptr);
                // temp_ptr = temp_ptr2;
                strcpy(temp_ptr, temp_ptr2);
            }
        }
    }
    for(int i = 0; i <= filler; i++) {
        printf("%s\n", folders[i]);
    }

}
