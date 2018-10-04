/*************************************************************************
	> File Name: haizei.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月04日 星期四 15时55分06秒
 ************************************************************************/

#include<iostream>
#include <string.h>
using namespace std;


#define filename "haizei"

#define user "USER=tesla"
int main(int argc, char *argv[], char **env){
    int flag = 0; 
    int len = strlen(argv[0]) - strlen(filename);
    char *p =  argv[0];
    printf("%s\n",argv[0]);
    printf("%s",p + len);
    if(strcmp((p + len),filename)!= 0) return -1;
    for(int i = 0; env[i] != NULL; i++){
        if(strcmp(env[i], user) == 0){
            flag = 1;
        }
    }
    if(flag == 0) return -1;
    printf("run is ok\n");
    return 0;
}
