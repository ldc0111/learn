/*************************************************************************
> File Name: master.cpp
> Author: ldc
> Mail: litesla
> Created Time: 2018年11月13日 星期二 20时05分41秒
************************************************************************/
#include "../common/common.h"
#include "./master.h" 



//读取配置文件，读取一个健值，结果在ｖａｌｕｅ数组中
int get_conf_value(char *pathname, char *key_name, char *value){
    char *line;
    size_t len= 0;
    ssize_t read;
    FILE *fp = NULL;
    fp = fopen(pathname, "r");
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
        //printf("strlen(ptr+1):%d %s", strlen(ptr+1),ptr+1);
    }  
    //printf("strlen: %d, %s",strlen(value), value);
    //printf("------");
    return 0;
}
//////////////////////////////////////////////////////////////////////////

//初始化ｍａｓｔ结构体 开放端口，存储总路径
void init(MASTER *mast){
    char temp[max_size];
    mast->path = (char *)malloc(sizeof(char) * max_size);
    get_conf_value("./mast.conf", "PATH", mast->path);
    get_conf_value("./mast.conf", "PORT", temp);
    mast->listen_port = atoi(temp);
    return ;
}
/////////////////////////////////////////////////////////////////////////////

int start_listen(int *fd_server, struct sockaddr_in *addr_server, int listen_port){
    addr_server->sin_family = AF_INET;
    addr_server->sin_port = htons(listen_port);
    addr_server->sin_addr.s_addr = htonl(INADDR_ANY);

    if ((*fd_server = socket(AF_INET, SOCK_STREAM,0)) < 0) {
        perror("socket: ");
        return -1;
    }
    if (bind(*fd_server, (struct sockaddr *)addr_server, sizeof(*addr_server)) < 0){
        perror("bind: ");
        return -1;
    }
    if (listen(*fd_server, BACKLOG) < 0) {
        perror("listen: ");
        return -1;
    }   
}




int main(){
    MASTER mast;
    init(&mast);
    //printf("%s\n",mast.path);
    printf("%d\n",mast.listen_port);
    if(start_listen(&(mast.fd_server), &(mast.addr_server), mast.listen_port) < 0 ){
        perror("start_listen is error!");
        return  -1;
    }
    while(1){
        
    }
    return 0;
}

