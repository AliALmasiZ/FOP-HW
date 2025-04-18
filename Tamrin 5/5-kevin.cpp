//403100043
#include <stdio.h>
#include <stdlib.h>

char* find_array(void* data, int* password) {
    char* ans = (char*)calloc(1001 , sizeof(char));
    int count = 0;
    int counter = 7;
    for(int i = 0; *(password + i) != 0; i++) {
        int temp = *(password + i);
        if(temp > 0) {
            *(ans + count) += ((*(((char*)data) + (temp-1)/8) >> ((8 - (temp % 8))%8)) & 1) << counter--;
            if(counter < 0){
                counter = 7;
                count++;
            }
        }else {
            temp *= -1;
            char x = *(((char*)data) + temp - 1);
            for(int i = 7; i >= 0; i--) {
                *(ans + count) += ((x >> i) & 1) << counter--;
                if(counter < 0) {
                    counter = 7;
                    count++;
                }
            }
            
        }
    }
    if(counter == 7) {
        *(ans + count) = '\0';
    }
    else {
        *(ans + ++count) = '\0';
    }
    return ans;
}
/*
int main() {
    unsigned char data[8] = {253, 60, 120, 92, 8, 201, 185, 212};
    int password[9] = {9, 18, 17, 7, 35, -6, 2, -8, 0};
    for(int i = 0; i < 5; i++) {
        printf("%c ", *((find_array(data, password)) + i));
    }
    
}
*/