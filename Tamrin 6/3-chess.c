//403100043
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define MAX_MESSAGE 501

char message[MAX_MESSAGE] = {}, word[20], *endptr, temp[50];

int m, n, number;
char table[51][51] = {};
int pieces['z'];
char characters[] = {"KkQqRrBbNnPpCcHhSsDdIiWwMmGg"};

char str_to_char(char *str) {
    if(!strcmp(str, "king")){
        return 'k';
    }
    if(!strcmp(str, "queen")){
        return 'q';
    }
    if(!strcmp(str, "rook")){
        return 'r';
    }
    if(!strcmp(str, "bishop")){
        return 'b';
    }
    if(!strcmp(str, "knight")){
        return 'n';
        
    }
    if(!strcmp(str, "pawn")){
        return 'p';
        
    }
    if(!strcmp(str, "cannon")){
        return 'c';
        
    }
    if(!strcmp(str, "chariot")){
        return 'h';
        
    }
    if(!strcmp(str, "sorcerer")){
        return 's';
        
    }
    if(!strcmp(str, "dragon")){
        return 'd';
        
    }
    if(!strcmp(str, "ninja")){
        return 'i';
        
    }
    if(!strcmp(str, "warrior")){
        return 'w';
        
    }
    if(!strcmp(str, "mage")){
        return 'm';
        
    }
    if(!strcmp(str, "golem")){
        return 'g';
        
    }
}
void read_input() {
    int col, row;
    char piece;
    scanf("%s %s %s %s %s %d %s %d", word, message, temp, temp, temp, &col, temp, &row);
    col--;
    row--;
    piece = str_to_char(message);
    if(!strcmp(word, "black"))
        piece = toupper(piece);
    pieces[piece] = n * row + col;    
    table[row][col] = piece;
}
void print_table() {
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(table[i][j] == 0) {
                printf(". ");
            }
            else {
                printf("%c ", table[i][j]);
            }
        }
        printf("\n");
    }
}
void move() {

    
    int col, row;
    char piece;
    scanf("%s %s %s %s %d %s %d", word, message, temp, temp, &col, temp, &row);
    col--;
    row--;
    piece = str_to_char(message);
    if(!strcmp(word, "black"))
        piece += 'A' - 'a';
    if(pieces[piece] == -1) {
        return;
    }
    table[pieces[piece] / n][pieces[piece] % n]  = 0;
    pieces[piece] = n * row + col;
    if(table[row][col] != 0) {
        pieces[table[row][col]] = -1;
    }
    table[row][col] = piece;
}
int main() {
    scanf("%d %d", &m, &n);
    memset(pieces, -1, sizeof(pieces));
    scanf("%d", &number);
    // fgets(temp, 50, stdin);
    for(int i = 0; i < number; i++) {
        read_input();
    }
    // print_table();
    scanf("%d", &number);
    for(int i = 0; i < number; i++) {
        move();
        // printf("------------------\n");
    }
        print_table();
    
}