/*************************************************************************
	> File Name: client.h
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年11月17日 星期六 16时32分52秒
 ************************************************************************/

#ifndef _CLIENT_H
#define scri 6
typedef struct Node_client{
    int fd_client;//心跳套接字
    int fd_listen;//监听套接字
    int master_port;//ｍａｓｔｅｒ链接监听端口
    int client_port;//ｃｌｉｅｎｔ端监听端口
    int urgent_port;//ｍａｓｔｅｒ紧急端口
    socklen_t len_addr_client;//存储ｓｔｒｕｃｔ　ｓｏｃｋａｄｄｒ——ｉｎ的长度
    char *datadir;//文件存储目录
    char *master_host;//ｍａｓｔｅｒ端ｈｏｓｔ
    char *zippath;//压缩文件名
    struct sockaddr_in dest_addr;//心跳套接字结构体
    struct sockaddr_in listen_addr;//监听套接字结构体
}Node_client;
#define _CLIENT_H
#endif
