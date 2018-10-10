/*************************************************************************
	> File Name: ls1.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月21日 星期五 19时17分38秒
 ************************************************************************/

#include<iostream>
#include <stdio.h>
#include <dirent.h>
//#include <sys/types.h>

void do_ls(char []);

int main(int ac,char * av[]){
    if (ac == 1) {
        do_ls(".");
    } else {
        while (--ac) {
            //printf("%s:\n", *(++av));
            ++av;
            do_ls(*av);
        }
    }
    return 0;
}
void do_ls(char dirname[]){
    DIR *dir_ptr;
    struct dirent  *direntp;
    if ((dir_ptr = opendir(dirname)) == NULL) {
        fprintf(stderr, "ls1 cannot open %s\n",dirname);
    } else {
        while ((direntp = readdir(dir_ptr)) != NULL)
            printf("%s   ", direntp->d_name);
        printf("\n");
        closedir(dir_ptr);
    }
}
