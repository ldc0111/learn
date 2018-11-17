/*************************************************************************
	> File Name: master.h
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年11月14日 星期三 15时51分44秒
 ************************************************************************/

#ifndef _MASTER_H
#define cache 10240
#define BACKLOG 20  
typedef struct master{
    int fd_server;
    int listen_port;
    socklen_t len_addr_client;
    char *path;
    struct sockaddr_in addr_server;
}MASTER;

void init(MASTER *);
int get_conf_value(char *, char *, char *);
int start_listen(int *, struct sockaddr_in *, int);
#define _MASTER_H
#endif
