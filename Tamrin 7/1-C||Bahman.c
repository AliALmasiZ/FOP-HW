//403100043
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct person { 
    int a;
    char b;
} Person;

typedef struct complex {
    int a;
    int b;
}Complex;

void printc(Complex *num) {
    printf("(%d, %d)\n", num -> a, num -> b);
}

void timesc(Complex n1, Complex n2, Complex *n3) {
    n3 -> a = n1.a * n2.a - n1.b * n2.b;
    n3 -> b = n1.a * n2.b + n1.b * n2.a;

}
int n, t, q;
Complex arr[1111] ;
unsigned char isfull[1111] = {};
void kargar(char* s) {
    char temp[1000] = {};
    int who, first, sec, who2, who3;
    sscanf(s, "%s", temp);
    if (!strcmp(temp, "delete")) {
        sscanf(s, "%s %d", temp, &who);
        who--;
        if(isfull[who] == 0) {
            printf("no number in %d!\n", who + 1);
            return;
        }
        printc(arr + who);
        isfull[who] = 0;
        return;
    }
    if (!strcmp(temp, "add")) {
        sscanf(s, "%s %d %d %d", temp, &who, &first, &sec);
        who--;
        if(isfull[who] != 0) {
            printf("number currently exists in %d!\n", who + 1);
            return;
        }
        (arr + who) -> a = first;
        (arr + who) -> b = sec;
        isfull[who] = 1;
        printf("added successfully!\n");
        return;
    }
    if (!strcmp(temp, "number")) {
        int count = 0;
        for(int i = 0; i < n; i++) {
            if(isfull[i] != 0) {
                count++;
            }
        }
        printf("%d\n", count);
        return;
    }
    if (!strcmp(temp, "operation")) {
        sscanf(s, "%s %d %c %d %s %d", temp, &who, temp, &who2, temp + 1, &who3);
        who--;
        who2--;
        who3--;
        if(isfull[who] == 0) {
            printf("not enough operands!\n");
            return;
        }
        if(isfull[who2] == 0) {
            printf("not enough operands!\n");
            return;
        }
        if(isfull[who3] != 0) {
            printf("destination currently full!\n");
            return;
        }
        isfull[who3] = 1;
        if(*(temp) == '+') {
            arr[who3].a = arr[who2].a + arr[who].a;
            arr[who3].b = arr[who2].b + arr[who].b;
            printc(arr + who3);
            isfull[who3] = 1;
            return;
        }
        if(*(temp) == '-') {
            arr[who3].a = arr[who].a - arr[who2].a;
            arr[who3].b = arr[who].b - arr[who2].b;
            printc(arr + who3);
            isfull[who3] = 1;
            return;
        }
        if(*(temp) == '*') {
            timesc(arr[who], arr[who2], arr + who3);
            printc(arr + who3);
            isfull[who3] = 1;
            return;
        }
    }
    if (!strcmp(temp, "count")) {
        int count = 0;
        sscanf(s, "%s %s %d", temp, temp, &first);
        switch (first)
        {
        case  1:
            for(int i = 0; i < n; i++) {
                if(((arr + i) -> a > 0 && (arr + i) -> b > 0) && isfull[i]) {
                    count++;
                }
            }
            printf("%d\n", count);
            break;
        case 2:
            for(int i = 0; i < n; i++) {
                if(((arr + i) -> a < 0 && (arr + i) -> b > 0 )&& isfull[i]) {
                    count++;
                }
            }
            printf("%d\n", count);
            break;

        case 3:
            for(int i = 0; i < n; i++) {
                if(((arr + i) -> a < 0 && (arr + i) -> b < 0 )&& isfull[i]) {
                    count++;
                }
            }
            printf("%d\n", count);
            break;
        case 4:
            for(int i = 0; i < n; i++) {
                // printc(arr + i);
                if(((arr + i) -> a > 0 && (arr + i) -> b < 0) && isfull[i]) {
                    count++;
                }
            }
            printf("%d\n", count);
            break;
        default:
            break;
        }
        return;
    }
    if (!strcmp(temp, "quadrant")) {
        sscanf(s, "%s %s %d", temp, temp, &who);
        who--;
        if(isfull[who] == 0) {
            printf("no number in %d!\n", who + 1);
            return;
        }
        if((arr + who) -> a > 0 && (arr + who) -> b > 0) {
            printf("1\n");
            return;
        }
        if((arr + who) -> a < 0 && (arr + who) -> b > 0) {
            printf("2\n");
            return;
        }
        if((arr + who) -> a < 0 && (arr + who) -> b < 0) {
            printf("3\n");
            return;
        }
        if((arr + who) -> a > 0 && (arr + who) -> b < 0) {
            printf("4\n");
            return;
        }
        printf("in no quadrant!\n");
        return;
        
    }
    if (!strcmp(temp, "conjugate")) {
        sscanf(s, "%s %d", temp, &who) ;
        who--;
        if (isfull[who] == 0) {
            printf("no number in %d!\n", who + 1);
            return;
        }
        arr[who].b *= -1;
        printc(arr + who);
        return;
    }
    if (!strcmp(temp, "rotate")) {
        sscanf(s, "%s %d %s", temp, &who, temp);
        who--;
        if(isfull[who] == 0) {
            printf("no number in %d!\n", who + 1);
            return;
        }
        Complex rot;
        rot.a = 0;
        if(!strncmp(temp, "clockwise", 9)) {
            rot.b = -1;
        }
        else {
            rot.b = 1;
        }

        timesc(rot, arr[who], arr + who);
        printc(arr + who);
        return;
    }           

}

int main() {
    // Person* fo;
    // fo->a = 12;
    // struct person a;

    char operation[1000];
    scanf("%d %d %d", &n, &t, &q);
    int index;
    for(int i = 0; i < t; i++) {
        scanf("%d ", &index);
        index--;
        scanf("%d %d", &((arr + index)->a), &((arr + index)->b));
        isfull[index] = 1;
    }
    getchar();
    for(int i = 0; i < q; i++) {
        fgets(operation, 1000, stdin);
        kargar(operation);
    }


    // printf("%d", fo->a);

}





 