//403100043
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//------------------defines------------------------
#define MAX_SIZE 80

//-------------------prototypes---------------------

void kargar(char *input);
void handle_add(char *str);
void handle_lca(char *str);
void handle_switch(char *str);
void handle_print(char *str);
void handle_predict(char *str);
int lca(int index1, int index2);
int binary_search(int a, int arr[], int start, int end);
void print_child(int index, int depth);
int compare_str(const void *a, const void *b);
int compare_number(const void *a, const void *b);
long long binary_search2(char* src, char **arr, int start, int end);
long long search(char *src, char **arr, int n);

//--------------------structs------------------------
// #pragma pack(1)
typedef struct Node {
    unsigned int id;
    char name[MAX_SIZE];
    long long parent_id;   
    double height;
    char eye[MAX_SIZE];
}Node;
// #pragma pack()

//--------------------main---------------------------
Node ** arr;
int kol = 0;
int start = 0;
int main() {
    char input[50];
    while(strncmp(fgets(input, 50, stdin), "end", 3)) {
        kargar(input);
    }
}
//-------------------functions----------------------
void kargar(char* input) {
    char command[50];
    sscanf(input, "%s", command);
    if(!strcmp(command, "add")) {
        handle_add(input);
    }
    else if(!strcmp(command, "lca")) {
        handle_lca(input);
    }
    else if(!strcmp(command, "switch")) {
        handle_switch(input);
    }
    else if(!strcmp(command, "print")) {
        handle_print(input);
    }
    else if(!strcmp(command, "predict")) {
        handle_predict(input);
    }
}

void handle_add(char *str) { //farz increasing 
    kol++;
    arr = (Node**)realloc(arr, kol * sizeof(Node*));
    arr[kol - 1] = (Node*)malloc(sizeof(Node));
    long long id, parent_id;
    sscanf(str, "%*s %lld %*s %lld", &id, &parent_id);
    if((parent_id >= start + kol || parent_id < start) && parent_id != -1) {
        kol--;
        printf("Parent doesn't exist!\n");
        return;
    }
    if(kol == 1)
        start = id;
    start = start < id ? start : id;
    sscanf(str, "%*s %u %s %lld %lf %s",
        &(arr[kol - 1] -> id),
        arr[kol - 1] -> name, 
        &(arr[kol - 1] -> parent_id), 
        &(arr[kol - 1] -> height), 
        arr[kol - 1] -> eye);
}

void handle_lca(char *str) {
    int first, second;
    sscanf(str, "%*s %d %d", &first, &second);
    int res = lca(first - start, second - start);
    if(res != -1) {
        printf("ID: %d NAME: %s\n", arr[res]->id, arr[res]->name);
        return;
    }
    printf("No common ancestor exists!\n");
    return;
}

int lca(int index1, int index2) {
    int path[1111] = {};
    int parent1 = arr[index1]->parent_id;
    int parent2 = arr[index2]->parent_id;
    path[0] = index1;
    int i = 1;
    while(parent1 != -1) {
        path[i] = parent1 - start;
        index1 = path[i++];
        parent1 = arr[index1]->parent_id;
    }

    qsort(path, i, sizeof(int), compare_number);

    if (binary_search(index2, path, 0, i-1)) {
            return index2;
    }
    while (parent2 != -1) {
        index2 = parent2 - start;
        parent2 = arr[index2]->parent_id;
        if (binary_search(index2, path, 0, i-1)) {
            return index2;
        }
    }
    return -1;

    
}

int binary_search(int a, int* arr, int start, int end) {
    if(start > end) {
        return 0;
    }
    int middle = (start + end) / 2;
    if(arr[middle] == a) {
        return 1;
    }
    if(arr[middle] < a) {
        return binary_search(a, arr, start, middle - 1);
    }
    if (arr[middle] > a) {
        return binary_search(a, arr, middle + 1, end);
    }
    return 0;
}

