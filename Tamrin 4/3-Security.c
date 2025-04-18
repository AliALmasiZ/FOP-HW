//403100043
#include <stdio.h>

int punc(char s[]) {
    char t[] = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    for (int i = 0; s[i] != ' '; i++){
        for (int j = 0; t[j] != '\0'; j++) { 
            if(t[j] == s[i]) 
                return 1;
                
        }
    }
    return 0;
}

int uppercase(char s[]) {
    for(int i = 0; s[i] != ' '; i++)
        if('A' <= s[i] && 'Z' >= s[i]) 
            return 1;
    return 0;

}

int vowel(char s[]){
    for (int i = 0; s[i] != ' '; i++) {
        if (s[i] == 'A' || s[i] == 'a' || s[i] == 'E' || s[i] == 'e' || s[i] == 'U' || s[i] == 'u' ||
            s[i] == 'I' || s[i] == 'i' || s[i] == 'O' || s[i] == 'o'){
                return 1;
            }
        
    }
    return 0;
}

int isDigit(char s){
    if(s >= '0' && s <= '9')
        return 1;
    return 0;
}

int digit(char s[]) {
    int m = 0, res = 0, counter = 1;
    for (int i = 0; s[i] != ' '; i++){
        if(isDigit(s[i])){
            m += s[i] - '0';
            if(isDigit(s[i+1]) && s[i+1] != ' '){
                m *= 10;
                counter++;
            }
            else {
                if (s[i-counter] == '-')
                    m *= -1;
                res += m;
                m =0;
                counter = 1;
            } 
                
        }
    }
    if(res == 10)
        return 2;
    if (res != 0)
        return 1;
    return 0;
}

int homelander(char s[]) {
    char t[23] = "homelanderandstarlight";
    int x , test = 0, j;
    for (int i = 0; s[i] != ' '; i++) {
        x = i;
        j = 0;
        test = 0;
        t[23] = "homelanderandstarlight";
        while(t[j++] != '\0') {
            if (t[j-1] == s[x]) {
                x++;
                test++;
                j = 0; 
                t[j-1] = ' ';
            }
        }
        if (test == 22) 
            return 1;
        else 
            test = 0;
    }
    return 0;
}
int main() {
    char s[6000];
    int i = -1;
    int score = 0;
    int tedad = 0;
    do {
        i++;
        tedad++;
        scanf("%c", &s[i]);

    } while (s[i] != ' ');
    score += uppercase(s);
    score += digit(s);
    score += vowel(s);
    score += punc(s);
    score += (tedad>10);
    score += homelander(s);
    printf("%d", score);
    return 0;
}