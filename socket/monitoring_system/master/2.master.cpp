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

typedef struct Node{
    int data;
    struct Node *next;
}Node;
typedef struct listedlist{
    Node head;
    int length;
}listedlist;

listedlist list[INS + 1];


listedlist *init_linkedlist() {
    listedlist *p = (listedlist *)malloc(sizeof(listedlist));
    p->head.next = NULL;
    p->length = 0;
    return p;
}
Node * getnewnode(int value){
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = value;
    p->next = NULL;
    return p;
}
void insert(listedlist * l,int value,int ind){
    Node *p = &(l->head);
    while (ind--) {
        p = p->next;
        if(p == NULL) return ;
    }
    Node * new_node = getnewnode(value);
    new_node->next = p->next;
    p->next = new_node;
    l->length += 1;
    return ;
}
///////////////////
typedef struct mypara{
    char *s;
    int num;
}mypara;
void* func(void *);

int find_min(listedlist * l){
    int ret = 0x3f3f3f3f,ind = 0;
    for(int i = 0; i < INS; i++){
        if(l[i].length < ret){
            ret = l[i].length;
            ind = i;
        }
    }
    return ind;
}
void output(listedlist * l){
    for(int i = 0; i < INS; i++){
        printf("[%d.list:",i);
        for( Node *node = l[i].head.next; node != NULL; node=node->next){
            printf(" %d", node->data);
        }
        printf("]\n");
    }
}

int main(){
    memset(&list, 0, sizeof(list));
    pthread_t t[INS];
    mypara myp[INS];
    int temp;
    
    for(int i = 0; i < INS; i++){
        myp[i].s = strdup("hello world");
        myp[i].num = i;
        if(pthread_create(&(t[i]), NULL, func, (void *)&myp[i]) == -1){
            perror("pthread_create:");
        }
    }
    /*
    while(scanf("%d", &temp) !=EOF){
        int ind = find_min(list);
        //Node *p = getnewnode(temp);
        //printf("%d ", temp);
        insert(&list[ind],temp, list[ind].length);
    }*/
    pthread_join(t[0],NULL);
    pthread_join(t[1],NULL);
    pthread_join(t[2],NULL);
    pthread_join(t[3],NULL);
    pthread_join(t[4],NULL);
    output(list);
    printf("%d",list[0].length);
    return 0;
}



void* func(void *arg){
    mypara *para;
    para = (mypara *) arg;
    printf("%s %d\n",para->s,para->num);
    for(int i = para->num; i <= 10; i++) {
        insert(&list[para->num], i, list[para->num].length);
    }
    //output(list);
    pthread_exit(NULL);
    return NULL;
}
