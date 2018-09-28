/*************************************************************************
> File Name: sv2.cpp
> Author: ldc
> Mail: litesla
> Created Time: 2018年09月24日 星期一 09时54分28秒
************************************************************************/

/*************************************************************************
> File Name: sv.cpp
> Author: ldc
> Mail: litesla
> Created Time: 2018年09月23日 星期日 17时26分23秒
************************************************************************/

#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>

#define BACKLOG 10
#define BUFFER_SIZE 1024


int main(int argc,char *argv[]){
    if(2!= argc){
        perror("argc");
        return -1;
    }
    int fd_server;
    int listen_port = atoi(argv[1]);
    struct sockaddr_in addr_server;
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(listen_port);
    addr_server.sin_addr.s_addr = htonl(INADDR_ANY);

    if((fd_server = socket(AF_INET,SOCK_STREAM, 0)) < 0){
        perror("socket:");
        return -1;
    }
    if(bind(fd_server, (struct sockaddr *)&addr_server,sizeof(addr_server)) < 0){
        perror("bind:");
        return -1;
    }
    if(listen(fd_server, BACKLOG) < 0){
        perror("listen:");
        return -1;
    }
    struct sockaddr_in addr_c;
    socklen_t len_addr_client = sizeof(addr_c);
    //char peeraddr[BUFFER_SIZE];
    int fd_c;
    if ((fd_c = accept(fd_server, (struct sockaddr*)&addr_c, &len_addr_client)) < 0){
        perror("accept:");
        return -1;
    }
    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];
    int size = 0;
    pid_t pid = fork();
    if(pid  <=  0){
        while(1){
            size = recv(fd_c , buffer1, sizeof(buffer1),0);
            if(size <= 0) continue;
            buffer1[size] = '\0';
            printf("%s : ", inet_ntoa(addr_c.sin_addr));
            printf("%s\n", buffer1);
        }
        exit(0);
    }else{
        while(1){
            scanf("%[^\n]s",buffer2);
            getchar();
            size = send(fd_c,buffer2, strlen(buffer2), 0);
        }
    }
    close(fd_c);
    close(fd_server);


}



