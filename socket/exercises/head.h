/*************************************************************************
	> File Name: head.h
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月27日 星期四 18时41分33秒
 ************************************************************************/

#ifndef _HEAD_H
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
#include <sys/stat.h>

#define max_size 1024
#define BACKLOG 10
#define PATH "./"

struct Node_client{
    int fd_client;
    int port;
    char *host;
    struct sockaddr_in dest_addr;
};
struct Node_server{
    int fd_server;
    int listen_port;
    socklen_t len_addr_client;
    struct sockaddr_in addr_server;
};


#define _HEAD_H
#endif
