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

#define BROWN                "\e[0;33m"
#define NONE                 "\e[0m"
#define BLUE                 "\e[0;34m"

void do_ls(char [], int);
void print(char *ch);
void dostat(char *,char *,int);
void show_stat_info(char *fname, struct stat *buf,int gon);
void mode_to_letters(int mode, char str[]);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

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
    struct stat dir;
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
        dostat(name[i],dirname,gon);
    }
    printf("\n");
}
void dostat( char *filename ,char dirname[],int gon){
    struct stat info;
    char pwdname[1000];
    
    strcpy(pwdname,dirname);
    if(strcmp(dirname,".") == 0){
        strcpy(pwdname,filename);
    } else if (strcmp(dirname,"/") == 0){
        strcat(pwdname,filename);
    } else {
        strcat(strcat(pwdname,"/"), filename);
    }
    

    if(stat(pwdname, &info) == -1){
        perror(filename);
    } else {
        show_stat_info(filename, &info,gon);
    }
}

void show_stat_info(char *filename, struct stat *info_p,int gon){
    char modestr[11];

    mode_to_letters(info_p->st_mode, modestr);
    if(gon & 2){
        printf("%s", modestr);
        printf("%4d ", (int)info_p->st_nlink);
        printf("%-8s ", uid_to_name(info_p->st_uid));
        printf("%-8s ", gid_to_name(info_p->st_gid));
        printf("%8ld ", (long) info_p->st_size);
        printf("%.12s ", 4 + ctime(&info_p->st_mtime));

        if (modestr[0] == 'd') printf(BROWN "%s\n" NONE, filename);
        else if(modestr[0] == '-') printf(BLUE "%s\n" NONE, filename);


    }else{
        if (modestr[0] == 'd') printf(BROWN "%s " NONE, filename);
        else if(modestr[0] == '-') printf(BLUE "%s " NONE, filename);

    }

}
void mode_to_letters(int mode, char str[]){
    strcpy(str,"----------");

    if (S_ISDIR(mode)) str[0] = 'd';
    if (S_ISCHR(mode)) str[0] = 'c';
    if (S_ISBLK(mode)) str[0] = 'b';

    if (mode & S_IRUSR) str[1] = 'r';
    if (mode & S_IWUSR) str[2] = 'w';
    if (mode & S_IXUSR) str[3] = 'x';

    if (mode & S_IRGRP) str[4] = 'r';
    if (mode & S_IWGRP) str[5] = 'w';
    if (mode & S_IXGRP) str[6] = 'x';

    if (mode & S_IROTH) str[7] = 'r';
    if (mode & S_IWOTH) str[8] = 'w';
    if (mode & S_IXOTH) str[9] = 'x';

}

char* uid_to_name(uid_t uid){
    struct passwd *pw_ptr;
    static char numstr[10];

    if ((pw_ptr = getpwuid(uid)) == NULL){
        sprintf(numstr,"%d", uid);
        return numstr;
    }else{
        return pw_ptr->pw_name;
    }
}
char* gid_to_name(gid_t gid){
    struct group *grp_ptr;
    static char numstr[10];
    
    if((grp_ptr = getgrgid(gid)) == NULL){
        sprintf(numstr,"%d", gid);
        return numstr;
    }else{
        return grp_ptr->gr_name;
    }
}

