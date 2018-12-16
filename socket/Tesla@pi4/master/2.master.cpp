/*************************************************************************
  > File Name: 2.master.cpp
  > Author: ldc
  > Mail: litesla
  > Created Time: 2018年11月15日 星期四 18时37分47秒
 ************************************************************************/
#include "../common/common.h"
#include "master.h"

#define INS 5
#define min(a,b) ((a) < (b) ? (a) : (b))
#define hashsize 20000
#define scripe  6
//////////////////////////////////////

pthread_mutex_t g_mutex[5];
//初始化　
//链表ａｐｉ
typedef struct Node{
    int fd_client;//用来创建客户给客户端发送信息的端套接字
    struct sockaddr_in addr_client;//保存客户端信息
    socklen_t len_addr_client;//保存addr_client 长度
    char filename[scripe][max_size];
    struct Node *next;
}Node;
typedef struct linkedlist{
    Node head;
    int length;
    int index;
}linkedlist;



void init_linkedlist(linkedlist *p, int ind) {
    p->index = ind;
    p->head.next = NULL;
    p->length = 0;
    return ;
}

Node * getnewnode(){
    Node *p = (Node *)calloc(sizeof(Node), 1);
    p->len_addr_client = sizeof(struct sockaddr_in);
    return p;
}

void insert(linkedlist * l, Node *new_node, int ind){
    Node *p = &(l->head);
    while (ind--) {
        p = p->next;
        if(p == NULL) return ;
    }
    new_node->next = p->next;
    p->next = new_node;
    l->length += 1;
    return ;
}

void delete_node(linkedlist *l, Node * node){
    if(node == NULL) return ;//是空不删
    Node *current_node = &(l->head);
    while(current_node != NULL && current_node->next != node){
        current_node = current_node->next;
    }
    Node *delete_node = current_node->next;
    current_node->next = delete_node->next;
    free(delete_node);
    l->length -= 1;
    return ;
}

////////////////////////////////////////////////////////////////
void* func(void *);

int find_min(linkedlist * l){
    int ret = 0x3f3f3f3f, ind = 0;
    for(int i = 0; i < INS; i++){
        if(l[i].length < ret){
            ret = l[i].length;
            ind = i;
        }
    }
    return ind;
}

/*
   void output(linkedlist * l){
   for(int i = 0; i < INS; i++){
   printf("[%d.list:",i);
   for( Node *node = l[i].head.next; node != NULL; node=node->next){
   printf(" %d", node->fd_client);
   }
   printf("]\n");
   }
   }*/


void output2(linkedlist *l){
    printf("[");
    printf("index:%d length:%d ", l->index, l->length);
    for( Node *node = l->head.next; node != NULL; node=node->next){
        printf(" %s", inet_ntoa(node->addr_client.sin_addr));
    }
    printf("]\n");
    return ;

}
//////////////////////////////////////////////////////////////////////////
typedef struct HashTable{
    int  data[hashsize];
    int  flag[hashsize]; 
}HashTable;

int hashfunc(int value){
    return value &0x7fffffff;
}
int search(HashTable *h, int value){

    int pos = hashfunc(value);
    int ind = pos % hashsize;
    int time = 1;

    while(h->flag[ind] != -1 && h->flag[ind] != value){
        ind = (ind + time * time) % hashsize;
        time++;
    }
    if(h->flag[ind] == value && h->data[ind] == 1) {
        return 1;//插入过
    }else if(h->flag[ind] == value && h->data[ind] == -1){
        return 0;//没插入过
    }
    //不存在
    return -1;
}

int insert_hash(HashTable *h, int value){
    int pos = hashfunc(value);
    int ind = pos % hashsize;
    int time = 1;
    while(h->flag[ind] != -1 && h->flag[ind] != value){
        ind = (ind + time * time ) % hashsize;
        time++;
    }
    if(h->flag[ind] == value){
        h->data[ind] = 1;
        return ind;
    }
    return -1;
}
void insert_flag(HashTable *h, int value){
    int pos = hashfunc(value);
    int ind = pos % hashsize;
    int time = 1;
    while(h->flag[ind] != -1){
        ind = (ind + time * time ) % hashsize;
        time++;
    }
    h->flag[ind] = value;
    return ;
}

void init_hash(HashTable *h, MASTER * mast){
    memset(h,-1,sizeof(HashTable));
    char buffer[max_size];
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, mast->prename);
    strcat(buffer, ".");
    int len = strlen(buffer);
    //printf("%d %d\n",mast->start, mast->finish);
    for(int i = mast->start; i <= mast->finish; i++){
        sprintf(buffer + len, "%d", i);
        //printf("%s\n",buffer);
        insert_flag(h,inet_addr(buffer));
    }
    return ;
}

/////////////////////////////////////////////////////////////////////
MASTER mast;

linkedlist list[INS];

HashTable h;

///////////////////////////////////////////////////////
//初始化ｓｏｃｋｅｔ
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

