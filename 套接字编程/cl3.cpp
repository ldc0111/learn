/*************************************************************************
	> File Name: cl3.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月25日 星期二 18时26分18秒
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
#include <string.h>

#define maxnbuf 1000

int main(int av,char *argv[]){
    int fd_client;
    int size = 0;
    char buffer[1000];
    struct sockaddr_in dest_addr;
    int port = atoi(argv[2]);
    char *host = argv[1];
    FILE *fp = fopen("./cl3.cpp","r");

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
    while (!feof(fp)) {
        fread(buffer,1,maxnbuf,fp);
        //printf("%s",buffer);
        size = send(fd_client,buffer,maxnbuf, 0);
        memset(buffer,0,sizeof(buffer));
    }
    close(fd_client);
    return 0;
}
//李得草





