/*************************************************************************
	> File Name: 2.hafu.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月31日 星期三 23时26分53秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define swap(a,b){\
    __typeof(a) __temp = a; a = b; b = __temp;\
}


typedef struct node{
    int key,freq;
    struct node *lchild, *rchild;
}node;

typedef struct heap{
    node **data;
    int size,cnt;
}heap;

node * getNewnode(int n){
    node *p = (node *)malloc(sizeof(node));
    p->freq = n;
    p->key = 0;
    p->lchild = NULL;
    p->rchild = NULL;
    return p;
}

heap * init(int n){
    heap *p = (heap * )malloc(sizeof(heap));
    p->data = (node **)calloc(sizeof(node*),(n + 1));
    p->cnt = 0;
    p->size = n;
    return p;
}
int empty(heap *h){
    return h->cnt <= 0;
}
void push(heap *h, node *val){
    if(h->cnt >= h->size) return;
    h->data[++(h->cnt)] = val;
    int ind = h->cnt;
    while (ind > 1) {
        if (h->data[ind]->freq > h->data[ind >> 1]->freq) break;
        swap(h->data[ind], h->data[ind >> 1]);
        ind >>= 1;
    }
}
node* top(heap *h){
    return h->data[1];
}

void  pop(heap *h){
    if(empty(h)) return ;
    h->data[1] = h->data[(h->cnt)--];
    int ind = 1;
    while((ind << 1) <= h->cnt){
        int temp = ind;
        if(h->data[temp]->freq > h->data[ind << 1]->freq) temp = ind << 1;
        if((ind << 1 | 1) <= h->cnt && h->data[temp]->freq > h->data[ind << 1 | 1]->freq) temp = ind << 1|1;
        if(temp == ind) break;
        swap(h->data[temp], h->data[ind]);
        ind = temp;
    }
    return ;
}
int count(heap *h){
    return h->cnt;
}


node* builld_haffman(heap *h){
    node *root = NULL;
    while(count(h) != 1){
        node * a = top(h);
        pop(h);
        node *b = top(h);
        pop(h);
        node *p = getNewnode(a->freq + b->freq);
        p->lchild = a;
        p->rchild = b;
        push(h,p);
    }
    return top(h);
}

void preorder(node *root){
    if(root == NULL) return ;
    printf("%d", root->freq);
    if(root->lchild != NULL || root->rchild != NULL){
        printf("(");
        preorder(root->lchild);
        printf(",");
        preorder(root->rchild);
        printf(")");
    }
}
void inorder(node *root){
    if(root == NULL) return ;
    inorder(root->lchild);
    printf(" %d ", root->freq);
    inorder(root->rchild);
}
void output(heap *h){
    printf("Arr = [");
    for(int i = 1; i <= h->cnt; i++){
        printf(" %d",h->data[i]->freq);
    }
    printf(" ]\n");
}

void extract_code(node *root,char (*code)[20],int k,char *buff){
    buff[k] = 0;
    if(root->key){
        strcpy(code[root->key],buff);
        return ;
    }
    buff[k] = '0';
    extract_code(root->lchild,code,k + 1,buff);
    buff[k] = '1';
    extract_code(root->rchild,code,k + 1, buff);
}

int main(){
    int n;
    scanf("%d", &n);
    heap *h = init(n);
    for(int i = 0; i < n; i++){
        char a[10];
        int b;
        scanf("%s%d",a,&b);
        node* te = getNewnode(b);
        te->key = a[0];
        push(h,te);
    }
    output(h);
    node *root = builld_haffman(h);
    preorder(root);
    printf("\n");
    char code[256][20] = {0},buff[20];
    extract_code(root,code,0,buff);
    for(int i = 0; i < 256; i++){
        if(code[i][0] == 0) continue;
        printf("%c:%s\n",i,code[i]);
    }
    return 0;
}
