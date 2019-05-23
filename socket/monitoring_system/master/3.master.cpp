/*************************************************************************
	> File Name: 3.master.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年12月08日 星期六 21时05分52秒
 ************************************************************************/
#include "../common/common.h"
#include "master.h"


#define INS 5
//同事链接几个客户端
#define min(a ,b) ((a) < (b) ? (a) : (b))
//取最小宏定义
#define hashsize 20000
//哈希表大小
#define scripe 6
//脚本数量


void* func(void *); 
void *func2(void *);
//一
//结构定义全局变量声明，对应结构体操作函数
pthread_mutex_t g_mutex[INS];
//子线程熟练

//1,链表节点
typedef struct Node{
    int fd_client;
    //用来创建master端给客户端发送信息的套接字
    struct sockaddr_in addr_client;
    //保存客户端信息
    socklen_t len_addr_client;
    //标记addr——client长度
    char filename[scripe][max_size];
    //脚本的名字
    struct Node *next;
    //指向下一个节点
}Node;
typedef struct linkedlist{
    Node head;
    //虚拟节点
    int length;
    //链表长度
    int index;
}linkedlist;

//链表初始化
void init_linkedlist(linkedlist *p, int ind) {
    p->index = ind;
    p->head.next = NULL;
    p->length = 0;
    return ;
}

//申请链表节点
Node *get_new_node() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    p->len_addr_client = sizeof(struct sockaddr_in);
    return p;
}

//在链表某个位置插入一个节点
void insert_list(linkedlist *l, Node *new_node, int ind) {
    Node *p = &(l->head);
    while (ind--) {
        p = p->next;
        if (p == NULL) return ;
    }
    new_node->next = p->next;
    p->next = new_node;
    l->length += 1;
    return ;
}

//删除链表节点
void delete_node(linkedlist *l, Node *node) {
    if (node == NULL) return ;
    Node *current_node = &(l->head);
    while (current_node != NULL && current_node->next != node) {
        current_node = current_node->next;
    }
    Node *delete_node = current_node->next;
    current_node->next = delete_node->next;
    free(delete_node);
    l->length -= 1;
    return ;
}

//遍历链表寻找元素最少的那个链表
int find_min(linkedlist *l) {
    int ret = 0x3f3f3f3f, ind = 0;
    for (int i = 0; i < INS; i++) {
        if (l[i].length < ret) {
            ret = l[i].length;
            ind = i;
        }
    }
    return ind;
}
void output(linkedlist *l) {
    printf ("[");
    printf("index :%d length :%d\n", l->index, l->length);
    for (Node *node = l->head.next; node != NULL; node = node->next) {
        printf("%s ", inet_ntoa(node->addr_client.sin_addr));
    }
    printf("]\n");
    return ;
}

//2hash结构
//hash结构定义
typedef struct HashTable{
    int data[hashsize];
    int flag[hashsize];
}HashTable;

//hash函数
int hashfunc(int value) {
    return value &0x7fffffff;
}

//2次探测法
int search(HashTable *h, int value) {
    int pos = hashfunc(value);
    int ind = pos % hashsize;
    int time = 1;
    while (h->flag[ind] != -1 && h->flag[ind] != value) {
        ind = (ind + time * time) % hashsize;
        time++;
    }
    if (h->flag[ind] == value && h->data[ind] == 1) {
        //插入过
        return 1;
    } else if (h->flag[ind] == value && h->data[ind] == -1){
        //没插入过
        return 0;
    }
    //不存在,无法插入
    return -1;
}

//插入hash
int insert_hash(HashTable * h, int value) {
    int pos = hashfunc(value);
    int ind = pos % hashsize;
    int time = 1;
    while (h->flag[ind] != -1 && h->flag[ind] != value) {
        ind = (ind + time * time) % hashsize;
        time++;
    }
    if (h->flag[ind] == value) {
        h->data[ind] = 1;
        return ind;
    }
    return -1;
}

