/*************************************************************************
> File Name: hafu.cpp
> Author: ldc
> Mail: litesla
> Created Time: 2018年10月28日 星期日 20时01分47秒
************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
typedef struct Node{
    int key,freq;
    struct Node *lchild,*rchild;
}Node;

Node * getNewNode(int key,int freq){
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->freq = freq;
    p->lchild = p->rchild = NULL;
    return p;
}

void clear(Node * root){
    if(root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}
int swap_node(Node **p,Node **q){
    //printf("[%d %d ]",(*p)->freq,(*q)->freq);
    Node *temp = *p;
    *p = *q;
    *q = temp;
    //printf("[%d %d %d]\n ",temp->freq,(*p)->freq,(*q)->freq);
    return 1;
}
void out(Node **arr,int n){
    printf("[");
    for(int i = 0; i < n; i++){
        printf("%d ",arr[i]->freq);
    }
    printf("]\n");
}

Node * build_haffman(Node **arr,int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(arr[j]->freq < arr[n - i - 1]->freq){
                swap_node(arr + j, arr + n - i - 1);
            }
            if(arr[j]->freq < arr[n - i - 2]->freq){
                swap_node(arr + j, arr + n - i - 2);
            }
        }
        printf("zui:%d ci:%d %d \n",arr[n - i - 1]->freq,arr[n - i - 2]->freq,n - i- 1);
        Node *temp = getNewNode(0,arr[n - i - 1]->freq + arr[n - i - 2]->freq);
        temp->lchild = arr[n - i - 1];
        temp->rchild = arr[n - i - 2];
        arr[n - i - 2] = temp;
        out(arr,n - i - 1);
    }
    return arr[0];
}

void extract_code(Node *root,char (*code)[20],int k,char *buff){
    buff[k] = 0;
    if(root->key){
        strcpy(code[root->key],buff);
        return ;
    }
    buff[k] = '0';
    extract_code(root->lchild,code,k + 1, buff);
    buff[k] = '1';
    extract_code(root->rchild,code,k + 1, buff);
}

void preorter(Node * root){
    if(root == NULL) return ;
    printf("%d ", root->freq);
    if(root->lchild != NULL || root->rchild){
        printf("(");
        preorter(root->lchild);
        printf(",");
        preorter(root->rchild);
        printf(")");

    }
}


int main(){
    int n;
    Node *root;
    scanf("%d", &n);
    Node **arr = (Node **)malloc(sizeof(Node *) *n);
    for(int i = 0; i < n; i++){
        char key[10];
        int freq;
        scanf("%s%d",key,&freq);
        arr[i] = getNewNode(key[0],freq);
    }

    root = build_haffman(arr,n);
    printf("\n");
    preorter(root);
    printf("\n");
    //printf("%d", root->freq);
    char code[256][20] = {0}, buff[20];
    extract_code(root,code,0, buff);
    for(int i = 0; i < 256; i++){
        if(code[i][0] == 0) continue;
        printf("%c:%s\n",i,code[i]);
    }
    return 0;
}
