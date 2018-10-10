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
using namespace std;

void do_ls(char []);
void dostat(char *,char *);
void show_stat_info(char *fname, struct stat *buf);
void mode_to_letters(int mode, char str[]);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);



int main(int ac, char *av[]){
    if (ac == 1) {
        do_ls(".");
    } else {
        while(--ac){
            //printf("%s:\n", *(++av));
            av++;
            do_ls( *av );
        }
    }
    return 0;
}
void do_ls(char dirname[]){
    DIR *dir_ptr;
    struct dirent * direntp;
    if ((dir_ptr = opendir(dirname)) == NULL){
        fprintf(stderr, "ls22:connot open %s\n", dirname);
    } else {
        while (( direntp = readdir(dir_ptr)) != NULL){
            dostat(direntp->d_name,dirname);
        }
        closedir(dir_ptr);
    }
}

void dostat( char *filename ,char dirname[]){
    struct stat info;
    char pwdname[1000];
    //memset(pwdname,0,sizeof(pwdname));
    strcpy(pwdname,dirname);
    if(strcmp(dirname,".") == 0){
        strcpy(pwdname,filename);
    } else if (strcmp(dirname,"/") == 0){
        strcat(pwdname,filename);
    } else {
        strcat(strcat(pwdname,"/"), filename);

    }
    //printf("dirname:%s\n filename:%s\n",dirname,filename);
    if(stat(pwdname, &info) == -1){
        perror(filename);
    } else {
        show_stat_info(filename, &info);
    }
}

void show_stat_info(char *filename, struct stat *info_p){
    //char *uid_to_name(), *gid_to_name(), *filemode();
    //void mode_to_letters();
    char modestr[11];

    mode_to_letters(info_p->st_mode, modestr);

    printf("%s", modestr);
    printf("%4d ", (int)info_p->st_nlink);
    printf("%-8s ", uid_to_name(info_p->st_uid));
    printf("%-8s ", gid_to_name(info_p->st_gid));
    printf("%8ld ", (long) info_p->st_size);
    printf("%.12s ", 4 + ctime(&info_p->st_mtime));
    printf("%-4d", info_p->st_blocks/2);
    printf("%s\n", filename);

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
    //struct passwd * getpwuid(), *pw_ptr;
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
    //struct group *getgrgid(), *grp_ptr;
    struct group *grp_ptr;
    static char numstr[10];
    
    if((grp_ptr = getgrgid(gid)) == NULL){
        sprintf(numstr,"%d", gid);
        return numstr;
    }else{
        return grp_ptr->gr_name;
    }
}
