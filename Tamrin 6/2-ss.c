//403100043
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY 111
#define MAX_MESSAGE 1001
int space(char c) {
    if (c == ' ' || c == '\t' || c == '\n') { 
        return 1;
    }
    return 0;
}

void remove_whitespace(char* s) {
    int j = 0, i = 0;
    while(space(s[i])) i++;
    while(s[j] != '\0') {
        s[j++] = s[i++];
    }
    while(space(s[j]) || s[j] == '\n' || s[j] == '\0') {
        j--;
    }
    s[j + 1] = '\0';
}
void encrypt() {
    int tmp;
    char key[MAX_KEY], message[MAX_MESSAGE];
    fgets(key, MAX_KEY, stdin);
    remove_whitespace(key);
    char* key1 = strtok(key, " ");
    char* key2 = strtok(NULL, " ");
    if(key2 == NULL) {
        key2 = key1;
    }
    remove_whitespace(key2);
    int k = strlen(key2);   
    fgets(message, MAX_MESSAGE, stdin);
    remove_whitespace(message);
    int message_len = strlen(message), checksum = 0;
    for(int i = 0; i < message_len; i++) {
        tmp = message[i] ^ key2[i % k];
        printf("%02x", tmp & 255);
        checksum += (int)message[i];
        checksum &= 256*256 - 1;
    }
    printf("%02x%02x\n", checksum & 255, checksum >> 8);
}
void decrypt() {
    char key[MAX_KEY], message[MAX_MESSAGE], res[MAX_MESSAGE] = {'\0'}, *endptr;
    fgets(key, MAX_KEY, stdin);
    char* key1 = strtok(key, " ");
    char *key2 = strtok(NULL, " ");
    if(key2 ==NULL) {
        key2 = key1;
    }
    remove_whitespace(key2);
    int k = strlen(key2), checksum = 0;
    fgets(message, MAX_MESSAGE, stdin);
    remove_whitespace(message);
    int message_len = strlen(message) - 4;
    char temp[3];
    for(int i = 0; i < message_len; i++) {
            char temp[3];

            temp[0] = *(message + i);
            temp[1] = *(message + i + 1);
            temp[2] = '\0';
            if(space(temp[0]) || space(temp[1]))
                continue;
            char ans = (char)strtol(temp, &endptr, 16) ^ key2[(i / 2) % k];
            
            strncat(res, &ans, 1);
            checksum += (int)ans;
            checksum &= 256*256 - 1;
            i++;
    }
    temp[0] = *(message + message_len + 2);
    temp[1] = *(message + message_len + 3);
    temp[2] = '\0';
    int orgsum = strtol(temp, &endptr, 16) * 256;
    temp[0] = *(message + message_len);
    temp[1] = *(message + message_len + 1);
    orgsum += strtol(temp, &endptr, 16);
    if(orgsum == checksum) {
        printf("%s\n", res);
        return ;
    }
    printf("Invalid key!\n");
    
}




int main() {
    char op[] = "decrypt";
    while(1) {
        scanf("%s", op);
        if(strcmp(op, "encrypt") == 0) {
            encrypt();
        }
        else if(strcmp(op, "decrypt") == 0) {
            decrypt();
        }
        else if (strcmp(op, "exit") == 0) {
            break;  
        }
        else {
            printf("Invalid Input!!\n");
        }
    }

    return 0;
}