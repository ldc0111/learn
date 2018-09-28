/*************************************************************************
	> File Name: client.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月27日 星期四 20时45分26秒
 ************************************************************************/

#include "head.h"




void transport(char * ch,int fd_client){
    FILE *fp = popen(ch,"r");
    char buffer[max_size];
    Node te;
    if (strcmp(ch, "./cpu.sh") == 0) buffer[0] = 'c';
    else if (strcmp(ch, "./disk.sh") == 0) buffer[0] = 'd';
    else if (strcmp(ch, "./mem.sh") == 0) buffer[0] = 'm';
    while(!feof(fp)){
        memset(buffer + 1, 0,sizeof(buffer) - 1);
        fread(buffer + 1,sizeof(char), max_size,fp);
        send(fd_client,buffer,max_size,0);
        printf(" %s ", buffer);

    }
    printf("\n\n\n");
    pclose(fp);
}


int main(int argc,char *argv[]){
    int fd_client;
    int size = 0;
    char buffer[1000];
    struct sockaddr_in dest_addr;
    int port = atoi(argv[2]);
    char *host = argv[1];

    if ((fd_client = socket(AF_INET,SOCK_STREAM,0)) < 0){
        perror("socket");
        return -1;
    }
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(host);
    if (connect(fd_client, (struct sockaddr *)&dest_addr,sizeof(dest_addr)) < 0){
        perror("connect");
        return -1;
    }
    
    if(!fork()){
        transport("./cpu.sh",fd_client);
        exit(0);
    }
    if(!fork()){
        transport("./disk.sh", fd_client);
        exit(0);
    }
    if(!fork()){
        transport("./mem.sh", fd_client);
        exit(0);
    }

    return 0;
}
