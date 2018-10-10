/*************************************************************************
	> File Name: ls4_1.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月22日 星期六 19时07分39秒
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
#include <cmath>
using namespace std;



////////////////////////////////////////////////////////////////////////////////////////////////////////
//Macro definition

#define NONE                 "\e[0m"
#define BLACK                "\e[0;30m"
#define L_BLACK              "\e[1;30m"
#define RED                  "\e[0;31m"
#define L_RED                "\e[1;31m"
#define GREEN                "\e[0;32m"
#define L_GREEN              "\e[1;32m"
#define BROWN                "\e[0;33m"
#define YELLOW               "\e[1;33m"
#define BLUE                 "\e[0;34m"
#define L_BLUE               "\e[1;34m"
#define PURPLE               "\e[0;35m"
#define L_PURPLE             "\e[1;35m"
#define CYAN                 "\e[0;36m"
#define L_CYAN               "\e[1;36m"
#define GRAY                 "\e[0;37m"
#define WHITE                "\e[1;37m"

#define BOLD                 "\e[1m"
#define UNDERLINE            "\e[4m"
#define BLINK                "\e[5m"
#define REVERSE              "\e[7m"
#define HIDE                 "\e[8m"
#define CLEAR                "\e[2J"
#define CLRLINE              "\r\e[K" //or "\e[1K\r"


#define maxn 1000
#define chlen 255
#define qu  11
//end///////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////
//Structure declaration
typedef struct Node{
    char name[chlen];
    //char pwdname[maxn];
    char jur[qu];
    int nlink;
    long  size;
    char ctim[chlen];
    struct stat filestat;
    char uidname[chlen];
    char gidname[chlen];

}Node;

typedef struct forlen0{
    int uid;
    int gid;
    int links;
}forlen0;

//end///////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function declaration

//Function0
//main
//参数处理

//Function1
//init
//全局变量初始化
void init();

//Function2
//do_ls
//得到每个文件的名字 和当前目录文件总数　完成后续操作
void do_ls(char *);

//Function3
//dostat
//得到每个文件的具体信息
void dostat(char *, int);

//Function4
//show_stat_info
//将信息输入进去　和字符转化 统计对齐格式　
void show_stat_info(int,struct stat*);

//Function5
//mod_to_letters
//将权限转化为字符串
void mod_to_letters(int, char *);

//Function6
//uid_to_name
//将uid转化成对应的名字　获取对齐长度
void uid_to_name(int,uid_t);

//Function7
//gid_to_name
//将gid转化成对应的名字　获取对齐长度
void gid_to_name(int,gid_t);

//Function8
//print1
//普通输出
void print1(int);

//Function9
//print2
//长格式输出
void print2(int);

//end///////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////
//Global variable declaration
Node files[maxn];
forlen0 forlen;
int op = 0;//00 la
int total;
//end///////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////
//正文

int main(int ac,char *av[]){
    init();
    int opp = 0, i = 2; //00 la

    *(++av);
    for(i = 2; i <= ac && (*av)[0] == '-'; *(++av),i++){
         strlen(*av) == 2 && (*av)[1] =='a'&& (opp |=1,1)||(*av)[1] == 'l' && (opp |= 2,1);
         strlen(*av) == 3 && ((*av)[1] == 'a' && (*av)[2] == 'l' ||
                              (*av)[1] == 'l' && (*av)[2] == 'a') && (opp |= 3,1);
    }

    op = opp;

    if (i > ac) {                        //默认文件夹
        do_ls(".");
    } else if (i == ac) {                //指定一个文件夹
        do_ls(*av);
    }
    else {
        while(i <= ac){                 //指定多个文件夹
            printf("%s:\n", *av);
            do_ls(*av);

            *(++av);
            i++;
            printf("\n");
            init();
        }

    }
    return 0;
}


void init(){
    memset(files,0,sizeof(Node)*maxn);
    forlen.uid = 0;
    forlen.gid = 0;
    forlen.links = 0;
    total = 0;
}


//Function2
//get_filename
//得到每个文件的名字 和当前目录文件总数　完成后续操作
int comp(const void *a, const void *b){
    return strcmp((*(Node*)a).name, (*(Node*)b).name);
}

void  do_ls(char *dirname){
    DIR *dir_ptr;
    struct dirent *direntp;
    struct stat dir;
    int tn = 0;
    

    if ((dir_ptr = opendir(dirname)) == NULL) {
        fprintf(stderr, "ls5:connot open %s\n", dirname);
    } else {
       
        while((direntp = readdir(dir_ptr)) != NULL){
            if(op & 1){//1
                strcpy(files[tn].name,direntp->d_name);
                tn++;
            }else{
                if(direntp->d_name[0] == '.') continue;
                strcpy(files[tn].name,direntp->d_name);
                tn++;
            }
        }
        
    }

    qsort(files,tn,sizeof(files[0]),comp);
    for(int i = 0; i < tn; i++) dostat(dirname, i);
    
    if(op & 2) print2(tn);
    else print1(tn);
    
}


//Function3
//dostat
//得到每个文件的具体信息
void dostat(char *dirname,int i){
    struct stat info;
    char pwdname[1000];
    
    strcpy(pwdname,dirname);
    if(strcmp(dirname,".") == 0){
        strcpy(pwdname,files[i].name);
    } else if (strcmp(dirname,"/") == 0){
        strcat(pwdname,files[i].name);
    } else {
        strcat(strcat(pwdname,"/"), files[i].name);
    }
    //strcpy(files[i].pwdname,pwdname);

    if(stat(pwdname, &info) == -1){
        perror(files[i].name);
    } else {
        show_stat_info(i,&info);
    }    
}


//Function4
//show_stat_info
//将信息输入进去　和字符转化 统计对齐格式　
void show_stat_info(int i,struct stat* info_p){
    forlen.links = forlen.links < log10((int)info_p->st_nlink) ? log10((int)info_p->st_nlink) : forlen.links;
    files[i].nlink = (int)info_p->st_nlink;
    files[i].size = (long)info_p->st_size;
    strcpy(files[i].ctim, 4 + ctime(&info_p->st_mtime));
    mod_to_letters(info_p->st_mode, files[i].jur);
    uid_to_name(i,info_p->st_uid);
    gid_to_name(i,info_p->st_gid);
    total += info_p->st_blocks/2;
}


//Function5 
//mod_to_letters:
//将权限转化为字符串
void mod_to_letters(int mode, char *str){
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


//Function6
//uid_to_name
//将uid转化成对应的名字　获取对齐长度
void uid_to_name(int i,uid_t uid){
    struct passwd *pw_ptr;
    static char numstr[10]; 

    if((pw_ptr = getpwuid(uid)) == NULL){
        sprintf(numstr,"%d", uid);

        strcpy(files[i].uidname, numstr);
        forlen.uid = forlen.uid < strlen(numstr) ? strlen(numstr):forlen.uid;
    }else{
        strcpy(files[i].uidname, pw_ptr->pw_name);
        forlen.uid = forlen.uid < strlen(pw_ptr->pw_name) ? strlen(pw_ptr->pw_name):forlen.uid;
    }
    return ;
}


//Function7
//gid_to_name
//将gid转化成对应的名字　获取对齐长度
void gid_to_name(int i, gid_t gid){
    struct group *grp_ptr;
    static char numstr[10]; 

    if((grp_ptr = getgrgid(gid)) == NULL){
        sprintf(numstr,"%d", gid);

        strcpy(files[i].gidname, numstr);
        forlen.gid = forlen.gid < strlen(numstr) ? strlen(numstr):forlen.gid;
    }else{
        strcpy(files[i].gidname, grp_ptr->gr_name);
        forlen.gid = forlen.gid < strlen(grp_ptr->gr_name) ? strlen(grp_ptr->gr_name):forlen.gid;
    }

    return ;
}


//Function8 
//print1
//普通输出
void print1(int tn){
    for(int i = 0; i< tn; i++){
        if (files[i].jur[0] == 'd')
            printf(YELLOW "%s  " NONE, files[i].name);
        else if (files[i].jur[0] == 'c')
            printf(RED "%s  " NONE, files[i].name);
        else if (files[i].jur[0] == 'b')
            printf(CYAN "%s  " NONE, files[i].name);
        else if (files[i].jur[3] == 'x'||files[i].jur[6] == 'x'|| files[i].jur[9])
            printf(L_BLUE "%s  " NONE,files[i].name);
        else if (files[i].jur[0] == '-')
            printf(BLUE "%s  " NONE, files[i].name);
    }
    printf("\n");
}


//Function9
//print2
//长格式输出
void print2(int tn){
    printf("total: %d\n",total);
    for(int i = 0; i< tn; i++){
        
        printf("%s ", files[i].jur);
        printf("%-*d ", forlen.links+1,files[i].nlink);
        printf("%-*s ", forlen.uid+1, files[i].uidname);
        printf("%-*s ", forlen.gid+1, files[i].gidname);
        printf("%8ld ", files[i].size);
        printf("%.12s ", files[i].ctim);        

        if (files[i].jur[0] == 'd')
            printf(YELLOW "%s\n" NONE, files[i].name);
        else if (files[i].jur[0] == 'c')
            printf(RED "%s\n" NONE, files[i].name);
        else if (files[i].jur[0] == 'b')
            printf(CYAN "%s\n" NONE, files[i].name);
        else if (files[i].jur[3] == 'x'||files[i].jur[6] == 'x'|| files[i].jur[9])
            printf(L_BLUE "%s\n" NONE,files[i].name);
        else if (files[i].jur[0] == '-')
            printf(BLUE "%s\n" NONE, files[i].name);
    }
}
//end/////////////////////////////////////////////////////////////////////////////////////////




