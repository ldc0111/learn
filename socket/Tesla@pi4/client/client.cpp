/*************************************************************************
> File Name: client.cpp
> Author: ldc
> Mail: litesla
> Created Time: 2018年11月17日 星期六 16时31分54秒
************************************************************************/
#include "../common/common.h"
#include "client.h"


void* func1(void *);
void* func2(void *);
void* func3(void *);
/////////////////////////////////////
typedef struct scripest{
    char *name;
    char *path;
    char *mepath;
    int ti,index;
}scripe;
scripe sc[scri];

Node_client client;
pthread_mutex_t g_mutex[scri];

/////////////////////////////////////////////////////////
//读取配置文件，读取一个健值，结果在ｖａｌｕｅ数组中
char * get_conf_value(const char *pathname, const char *key_name){
    char *line;
    size_t len = 0;
    ssize_t read;
    char *value = (char *)calloc(sizeof(char), max_size);
    FILE *fp = NULL;
    fp = fopen(pathname, "r");
    if (fp == NULL) {
        perror("fopen:");
        return NULL;
    }

    while ((read = getline(&line,&len,fp)) > 0) {
        //printf("%s", line);
        char *ptr = strstr(line,key_name);
        if (ptr == NULL) continue;
        ptr += strlen(key_name);
        if (*ptr != '=') continue;
        strncpy(value, (ptr+1), strlen(ptr+2));//strlen(per+2) 少获取一个长度，代表换行
        int tempvalue = strlen(value);
        value[tempvalue] = '\0';
        //printf("strlen(ptr+1):%d %s", strlen(ptr+1),ptr+1);
    }  
    //printf("strlen: %d, %s",strlen(value), value);
    //printf("------");
    return value;
}


int init(Node_client *client){
    client->master_port = atoi(get_conf_value("../common/pihealthd.conf", "master_port"));
    client->master_host = get_conf_value("../common/pihealthd.conf", "master_host");
    client->client_port = atoi(get_conf_value("../common/pihealthd.conf", "client_port"));
    client->datadir = get_conf_value("./client.conf","datadir");
    client->zippath = get_conf_value("./client.conf","zippath");
    client->len_addr_client = sizeof(struct sockaddr_in);
}

int heart(Node_client * client){
    if ((client->fd_client = socket(AF_INET,SOCK_STREAM,0)) < 0){
    perror("socket");
    return -1;
    }
    
    client->dest_addr.sin_family = AF_INET;
    client->dest_addr.sin_port = htons(client->master_port);
    client->dest_addr.sin_addr.s_addr = inet_addr(client->master_host);
    if (connect(client->fd_client, (struct sockaddr *)&(client->dest_addr),sizeof(client->dest_addr)) < 0){
    printf("%d",__LINE__);
    perror("connect");
    close(client->fd_client);
    return -1;
    }
    //ｍａｓｔｅｒ处理方案是，如果有这个节点的信息就不插入，如果没有就进行插入，会构建链接，
    //因为目的只是让ｍａｓｔｅｒ存储信息所以可以直接进行关闭
    close(client->fd_client);
    return 0; 
}


