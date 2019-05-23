/*************************************************************************
	> File Name: read_conf.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月30日 星期日 10时20分26秒
 ************************************************************************/

#include "../common/common.h"


int get_conf_value(char *pathname,char *key_name,char *value){
    char *line;
    size_t len= 0;
    ssize_t read;
    FILE *fp = NULL;
    fp = fopen(pathname,"r");
    if (fp == NULL) {
        perror("fopen:");
        return -1;
    }

    while ((read = getline(&line,&len,fp)) > 0) {
        //printf("%s", line);
        char *ptr = strstr(line,key_name);
        if (ptr == NULL) continue;
        ptr += strlen(key_name);
        if (*ptr != '=') continue;
        strncpy(value, (ptr+1), strlen(ptr+2));//strlen(per+2) 少获取一个长度，代表换行
        int tempvalue = strlen(value);
        value[tempvalue] = '\0';

        printf("strlen(ptr+1):%d %s", strlen(ptr+1),ptr+1);
    }  
    printf("strlen: %d, %s",strlen(value), value);
    printf("------");
    return 0;
}

int main(){
    char bufer[max_size];
    memset(bufer, 0, sizeof(bufer));
    get_conf_value("../common//pihealthd.conf", "start", bufer);
    return 0;
}