//初始化ｍａｓｔ结构体 开放端口，存储总路径
void init(MASTER *mast){
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
void init_list(linkedlist *list){
    for(int i = 0; i < INS; i++){
        init_linkedlist(&list[i], i);
    }
}

int start_listen(int *fd_server, struct sockaddr_in *addr_server, int listen_port){
    addr_server->sin_family = AF_INET;
    addr_server->sin_port = htons(listen_port);
    addr_server->sin_addr.s_addr = htonl(INADDR_ANY);

    if ((*fd_server = socket(AF_INET, SOCK_STREAM,0)) < 0) {
        perror("socket: ");
        return -1;
    }
    if (bind(*fd_server, (struct sockaddr *)addr_server, sizeof(*addr_server)) < 0){
        perror("bind: ");
        return -1;
    }
    if (listen(*fd_server, BACKLOG) < 0) {
        perror("listen: ");
        return -1;
    }   
}

void mkfile(Node *node){    
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


//建立链表初始化节点信息
int  accept_client(){
    Node *temp = getnewnode();
    if((temp->fd_client = accept(mast.fd_server[0], (struct sockaddr *)(&(temp->addr_client)), &(temp->len_addr_client)))  < 0){
        close(temp->fd_client);
        perror("accept :");
        return -1;
    }
    close(temp->fd_client);
    int ind = find_min(list);
    printf("connect %s\n", inet_ntoa(temp->addr_client.sin_addr));
    if(search(&h, inet_addr(inet_ntoa(temp->addr_client.sin_addr))) == 0){
        pthread_mutex_lock(&g_mutex[ind]);
        insert_hash(&h, inet_addr(inet_ntoa(temp->addr_client.sin_addr)));
        insert(&list[ind],temp, list[ind].length);
        pthread_mutex_unlock(&g_mutex[ind]);
    }
    mkfile(temp);


    //output2(&list[ind]);
    return 0;
}
int main(){
    memset(&list, 0, sizeof(list));
    pthread_t t[INS];
    init(&mast);
    init_hash(&h, &mast);
    init_list(list);
    for(int i = 0; i < INS; i++){
        if(pthread_create(&(t[i]), NULL, func, (void *)&list[i]) == -1){
            perror("pthread_create:");
            return -1;
        }
    }
    for(int i = 0; i < pot; i++){
        if(start_listen(&(mast.fd_server[i]), &(mast.addr_server[i]), mast.listen_port[i]) < 0 ){
            perror("start_listen is error!");
            return  -1;
        }
    }
    while(1){
        accept_client();
    }
    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    pthread_join(t[2], NULL);
    pthread_join(t[3], NULL);
    pthread_join(t[4], NULL);
    return 0;
}
//尝试链接，不存在删除存在，不删除
int init_client(linkedlist *l, Node *temp){
    if ((temp->fd_client = socket(AF_INET,SOCK_STREAM,0)) < 0){
        perror("socket");
        return -1;
    }
    temp->addr_client.sin_family = AF_INET;
    temp->addr_client.sin_port = htons(mast.client_port);

    if(connect(temp->fd_client, (struct sockaddr *)&(temp->addr_client), sizeof(temp->addr_client)) < 0){
        //不存在
        //do something
        printf("%s %d is non\n", inet_ntoa(temp->addr_client.sin_addr), temp->len_addr_client);
        pthread_mutex_lock(&g_mutex[l->index]);
        int ind = insert_hash(&h, inet_addr(inet_ntoa(temp->addr_client.sin_addr)));
        if(ind >= 0){
            h.data[ind] = -1;
        }
        close(temp->fd_client);
        delete_node(l, temp);
        pthread_mutex_unlock(&g_mutex[l->index]);
        return -1;
    }
    return 0;
}

void recive_data(Node * node){
    if(access(mast.path,0775) == -1){
        //防止误删
        mkdir(mast.path,0775);
    }
    char buffer[max_size + 5];
    int size = 0;
    FILE *f;
    int recode;
    int server_tfd;
    strcpy(buffer, mast.path);
    strcat(buffer,"/");
    strcat(buffer, inet_ntoa(node->addr_client.sin_addr));
    if(access(buffer, F_OK) == -1){
        //根据ｉｐ创建文件夹　防止误删
        mkdir(buffer,0775);
    }
    printf("socket %d %s\n", node->fd_client, inet_ntoa(node->addr_client.sin_addr));
    //如果文件没有结束第一个是标识码，如果文件结束第一个是一个英文字符，直接跳出结束套接字就
    size = recv(node->fd_client, buffer, 1, 0);
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
    }
    while(size > 0){
        memset(buffer,0,sizeof(buffer));
        size = recv(node->fd_client,buffer,max_size, 0);
        buffer[size] ='\0';
        printf("size :%d\n%s\n", size, buffer);
        fwrite(buffer, strlen(buffer), sizeof(buffer[0]), f);
    }
    fclose(f);
    close(node->fd_client);
}


void* func(void *arg){
    linkedlist *list = (linkedlist *)arg;
    while(1){
        //output2(list);
        for(Node *i = list->head.next; i != NULL && (int )i->addr_client.sin_port != 0; i = i->next){
            for(int j = 0; j < scripe; j++){
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
    pthread_exit(NULL);
    return NULL;
}
