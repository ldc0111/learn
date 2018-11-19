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
//////////////////////////////////////


//初始化　
//链表ａｐｉ
typedef struct Node{
    int fd_client;
    struct sockaddr_in addr_client;
    socklen_t len_addr_client;
    struct Node *next;
}Node;
typedef struct linkedlist{
    Node head;
    int length;
}linkedlist;



linkedlist *init_linkedlist() {
    linkedlist *p = (linkedlist *)malloc(sizeof(linkedlist));
    p->head.next = NULL;
    p->length = 0;
    return p;
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
    printf(" %d ", l->length);
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

linkedlist list[INS + 1];

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
    mast->path = get_conf_value("./mast.conf", "PATH");
    mast->listen_port = atoi(get_conf_value("../common/pihealthd.conf", "master_port"));
    mast->client_port = atoi(get_conf_value("../common/pihealthd.conf", "client_port"));
    mast->prename = get_conf_value("../common/pihealthd.conf", "prename");
    mast->start = atoi(get_conf_value("../common/pihealthd.conf", "start"));
    mast->finish = atoi(get_conf_value("../common/pihealthd.conf", "finish"));
    if(access(mast->path, F_OK) == -1){
        mkdir(mast->path, 0775);
    }
    return ;
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

//建立链表
int  accept_client(){
    Node *temp = getnewnode();
    if(temp->fd_client = accept(mast.fd_server, (struct sockaddr *)(&(temp->addr_client)), &(temp->len_addr_client))  < 0){
        perror("accept :");
        return -1;
    }
    int ind = find_min(list);
    //printf("%d\n", inet_addr(inet_ntoa(temp->addr_client.sin_addr)));
    if(search(&h, inet_addr(inet_ntoa(temp->addr_client.sin_addr))) == 0){
        insert_hash(&h, inet_addr(inet_ntoa(temp->addr_client.sin_addr)));
        insert(&list[ind],temp, list[ind].length);
    }
    close(temp->fd_client);
    output2(&list[ind]);
    return 0;
}
int main(){
    memset(&list, 0, sizeof(list));
    pthread_t t[INS];
    init(&mast);
    init_hash(&h, &mast);
    for(int i = 0; i < INS; i++){
        if(pthread_create(&(t[i]), NULL, func, (void *)&list[i]) == -1){
            perror("pthread_create:");
            return -1;
        }
    }
    if(start_listen(&(mast.fd_server), &(mast.addr_server), mast.listen_port) < 0 ){
        perror("start_listen is error!");
        return  -1;
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

int init_client(linkedlist *l, Node *temp){
    if ((temp->fd_client = socket(AF_INET,SOCK_STREAM,0)) < 0){
        perror("socket");
        return -1;
    }
    temp->addr_client.sin_family = AF_INET;
    temp->addr_client.sin_port = htons(mast.client_port);
    if(connect(temp->fd_client, (struct sockaddr *)&(temp->addr_client), sizeof(temp->len_addr_client)) < 0){
        //不存在
        //do something
        printf("%s is non\n", inet_ntoa(temp->addr_client.sin_addr));
        int ind = insert_hash(&h, inet_addr(inet_ntoa(temp->addr_client.sin_addr)));
        if(ind >= 0){
            h.data[ind] = -1;
        }
        delete_node(l, temp);
        return -1;
    }
    return -1;
}




void recive_data(Node * node){
    char buffer[max_size];
    int size = 0;
    strcpy(buffer, mast.path);
    strcat(buffer,"/");
    strcat(buffer, inet_ntoa(node->addr_client.sin_addr));
    if(access(buffer, F_OK) == -1){//根据ｉｐ创建文件夹
        mkdir(buffer,0775);
    }
    char data[6][max_size];
    strncpy(data[0], buffer, strlen(buffer));
    strcat(data[0], "/0.Malevolent_process.log");
    strncpy(data[1], buffer, strlen(buffer));
    strcat(data[1], "/1.cpu.log");
    strncpy(data[2], buffer, strlen(buffer));
    strcat(data[2], "/2.gesiofsysop.log");
    strncpy(data[3], buffer, strlen(buffer));
    strcat(data[3], "/3.yonghu.log");
    strncpy(data[4], buffer, strlen(buffer));
    strcat(data[4], "/4.mem.log");
    strncpy(data[5], buffer, strlen(buffer));
    strcat(data[5], "/5.disk.log");
    FILE *f[6];
    f[0] = fopen(data[0], "a+");
    f[1] = fopen(data[1], "a+");
    f[2] = fopen(data[2], "a+");
    f[3] = fopen(data[3], "a+");
    f[4] = fopen(data[4], "a+");
    f[5] = fopen(data[5], "a+");

}


void* func(void *arg){
    linkedlist *list = (linkedlist *)arg;
    while(1){
        for(Node *i = list->head.next; i != NULL && (int )i->addr_client.sin_port != 0; i = i->next){
            if(init_client(list, i) >= 0){
                //do something
                recive_data(i);
            }
        }
        output2(list);
        sleep(1);
    }
    pthread_exit(NULL);
    return NULL;
}
