#include <stdio.h>
#include <string.h>
int main() {
    char name[11][20];
    
    for (int i = 1; i <= 10; i++){
        scanf("%s", name[i]);
    }
    for (int i = 1; i < 10; i++){
        for(int j = 1; j < 10 - i + 1; j++){
            if(strcmp(name[j], name[j + 1]) > 0){
                strcpy(name[0],name[j]);
                strcpy(name[j],name[j + 1]);
                strcpy(name[j + 1], name[0]);
            }
        }
    }
    for(int i = 1; i <= 10; i++){
        printf("%s\n",name[i]);
    }
    return 0;
}