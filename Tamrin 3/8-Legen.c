//403100043
#include <stdio.h>

int main() {
    int q, n ,m , a[110][110] ;
    scanf("%d %d",&n ,&m);
    for(int i=1 ;i <=n ; i++ ){
        for (int j =1; j<=m ; j++) scanf("%d", &a[i][j]);
    }
    
    scanf("%d", &q);
    for(int i= 0;i<q;i++) {
        int b[100100];
        for (int i = 0; i < 100100; i++)
        {
            b[i]=0;
        }
        
        int x_1,x_2,y_1,y_2,num=0;
        scanf("%d %d %d %d", &x_1, &y_1, &x_2, &y_2);
        for(int j=x_1;j<=x_2;j++){
            for(int k=y_1;k<=y_2;k++){
                if(b[a[j][k]]!= 1){
                    num++;
                    b[a[j][k]]=1;
                }
            }
        }
        printf("%d ", num);
    }
    
    
}