//hash初始化flag
void insert_flag(HashTable *h, int value) {
    int pos = hashfunc(value);
    int ind = pos % hashsize;
    int time = 1;
    while (h->flag[ind] != -1) {
        ind = (ind + time * time) % hashsize;
        time++;
    }
    h->flag[ind] = value;
    return ;
}

//初始化hash 
void init_hash(HashTable * h, MASTER * mast) {
   memset(h, -1, sizeof(HashTable));
    char buffer[max_size];
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, mast->prename);//192.168.1
    strcat(buffer, ".");
    int len = strlen(buffer);
    for (int i = mast->start; i <= mast->finish; i++) {
        sprintf(buffer + len, "%d", i);
        insert_flag(h, inet_addr(buffer));
    }
    return ;
}

//定义结构体全局变量和master变量
MASTER mast;

linkedlist list[INS];

HashTable h;

//二，初始化功能
//读取配置文件，读取一个键值，结果在保存在value中,且函数内部申请空间
char *get_conf_value(const char *pathname, const char *key_name) {
    char *line;
    size_t len = 0;
    ssize_t read;
    char *value = (char *)calloc(sizeof(char), max_size);
    FILE *fp = NULL;
    fp = fopen(pathname, "r");
    if (fp == NULL) {
        printf ("%d",__LINE__);
        perror("fopen:");
        return NULL;
    }

    while ((read = getline(&line,&len,fp)) > 0) {
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
    if (value == NULL) {
        printf("%d %s is node",__LINE__, key_name);
        perror("value :");
    }
    return value;
}

//初始化ｍａｓｔ结构体 开放的端口，存储总路径，允许的ip范围，线程，等
void init_master(MASTER *mast) {
    char temp[max_size];
    pthread_mutex_init(&g_mutex[0], NULL);
    pthread_mutex_init(&g_mutex[1], NULL);
    pthread_mutex_init(&g_mutex[2], NULL);
    pthread_mutex_init(&g_mutex[3], NULL);
    pthread_mutex_init(&g_mutex[4], NULL);
    mast->path = get_conf_value("./mast.conf", "PATH");
    mast->listen_port[0] = atoi(get_conf_value("../common/pihealthd.conf", "master_port"));
    mast->listen_port[1] = atoi(get_conf_value("../common/pihealthd.conf", "master_port2"));
    mast->listen_port[2] = atoi(get_conf_value("../common/pihealthd.conf", "master_port3"));
    mast->client_port = atoi(get_conf_value("../common/pihealthd.conf", "client_port"));
    mast->prename = get_conf_value("../common/pihealthd.conf", "prename");
    mast->start = atoi(get_conf_value("../common/pihealthd.conf", "start"));
    mast->finish = atoi(get_conf_value("../common/pihealthd.conf", "finish"));
    if(access(mast->path, F_OK) == -1){
        mkdir(mast->path, 0775);
    }
    return ;
}

//初始化链表数组
void init_list(linkedlist *list) {
    for (int i = 0; i < INS; i++) {
        init_linkedlist(&list[i], i);
    }
}

//打开监听端口,等待客户端心跳或者传送信息
int start_listen(int *fd_server, struct sockaddr_in *addr_server, int listen_port) {
    addr_server->sin_family = AF_INET;
    addr_server->sin_port = htons(listen_port);
    addr_server->sin_addr.s_addr = htonl(INADDR_ANY);

    if ((*fd_server = socket(AF_INET, SOCK_STREAM,0)) < 0) {
        perror("socket: ");
        return -1;
    }
    if (bind(*fd_server, (struct sockaddr *)addr_server, sizeof(*addr_server)) < 0){
        perror("bind: ");
        exit(1);
        return -1;
    }
    if (listen(*fd_server, BACKLOG) < 0) {
        perror("listen: ");
        return -1;
    }   
}


//初始化链表节点存储的脚本的信息文件名
void mkfile(Node *node) {    
    char buffer[max_size];
    strcpy(buffer, mast.path);
    strcat(buffer,"/");
    strcat(buffer, inet_ntoa(node->addr_client.sin_addr));
    if (access(buffer, F_OK) == -1){
        //根据ｉｐ创建文件夹
        mkdir(buffer,0775);
    }
    strncpy(node->filename[0], buffer, strlen(buffer));
    strcat(node->filename[0], "/0.Malevolent_process.log");
    strncpy(node->filename[1], buffer, strlen(buffer));
    strcat(node->filename[1], "/1.cpu.log");
    strncpy(node->filename[2], buffer, strlen(buffer));
    strcat(node->filename[2], "/2.gesiofsysop.log");
    strncpy(node->filename[3], buffer, strlen(buffer));
    strcat(node->filename[3], "/3.yonghu.log");
    strncpy(node->filename[4], buffer, strlen(buffer));
    strcat(node->filename[4], "/4.mem.log");
    strncpy(node->filename[5], buffer, strlen(buffer));
    strcat(node->filename[5], "/5.disk.log");

}
//建立链表初始化节点信息,并将新的节点存储入最短的那个链表中,如果哈希表中存在这个值，将不在插入
int  accept_client(){
    Node *temp = get_new_node();
    if((temp->fd_client = accept(mast.fd_server[0], (struct sockaddr *)(&(temp->addr_client)), &(temp->len_addr_client)))  < 0){
        close(temp->fd_client);
        perror("accept :");
        return -1;
    }
    close(temp->fd_client);
    int ind = find_min(list);
    printf("heart %s\n", inet_ntoa(temp->addr_client.sin_addr));

    if(search(&h, inet_addr(inet_ntoa(temp->addr_client.sin_addr))) == 0){
        pthread_mutex_lock(&g_mutex[ind]);
        insert_hash(&h, inet_addr(inet_ntoa(temp->addr_client.sin_addr)));
        insert_list(&list[ind],temp, list[ind].length);
        pthread_mutex_unlock(&g_mutex[ind]);
    }
    mkfile(temp);

    return 0;
}

//总初始化函数
void init(){
    init_master(&mast);
    init_hash(&h, &mast);
    init_list(list);
    return ;
}

//三，主函数
int main() {
    pthread_t t[INS + 1];
    //线程标记变量

    init();
    //调用各种初始化函数
    
    for (int i = 0; i < INS; i++) {
        if (pthread_create(&t[i], NULL, func, (void *)&list[i]) == -1) {
            printf("%d", __LINE__);
            perror("pthread_create:");
            return -1;
        }
    }
    //调用各种初始化函数线程去主动链接客户端，并接收信息

    for (int i = 0; i < pot; i++) {
        if (start_listen(&mast.fd_server[i], &(mast.addr_server[i]), mast.listen_port[i]) < 0) {
            perror("start_listen is ");
            exit(1);
        }
    }
    //监听需要接听的端口
    if (pthread_create(&t[INS], NULL, func2,(void *)0) == -1) {
        printf("%d", __LINE__);
        perror("pthread_create:");
        return -1;
    }
    //接收报警信息的线程

    while (1) {
        accept_client();
        //主线程，等待连接
    }
    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    pthread_join(t[2], NULL);
    pthread_join(t[3], NULL);
    pthread_join(t[4], NULL);
    //等待线程返回
    return 0;
}

//尝试链接　并删除不在线的节点
int init_client(linkedlist *l, Node *temp) {
    if ((temp->fd_client = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
    temp->addr_client.sin_family = AF_INET;
    temp->addr_client.sin_port = htons(mast.client_port);
    
    if (connect(temp->fd_client, (struct sockaddr *)&(temp->addr_client), sizeof(temp->addr_client)) < 0) {
        //不存在　进行删除
        printf("%s %d is non\n", inet_ntoa(temp->addr_client.sin_addr), temp->len_addr_client);
        pthread_mutex_lock(&g_mutex[l->index]);
        int ind = insert_hash(&h, inet_addr(inet_ntoa(temp->addr_client.sin_addr)));//返回哈希下标
        if (ind >= 0) h.data[ind] = -1;//删除哈希
        close(temp->fd_client);
        delete_node(l, temp);
        pthread_mutex_unlock(&g_mutex[l->index]);
        return -1;
    }
    return 0;
}

//接受客户端数据
void recive_data(Node *node) {
    if (access(mast.path, 0775) == -1) {
        mkdir(mast.path, 0775);
        //防止误删
    }
    char buffer[max_size + 5];
    int size = 0;
    FILE *f;
    strcpy(buffer, mast.path);
    strcat(buffer, "/");
    strcat(buffer, inet_ntoa(node->addr_client.sin_addr));
    //获取文件名
    if (access(buffer, F_OK) == -1) {
        mkdir(buffer, 0775);
        //根据ｉｐ创建文件夹
    }
    //每次链接第一个总是标志位，在相应的套接字缓冲区
    size = recv(node->fd_client, buffer, 1, 0);
    printf("size %d %c\n", size, buffer[0]);
    //从套接字缓冲区接收一个字
    if(size > 0 && buffer[0] == '0'){
        f = fopen(node->filename[0], "a+");
    } else if(size > 0 && buffer[0] == '1'){
        f = fopen(node->filename[1], "a+");
    } else if(size > 0 && buffer[0] == '2'){
        f = fopen(node->filename[2], "a+");
    } else if(size > 0 && buffer[0] == '3'){
        f = fopen(node->filename[3], "a+");
    } else if(size > 0 && buffer[0] == '4'){
        f = fopen(node->filename[4], "a+");
    } else if(size > 0 && buffer[0] == '5'){
        f = fopen(node->filename[5], "a+");
    }else {
        //有链接但是没数据的化
        size = -10;
    }
    //根据标志位打开文件
    while (size > 0) {
        memset(buffer,0,sizeof(buffer));
        size = recv(node->fd_client,buffer,max_size, 0);
        buffer[size] ='\0';
        fwrite(buffer, strlen(buffer), sizeof(buffer[0]), f);
        //接受相应缓存区的东西并存贮在文件中
    }
    size != -10 && fclose(f);
    close(node->fd_client);
    //关闭文件关闭套接字
    return ;
}

void *func(void *arg) {
    linkedlist *list = (linkedlist *)arg;
    while(1){
        //output(list);
        
        for(Node *i = list->head.next; i != NULL && (int )i->addr_client.sin_port != 0; i = i->next){
            //printf("%s is connect\n", inet_ntoa(i->addr_client.sin_addr));
            for(int j = 0; j < scripe; j++){
                printf("%s is connect\n", inet_ntoa(i->addr_client.sin_addr));
                //接受６个脚本的信息，创建６次套接字
                if(init_client(list, i) >= 0){
                    //do something
                    recive_data(i);
                }else{
                    break;
                }
            }
        }
        sleep(2);
    }
    //循环遍历链表，每个节点代表一个客户端，每个客户端接受６次信息，依次是６个脚本的信息
    //遍历结束会睡眠几秒，等待客户端有足够的数据
    pthread_exit(NULL);    
    return NULL;
}

//报警信息事实传递
void *func2(void *arg){
    while (1) {
        Node *temp = get_new_node();
        if((temp->fd_client = accept(mast.fd_server[1], (struct sockaddr *)(&(temp->addr_client)), &(temp->len_addr_client)))  < 0){
            close(temp->fd_client);
            perror("accept :");
            return NULL;
        }
        char buffer[max_size + 5];
        int size = 0;
        size = recv(temp->fd_client, buffer, max_size, 0);
        if (size > 0) {
            printf("%s: %s", inet_ntoa(temp->addr_client.sin_addr), buffer);
        }
        close(temp->fd_client);
    }
    return NULL;
}



