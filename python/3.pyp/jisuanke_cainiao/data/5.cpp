#include <stdio.h>

int main(){
    int y,m,d;
    scanf("%d-%d-%d",&y,&m,&d);
    if(m > 12||d > 31){
        printf("NO");
    }else if((m == 4||m == 6|| m == 9|| m == 11)&& d > 30){
        printf("NO");
    }else if(m == 2 &&!(y% 100 != 0 && y %4 == 0||y %400 == 0)&& d > 28){
         printf("NO");   
    }else if((m == 2)&&((y % 100!= 0 && y%4 == 0)||(y %400 == 0)) && d > 29){
            printf("NO");
    }else{
        printf("YES");
    }
    
    return 0;
}