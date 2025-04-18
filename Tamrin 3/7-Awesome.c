//403100043
#include <stdio.h>

int main() {
    int m, n , boats=0 , bombs ,x,y;
    scanf("%d %d",&m,&n);
    int a[100][100];
    for (int i= 0;i<m ; i++){
        for(int j = 0; j<n ;j++) scanf("%d", &a[i][j]);
    }
    scanf("%d", &bombs);
    for (int i= 0;i<m ; i++){
        for(int j = 0; j<n ;j++) if(a[i][j]==1) boats++;
    }
    int bomb_copy = bombs;
    int boat_copy = boats;
    while(bombs > 0 && boats !=0){
        scanf("%d %d", &x , &y);
        if(x >= m || y>=n) printf("\nOut Of Board, %d of %d bombs have been used.", bomb_copy-bombs , bomb_copy);
        else if(a[x][y]==2) printf("\nWrong Place, %d of %d bombs have been used.", bomb_copy-bombs , bomb_copy);
        else if (a[x][y]==1) {bombs--;boats--;a[x][y]=2;printf("\nHit, %d of %d bombs have been used.", bomb_copy-bombs , bomb_copy);}
        else if (a[x][y]==0) {bombs--;a[x][y]=2;printf("\nSea, %d of %d bombs have been used.", bomb_copy-bombs , bomb_copy);}
    }

    if(boats == 0)printf("\nYou Won!");
    else printf("\nYou Lost!, %d of %d boats still remaining.", boats , boat_copy);


}