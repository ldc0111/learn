/*************************************************************************
	> File Name: master.h
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年11月14日 星期三 15时51分44秒
 ************************************************************************/

#ifndef _MASTER_H
#define pot 3
typedef struct master{
    int fd_server[pot];//门卫套接字
    int listen_port[pot];//收节点监听端口,数据传送端口　紧急端口
    socklen_t len_addr_client;
    int client_port;
    char *path;//文件存储路径
    char *prename;//开始ｉｐ
    int  start;
    int finish;
    struct sockaddr_in addr_server[3];
}MASTER;

void init(MASTER *);
int get_conf_value(char *, char *, char *);
int start_listen(int *, struct sockaddr_in *, int);
#define _MASTER_H
#endif
