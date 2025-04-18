//403100043
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000
// #pragma pack(1)
typedef struct doll {
    unsigned int id;
    size_t array_size;
    struct doll **insides;
}Doll;
void kargar(char *str);
Doll **arr;
size_t kol;
void remake_array() {
    size_t u = 0;
    while(u < kol) {
        if(arr[u] == NULL) {
            for(size_t i = u; i < kol; i++) {
                arr[i] = arr[i + 1];
            }
            kol--;
        }
        else {
            u++;
        }
    }
}
void shift_right(int n, unsigned start) {
    if(n > 0) {
        int end = 0;
        while (arr[end] != NULL) {
            end++;
        }
        for (int i = end; i >= start; i--) {
            arr[i + n] = arr[i];
        }
    }
    else if(n < 0) {
        n *= -1;
        for (int i = start; i < MAX_SIZE; i++ ) {
            arr[i] = arr[i + n];
            if(arr[i] == NULL) 
                break;
        }
    }
    return;
}
void put_into(Doll** aroosak, Doll *destination) {
    destination -> array_size++;
    destination -> insides = (Doll**)realloc(destination -> insides, destination -> array_size * sizeof(Doll*));
    destination -> insides[destination -> array_size - 1] = *(aroosak);
    *(aroosak) = NULL;

}
void sort_by_id(Doll **doll, int start, int end) { //includes start index but not end index
    int u = start;
    while(u != end) {
        Doll *min_id = doll[u]; 
        Doll *temp;
        for(int i = u; i < end; i++) {
            if(min_id -> id > doll[i] -> id) {
                temp = min_id;
                min_id = doll[i];
                doll[i] = temp;
            }
        }
        doll[u++] = min_id;
    }
}
void handle_put(char *str) {
    int k, i, next_index;
    sscanf(str, "%*s %d %d", &k, &i);
    i--;// zero-base
    for (int j = 0; j < k; j++) {
        scanf("%d ", &next_index);
        next_index--;//zero-base
        put_into(&arr[next_index], arr[i]);
    }
    remake_array();
}
void handle_empty(char *str) {
    int i;
    sscanf(str, "%*s %d", &i);
    i--;
    shift_right(arr[i] -> array_size, i + 1);
    for(int j = i + 1; j <= i + arr[i] -> array_size; j++) {
        arr[j] = arr[i] -> insides[j - i - 1];
    }
    sort_by_id(arr, i + 1, i + arr[i] -> array_size + 1);
    kol += arr[i] -> array_size;
    arr[i] -> array_size = 0;
    arr[i] -> insides = NULL;
}
void handle_dolls_count() {
    printf("%lu\n", kol);
}
int count(Doll* aroosak) {
    int res = 0;
    for(int i = 0; i < aroosak -> array_size; i++) {
        res += count(aroosak -> insides[i]);
        res++;
    }
    return res;
}
void handle_count(char *str) {
    int i;
    sscanf(str, "%*s %d", &i);
    i--;
    printf("%d\n", count(arr[i]) + 1); // chera +1?
}
void handle_get_id(char *str) {
    int i;
    sscanf(str, "%*s %d", &i);
    i--;
    printf("%d\n", arr[i] -> id);
}
void kargar(char* str) {
    char command[MAX_SIZE];
    sscanf(str, "%s", command);
    if(!strcmp(command, "put")) {
        handle_put(str);
    }
    else if(!strcmp(command, "empty")) {
        handle_empty(str);   
    }
    else if(!strcmp(command, "main_dolls_count")) {
        handle_dolls_count();
    }
    else if(!strcmp(command, "count")) {
        handle_count(str);
    }
    else if(!strcmp(command, "get_id")) {
        handle_get_id(str);
    }
    else if(!strcmp(command, "keke")) {
        printf("kol : %lu\n", kol);
        for(int i = 0; i < kol; i++) {
            printf("%d\n", arr[i] -> id);
        }
    }
}
int main() {
    int n, q;
    char str[MAX_SIZE];
    scanf("%d %d", &n, &q);
    kol = n;
    arr = (Doll**)calloc(MAX_SIZE, sizeof(Doll*));
    for(int i = 0; i < n; i++) {
        arr[i] = (Doll*)malloc(sizeof(Doll));
        arr[i] -> array_size = 0;
        arr[i] -> insides = NULL;
        arr[i] -> id = i + 1;
    }
    getchar();
    for(int i = 0; i < q; i++) {
        fgets(str, MAX_SIZE, stdin);
        kargar(str);
    }
}
// #pragma pack()