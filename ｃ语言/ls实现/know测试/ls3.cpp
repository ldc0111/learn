/*************************************************************************
	> File Name: ls2.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月21日 星期五 19时44分01秒
 ************************************************************************/

#include<iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
using namespace std;

void do_ls(char [], int);
void print(char *ch);
void dostat(char *,char *);



int main(int ac,char *av[]){
    int temp = 0,i = 2; //00 低位是ａ，高位是ｌ
    *(++av);
    for(i = 2; i <= ac && (*av)[0] == '-'; *(++av),i++){
         strlen(*av) == 2 && (*av)[1] =='a'&& (temp |=1,1)||(*av)[1] == 'l' && (temp |= 2,1);
         strlen(*av) == 3 && ((*av)[1] == 'a' && (*av)[2] == 'l' ||
                              (*av)[1] == 'l' && (*av)[2] == 'a') && (temp |= 3,1);
    }
    if (i > ac) {
        do_ls(".",temp);
    }else if (i == ac) {
        do_ls(*av,temp);
    }
    else{
        while(i <= ac){
            printf("%s:\n",*av);
            do_ls(*av,temp);
            *(++av);
            i++;
        }
    }
    return 0;
}


int comp(const void *a, const void *b){
    return strcmp((char *)a, (char *)b);
}


void do_ls(char *dirname, int gon){
    DIR *dir_ptr;
    struct dirent *direntp;
    char name[1000][255];
    int tn = 0;
    
    if ((dir_ptr = opendir(dirname)) == NULL) {
        fprintf(stderr, "ls3:connot open %s\n", dirname);
    } else {
       
        while((direntp = readdir(dir_ptr)) != NULL){
            if(gon & 1){//1
                strcpy(name[tn],direntp->d_name);
                tn++;
            }else{
                if(direntp->d_name[0] == '.') continue;
                strcpy(name[tn],direntp->d_name);
                tn++;
            }
        }
        
    }
    qsort(name,tn,sizeof(name[0]),comp);
    for(int i = 0; i < tn; i++){
        if(gon & 2){
            dostat(name[i],dirname);
        }
        else{
            print(name[i]);
        }
    }
}

