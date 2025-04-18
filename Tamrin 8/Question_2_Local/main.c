#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/***********************/
/*                     */
/*      Ali Almasi     */
/*      403100043      */
/*                     */
/***********************/

#define MAX_LINE 1024
#define MAX_WORD 100
#define MAX_CATEGORIES 10
#define MAX_KEYWORDS 50
#define DELIMS "\t\n.,;!?\\\"'()[]{}:- "

typedef struct _keyword_element_t{
    char keyword[MAX_WORD];
    double weight;
}KeywordElement;

int keywords_extractor(KeywordElement *dest, char * str, char* category) {
    char *token = strtok(str, ": \n\r");
    strcpy(category, token);
    int i = 0;
    token = strtok(NULL, ": \n\r");
    while(token != NULL) {
        strcpy(dest[i].keyword, token);
        token = strtok(NULL, ": \n\r");
        char *temp;
        dest[i].weight = strtod(token, &temp);
        token = strtok(NULL, ": \n\r");
        i++;
    }
    return i;
}
int find_word(const char* src, const char * word) {
    char cpy[MAX_LINE * MAX_LINE];
    strcpy(cpy, src);
    char *token = strtok(cpy, DELIMS);
    int count = 0;
    while(token != NULL) {
        if(!strcasecmp(word, token)) {
            count++;
        }
        token = strtok(NULL, DELIMS);
    }
    return count;
}
double relevance(KeywordElement *elements, const char *str) {
    double res = 0;
    for(int i = 0; i < MAX_KEYWORDS; i++) {
        res += find_word(str, elements[i].keyword) * elements[i].weight;
    }
    return res;
}

int main(int argc, char const *argv[]) {
    const char* categories_path = argv[1];
    FILE *categories_file = fopen(categories_path, "r");
    char line[MAX_LINE];
    KeywordElement elements[MAX_CATEGORIES][MAX_KEYWORDS] = {};
    char category[MAX_CATEGORIES][MAX_WORD] = {};
    int categories_count = 0;
    while (fgets(line, MAX_LINE, categories_file) != NULL) {
        line[strcspn(line, "\r")] = 0;
        keywords_extractor(elements[categories_count], line, category[categories_count]);
        categories_count++;
    }
    fclose(categories_file);

    
    for (int i = 2; i < argc; i++) {//!!!!
        const char *path = argv[i];
        FILE *fptr = fopen(path, "r");
        char str[MAX_LINE * MAX_LINE] = {};
        int bool = 0;
        char line[MAX_LINE] = {};
        while(fgets(line, MAX_LINE, fptr) != NULL) {
            line[strcspn(line, "\r\n")] = 0;
            strcat(str, line);
        }
        double R = 0, temp;
        int max_idx;
        for(int i = 0; i < categories_count; i++) {
            temp = relevance(elements[i], str);
            if(temp > R) {
                bool = 0;
                max_idx = i;
                R = temp;
            }
            else if(temp == R) {
                bool = 1;
            }
        }
        if(bool) {
            printf("%s\n", "Unknown");
        }else
            printf("%s\n", category[max_idx]);
        fclose(fptr);
    }

    return 0;
}