void handle_switch(char *str) {
    int first, second;
    sscanf(str, "%*s %d %d", &first, &second);
    first -= start;
    second -= start;
    int res = lca(first, second);
    if(arr[first]->parent_id == -1 && arr[second]->parent_id == -1) {
        printf("The given IDs are both roots!\n");
        return;
    }
    if(arr[first]->parent_id == arr[second]->parent_id) {
        printf("The given IDs are already siblings!\n");
        return;
    }
    if(res == first || res == second) {
        printf("You can't switch with an ancestor!\n");
        return;
    }
    long long temp = arr[first]->parent_id;
    arr[first]->parent_id = arr[second]->parent_id;
    arr[second]->parent_id = temp;
    return;
}
void handle_print(char *str) {
    int id;
    sscanf(str, "%*s %d", &id);
    print_child(id - start, 0);
}
void print_child(int index, int depth) {
    for(int i = 0; i < depth; i++) {
        printf("\t");
    }
    printf("%s\n", arr[index]->name);
    for(int i = 0; i < kol; i++) {
        if(arr[i]->parent_id == index + start){
            print_child(i, depth + 1);
        }
    }
}
void handle_predict(char *str) {
    int id;
    sscanf(str, "%*s %d", &id);
    id -= start;
    int weight = 1;
    int temp = id;
    while (arr[temp]->parent_id != -1) {
        weight++;
        temp = arr[temp]->parent_id - start;
    }
    temp = id;
    char *star[MAX_SIZE]; // star = string array
    for(int i = 0; i < MAX_SIZE; i++) {
        star[i] = (char*)calloc(MAX_SIZE, sizeof(char));
    }
    int res[MAX_SIZE] = {};
    int end = 0;
    int sum = (weight * (weight + 1)) / 2;
    double av = 0;
    while (weight > 0) {
        long long index = search(arr[temp]->eye, star, end + 1);
        if(index == -1) {
            index = end;
            // star[end] = (char*)calloc(MAX_SIZE , sizeof(char));
            strcpy(star[end], arr[temp]->eye);
            end++;
        }
        av += weight * arr[temp]->height;
        res[index] += weight;
        temp = arr[temp]->parent_id - start;
        weight--;
    }
    int Mindex = 0;
    for(int i = 0; i < end; i++) {
        if(res[Mindex] < res[i])
            Mindex = i;
        else if (res[Mindex] == res[i]) {
            if(strcasecmp(star[Mindex], star[i]) > 0) {
                Mindex = i;
            }
        }
    }
    av /= sum;
    av = floor(av * 100) / 100;
    double kheili_temp;
    kheili_temp = res[Mindex] * 100;
    kheili_temp /= sum;
    kheili_temp = floor(kheili_temp * 100) / 100;
    printf("eye color: %s %0.2lf%%\n", star[Mindex], kheili_temp);
    printf("height: %0.2lf\n", av);

    
}

int compare_str(const void *a, const void *b) {
    return strcasecmp(*(char**)a, *(char**)b);
}

int compare_number(const void *a, const void *b) {
    return - *(int *)a + *(int *)b;
}

long long binary_search2(char* src, char **arr, int start, int end) { //test
    int middle = (start + end - 1) / 2; //include start but not end
    if (start >= end) {
        return -1;
    }
    if(strcasecmp(src, arr[middle]) > 0) {
        return binary_search2(src, arr, middle + 1, end);
    }
    if(strcasecmp(src, arr[middle]) < 0) {
        return binary_search2(src, arr, start, middle - 1);
    }
    if(strcasecmp(src, arr[middle]) == 0) {
        return middle;
    }
    return -1;
}
long long search(char* src, char **arr, int n) {
    for(int i = 0; i < n; i++) {
        if(!strcmp(src, arr[i])){
            return i;
        }
    }
    return -1;
}
/*
int mysort(char ** strarr, int end) { // not include end
    for(int i = 0; i < end; i++) {
        int test = strcasecmp(strarr[i], strarr[end - 1]);
        if(test < 0) {
            char *tmp_ptr = strarr[end - 1];
            for(int j = i; j < end - 1; j++) {
                strarr[j + 1] = strarr[j] ;
            }
            strarr[i] = tmp_ptr;
            return i;
        }
        if(test == 0) {
            return i;
        }
    }
    return end - 1;
}
*/