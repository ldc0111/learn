/*************************************************************************
> File Name: server.cpp
> Author: ldc
> Mail: litesla
> Created Time: 2018年09月27日 星期四 18时43分27秒
************************************************************************/

#include "head.h"


int  listenn(int *fd_server, struct sockaddr_in *addr_server,int listen_port){
    addr_server->sin_family = AF_INET;
    addr_server->sin_port = htons(listen_port);
    addr_server->sin_addr.s_addr = htonl(INADDR_ANY);

    if ((*fd_server = socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("socket: ");
        return -1;
    }
    if (bind(*fd_server, (struct sockaddr *)addr_server, sizeof(*addr_server)) < 0){
        perror("bind: ");
        return -1;
    }
    if (listen(*fd_server,BACKLOG) < 0) {
        perror("listen: ");
        return -1;
    }

}


int recvfile(int fd_server,struct sockaddr_in addr_client, socklen_t len_addr_client){
    int fd_client;
    if ((fd_client = accept(fd_server,(struct sockaddr *)&addr_client, &len_addr_client)) < 0){
        perror("accept:");
        return -1;
    }

    if (!fork()) {
        char buffer[max_size] = PATH;
        strcat(buffer,inet_ntoa(addr_client.sin_addr));
        mkdir(buffer,0775);
        int size = 0;
        
        char ic[max_size];
        strncpy(ic,buffer,strlen(buffer));
        strcat(ic,"/cpu.log");
        char id[max_size];
        strncpy(id,buffer,strlen(buffer));
        strcat(id,"/disk.log");
        char im[max_size];
        strncpy(im,buffer,strlen(buffer));
        strcat(im,"/mem.log");
        FILE *fc = fopen(ic,"a+");
        FILE *fd = fopen(id,"a+");
        FILE *fm = fopen(im,"a+");

        while(1){
            memset(buffer,0,sizeof(buffer));
            size = recv(fd_client,buffer, max_size,0);
            if(size <= 0) break;
            buffer[size] = '\0';
            //printf("%c ",buffer[0]);
            //printf("%s", buffer+1);
            if (buffer[0] == 'c') {
                fwrite(buffer+1, strlen(buffer) - 1, sizeof(buffer[0]), fc);
            } else if (buffer[0] == 'd') {
                fwrite(buffer+1, strlen(buffer) - 1, sizeof(buffer[0]), fd);
            } else if (buffer[0] == 'm'){
                fwrite(buffer+1, strlen(buffer) - 1, sizeof(buffer[0]), fm);
            }
        }
        close(fd_client);
        exit(0);

    }
}
void init(struct Node_server *server, char *argv[]){
    server->listen_port = atoi(argv[1]);
    server->addr_server;
    server->len_addr_client = sizeof(struct sockaddr_in);
    if (listenn(&(server->fd_server), &(server->addr_server),server->listen_port) < 0){
        printf("listenn is error!");
        return ;
    }
}



int main(int argc, char *argv[]){
    struct Node_server server;
    struct sockaddr_in addr_client;

    init(&server, argv);

    while(1){
        recvfile(server.fd_server, addr_client, server.len_addr_client);
    }
    close(server.fd_server);
    return 0;
}

