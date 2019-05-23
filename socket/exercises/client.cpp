/*************************************************************************
	> File Name: client.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月27日 星期四 20时45分26秒
 ************************************************************************/

#include "head.h"

void transport(const char * ch,int fd_client){
    printf("fd_client %d\n", fd_client);
    FILE *fp = popen(ch,"r");
    char buffer[max_size];

    if (strcmp(ch, "./cpu.sh") == 0) buffer[0] = 'c';
    else if (strcmp(ch, "./disk.sh") == 0) buffer[0] = 'd';
    else if (strcmp(ch, "./mem.sh") == 0) buffer[0] = 'm';
    
    while(!feof(fp)){
        memset(buffer + 1, 0,sizeof(buffer) - 1);
        fread(buffer + 1,sizeof(char), max_size,fp);
        send(fd_client,buffer,max_size,0);
        printf("%s", buffer);
    }
    pclose(fp);
}

void forkk(int fd_client){
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
    return;
}
int init(struct Node_client *client,char *argv[]){
    client->port = atoi(argv[2]);
    client->host = argv[1];

    if ((client->fd_client = socket(AF_INET,SOCK_STREAM,0)) < 0){
        perror("socket");
        return -1;
    }
    client->dest_addr.sin_family = AF_INET;
    client->dest_addr.sin_port = htons(client->port);
    client->dest_addr.sin_addr.s_addr = inet_addr(client->host);
    if (connect(client->fd_client, (struct sockaddr *)&(client->dest_addr),sizeof(client->dest_addr)) < 0){
        perror("connect");
        return -1;
    }
}

int main(int argc,char *argv[]){
    struct Node_client client;
    init(&client,argv);
    while(1){
        forkk(client.fd_client);
        sleep(5);
    }
    return 0;
}
