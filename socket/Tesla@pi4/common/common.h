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
#include <pthread.h>
#define max_size 1024
#define BACKLOG 10 
#define _HEAD_H
#endif

#ifdef DBG
#define DBG(fmt,args...) printf(fmt,##args)
#else
#define DBG(fmt,args...)
#endif