int init_scripe(scripe *sc){
    sc[0].name = get_conf_value("./client.conf", "name0");
    sc[0].path = get_conf_value("./client.conf", sc[0].name);
    sc[0].ti = atoi(get_conf_value("./client.conf", "time0"));
    sc[0].mepath = get_conf_value("./client.conf", "mepath0");
    sc[0].index = 0;

    sc[1].name = get_conf_value("./client.conf", "name1");
    sc[1].path = get_conf_value("./client.conf", sc[1].name);
    sc[1].ti = atoi(get_conf_value("./client.conf", "time1"));
    sc[1].mepath = get_conf_value("./client.conf", "mepath1");
    sc[1].index = 1;

    sc[2].name = get_conf_value("./client.conf", "name2");
    sc[2].path = get_conf_value("./client.conf", sc[2].name);
    sc[2].ti = atoi(get_conf_value("./client.conf", "time2"));
    sc[2].mepath = get_conf_value("./client.conf", "mepath2");
    sc[2].index = 2;

    sc[3].name = get_conf_value("./client.conf", "name3");
    sc[3].path = get_conf_value("./client.conf", sc[3].name);
    sc[3].ti = atoi(get_conf_value("./client.conf", "time3"));
    sc[3].mepath = get_conf_value("./client.conf", "mepath3");
    sc[2].index = 2;

    sc[4].name = get_conf_value("./client.conf", "name4");
    sc[4].path = get_conf_value("./client.conf", sc[4].name);
    sc[4].ti = atoi(get_conf_value("./client.conf", "time4"));
    sc[4].mepath = get_conf_value("./client.conf", "mepath4");
    sc[4].index = 4;


    sc[5].name = get_conf_value("./client.conf", "name5");
    sc[5].path = get_conf_value("./client.conf", sc[5].name);
    sc[5].ti = atoi(get_conf_value("./client.conf", "time5"));
    sc[5].mepath = get_conf_value("./client.conf", "mepath5");
    sc[5].index = 5;
    //自检
    //for(int i = 0; i < scri; i++){    
    //    printf("%s\t%s\t%d\n", sc[i].name, sc[i].path, sc[i].ti);
    //}
    return 0;
}

void init_lock(pthread_mutex_t * g_mutex,int num){
    for(int i = 0; i < num; i++){
        pthread_mutex_init(&g_mutex[i],NULL);
    }
    return ;
}

int main(){
    pthread_t t[scri + 2];
    //初始化ｃｌｉｅｎｔ结构体
    init(&client);

    //初始化互斥锁
    init_lock(g_mutex, scri);
    //初始化脚本信息
    init_scripe(sc);
    //初始化监听端口 如果ｍａｓｔ链接进来就以次发送信息，
    //listen(&client);
    if(pthread_create(&(t[6]), NULL, func2,(void *)&client)== -1){
        printf("%d",__LINE__);
        perror("pthread_create_func2:  ");
        return -1;
    }
    
    //线程　检测文件大小，并压缩
    //此处缺一个函数
    if(pthread_create(&(t[7]), NULL, func3,(void *)NULL)== -1){
        printf("%d",__LINE__);
        perror("pthread_create_func3:  ");
        return -1;
    }

    //开启6个线程
    for(int i = 0; i < scri; i++){
        if(pthread_create(&(t[i]), NULL, func1, (void *)&sc[i]) == -1){
            printf("%d ",__LINE__);
            perror("pthread_create_func1:  ");
            return -1;
        }        
    }

    do{
        //心跳 主线程
        heart(&client);
        sleep(15);
    }while(1);

    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    pthread_join(t[2], NULL);
    pthread_join(t[3], NULL);
    pthread_join(t[4], NULL);
    pthread_join(t[5], NULL);
    pthread_join(t[6], NULL);
    pthread_join(t[7], NULL);
    return 0;
}

void* func1(void *arg){
    while(1){
        scripe *te=(scripe *)arg;
        FILE *fp=popen(te->path, "r");
        char buff[max_size];
        memset(buff, 0, sizeof(buff));
        char pathname[max_size];
        //判断文件夹是否存在
        if(access(client.datadir, F_OK) == -1){
            mkdir(client.datadir,0775);
        }
        strcpy(pathname, client.datadir);
        strcat(pathname, "/");
        strcat(pathname, te->mepath);
        FILE *fl=fopen(pathname,"a+");
        
        //运行一次
        fread(buff,sizeof(char),max_size,fp);
        //判断信息里面是否有警告
        //写一个函数


        //写入文件一次
        pthread_mutex_lock(&g_mutex[te->index]);
        fwrite(buff, strlen(buff), sizeof(buff[0]),fl);
        pthread_mutex_unlock(&g_mutex[te->index]);
        pclose(fp);
        fclose(fl);
        sleep(te->ti);
    }
    pthread_exit(NULL);
    return NULL;
}

