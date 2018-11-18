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
//////////////////////////////////////
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

linkedlist list[INS + 1];


linkedlist *init_linkedlist() {
    linkedlist *p = (linkedlist *)malloc(sizeof(linkedlist));
    p->head.next = NULL;
    p->length = 0;
    return p;
}

Node * getnewnode(){
    Node *p = (Node *)calloc(sizeof(Node),1);
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
void output(linkedlist * l){
    for(int i = 0; i < INS; i++){
        printf("[%d.list:",i);
        for( Node *node = l[i].head.next; node != NULL; node=node->next){
            printf(" %d", node->fd_client);
        }
        printf("]\n");
    }
}
//////////////////////////////////////////////////////////////////////////
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
    mast->listen_port = atoi(get_conf_value("../common/pihealthd.conf", "PORT"));
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

int main(){
    memset(&list, 0, sizeof(list));
    pthread_t t[INS];
    MASTER mast;
    init(&mast);

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
        Node *temp = getnewnode();
        if(temp->fd_client = accept(mast.fd_server, (struct sockaddr *)&temp->addr_client, &temp->len_addr_client)  < 0){
            perror("accept :");
            return -1;
        }
        int ind = find_min(list);
        insert(&list[ind],temp, list[ind].length);
    }
    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    pthread_join(t[2], NULL);
    pthread_join(t[3], NULL);
    pthread_join(t[4], NULL);
    return 0;
}

void* func(void *arg){
    linkedlist *list = (linkedlist *)arg;
    pthread_exit(NULL);
    return NULL;
}
