//403100043
#include <stdio.h>
int n , m, rows[21][21], cols[21][21], rowNum[21], colNum[21], table[21][21] = {};
void printer();         
void getInput() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n ;i++ ) {
        scanf("%d", &rowNum[i]);
        for(int j = 0; j < rowNum[i]; j++) { 
            scanf("%d", rows[i] + j);
        }
    }   
    for (int i = 0; i < m ;i++ ) {
        scanf("%d", &colNum[i]); 
        for(int j = 0; j < colNum[i]; j++) {
            scanf("%d", cols[i] + j);
        }
    }
}
int checker(int r, int column) {
    int x = n - 1, i = colNum[column];
    if(colNum[column] == 0) {
        for(int j = x; j >= r; j--) {
                    if(table[j][column] != 0) {
                        return 0;
                    }
                }
                return 1;
    }
    int temp = cols[column][--i];
    while(x >= r) {
        if(table[x--][column]) {
            if(temp-- == 0) {
                return 0;
            }
        }else if (temp == 0 ) {
            if(i != 0)
                temp = cols[column][--i];
            else
                for(int j = x; j >= r; j--) {
                    if(table[j][column] != 0) {
                        return 0;
                    }
                }
        }else { 
            if(temp != cols[column][i])
                for(int j = x; j >= r; j--) {
                    if(table[j][column] != 0) { 
                        return 0;
                    }
                }
        }
    }
    return 1;
}
int tableMaker(int row) {
    if(row == -1)   
        return 1;
    int x = 0, y = 0, k = 0, dis[21] = {}, temp = 1  , temp2 = 0;
    if(rowNum[row] == 0) {
        for(int j = 0; j < m; j++) {
                if(checker(row, j)==0 ) {
                      temp = 0;
                    break;
            }
        }
        if(temp && tableMaker(row - 1)) {
            return 1;
        }
        return 0;
    }
    for(int i = 1; i < rowNum[row]; i++) {
        dis[i] = 1;
    }
    while(1) {
        temp = 1;
        temp2 = 0;  
        if (x >= m ) {  
                int j = 0;
                if(dis[0] != 0  ) {     
                    if(dis[0] == 1)
                        temp2 = 1;
                    dis[0] = 0;
                    dis[1]++;
                    if(rowNum[row] == 1)
                        return 0;
                }       
                if (temp2) {
                    while(1) {
                        j++;
                        if(j == rowNum[row] - 1) {
                            return 0;
                        }
                        if(dis[j] == 1)
                            break;  
                         
                        if (dis[j] == 2) {
                            dis [j] = 1;
                            dis [j + 1]++;  
                            continue;
                        }
                        dis [j] = 1;
                        dis [j + 1]++;
                        break;
                    }
                }                   
        }
        x = 0;  
        for (int j = 0; j < rowNum[row]; j++) {
            for(k = x; k < x + dis[j]; k++) {
                table[row][k] = 0;
            }
            x = k;
            for(k = x   ; k < x + rows[row][j]; k++) {
                table[row][k] = 1;
            }
            x = k;
        }
        for(k = x; k < m; k++) {
                table[row][k] = 0;
        }
        for(int j = 0; j < m; j++) {
                if(checker(row, j)==0 ) {
                    temp = 0;
                    break;
            }
        }

            if(temp && tableMaker(row - 1)) {
            return 1;
        }
        dis[0]++;
        // for(int i = 0; i < m; i++) {
        //     table[row][i] = 0;  
        // }        
    }

}

void printer() {        
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(table[i][j] == 1)
                printf("EE");
            else    
                printf("  ");
        }   
        printf("\n");
    }
        
}
int main() {
    getInput();     
    tableMaker(n - 1);
    printer();
    return 0;
}
/*
0 1 0 1 1 0 
0 0 0 0 0 0
1 1 0 1 1 1
1 1 0 <0 1 0
0 0 1 1 1 1 >
1 0 0 0 0 0
*/