void transport(int fd_temp, int index){
    char pathname[max_size];
    char buff[max_size + 1];
    buff[0] = index + '0';//标识码
    buff[1] = 0;
    //判断文件夹是否存在
    if(access(client.datadir, F_OK) == -1){
        return ;
    }
    strcpy(pathname, client.datadir);
    strcat(pathname, "/");
    strcat(pathname, sc[index].mepath);
    if(access(pathname, F_OK) == -1){
        return ;
    }

    FILE *fl=fopen(pathname,"r");
    if(fl == NULL){
        return ;
    }
    //发送标示码
    printf("%s", buff);
    send(fd_temp, buff, strlen(buff), 0);
    //发送文件
    while(!feof(fl)){
        memset(buff,0,sizeof(buff));
        fread(buff, sizeof(char), max_size,fl);
        send(fd_temp, buff, strlen(buff), 0);
    }
    //删除文件
    char command[50];
    //对６个文件加上互斥锁，放置信息写入
    sprintf(command, "rm %s", pathname);
    system(command);
}



//作用监听 传送文件
void* func2(void *arg){
    Node_client *client = (Node_client *)arg;
    client->listen_addr.sin_family = AF_INET;
    client->listen_addr.sin_port= htons(client->client_port);
    client->listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((client->fd_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("%d ", __LINE__);
        perror("socket:");
        return NULL;
    }
    if(bind(client->fd_listen, (struct sockaddr *)&client->listen_addr,sizeof(client->listen_addr)) < 0) {
        printf("%d", __LINE__);
        perror("bind :");
        return NULL;
    }
    //测试端口
    
    if(listen(client->fd_listen,BACKLOG) < 0) {
        printf("%d", __LINE__);
        printf("listen:");
        return NULL;
    }
    
    //显示那个ｈｏｓｔ连接了
    //等待链接　待续未完ｍａｓｔｅｒ会创建６次链接，并判断ｃｌｉｅｎｔ端是否在运行，，如果不在运行
    //就删除节点的信息，如果就会链接６次，每个文件进行一次传送
    for (int i = 0; i < 6; i = (i + 1)% 6){
        int fd_temp;
        if((fd_temp = accept(client->fd_listen, (struct sockaddr*)(&(client->listen_addr)), &(client->len_addr_client))) < 0) {
            printf("%d ",__LINE__);
            perror("accept:");
            return NULL;
        }
        printf("i %d, socket %d %s is connect\n", i, fd_temp, inet_ntoa(client->listen_addr.sin_addr));
        //查看是否压缩文件
        //有，解压，传送响应的压缩文件，

        //表示要传送那个脚本的信息
        pthread_mutex_lock(&g_mutex[i]);
        transport(fd_temp,i);
        pthread_mutex_unlock(&g_mutex[i]);

        close(fd_temp);
    }
    pthread_exit(NULL);
    return NULL;
}

int filesize(char *filename){
    struct stat statbuf;
    stat(filename, &statbuf);
    return statbuf.st_size;
}


//检测文件大小　压缩线程
void* func3(void *arg){
    while(1){
        int size = 0;
        for (int i = 0; i < scri; i++){
            char dirname[max_size];
            strcpy(dirname, client.datadir);
            strcat(dirname, "/");
            strcat(dirname, sc[i].mepath);
            size += filesize(dirname);
            //printf("%s\n",dirname);
        }
         
        if(size > 30 * 1024 * 1024){
        char command[50];
        //对６个文件加上互斥锁，放置信息写入
        for(int i = 0; i < scri; i++){
            pthread_mutex_lock(&g_mutex[i]);
        }
        sprintf(command, "zip -r %s %s", client.datadir, client.datadir);
        system(command);
        //删除源文件操作，还没有写

        //解锁，可以产生信的文件啦
        for(int i = 0; i < scri; i++){
            pthread_mutex_unlock(&g_mutex[i]);
        }
        }
        sleep(10000);
    }
    pthread_exit(NULL);
    return NULL;
}
