/*************************************************************************
	> File Name: 297.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年11月04日 星期日 21时59分24秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
};
//////////////////////////////////////////////////////////////////////////
#define maxn 10000
typedef struct Queue{
    struct TreeNode ** data;
    int head,tail,count,length;
}Queue;

Queue *init(int length){
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (struct TreeNode **)malloc(sizeof(struct TreeNode*));
    q->head = 0;
    q->tail = -1;
    q->count = 0;
    q->length = length;
    return q;
}

void push(Queue *q,struct TreeNode *node){
    if(q->count >= q->length) return ;
    q->tail = (q->tail + 1) % q->length;
    q->data[q->tail] = node;
    q->count++;
    return ;
}

struct TreeNode* top(Queue *q){
    return q->data[q->head];
}


void  pop(Queue *q){
    q->head = (q->head + 1) % q->length;
    q->count -= 1;
    
}

void clear(Queue *q){
    free(q->data);
    free(q);
}
int empty(Queue *q){
    return q->count <= 0;
}

void output(Queue * q){
    printf("Queue = [ %d %d     ",q->head,q->tail); 
    for(int i = q->head; i <= q->tail; i++){
        printf("%d ",q->data[i]->val);
    }
    printf("]\n");
}


///////////////////////////////////




/** Encodes a tree to a single string. */
int preorder(struct TreeNode * root){
    if(root == NULL ) return 0;
    printf("%d",root->val);
    if(root->left != NULL || root->right != NULL){
        printf("(");
        preorder(root->left);
        printf(",");
        preorder(root->right);
        printf(")");
    }
    return 0;
}

int getint(char **arr){
    int temp  = 0;
    while((**arr) >= '0' && (**arr) <= '9') {
        temp = temp * 10 + **arr - '0';
        (*arr)++;
    }
    return temp;
}

struct TreeNode * getNewnode(int value){
    struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    node->val = value;
    node->left = node->right = NULL;
    return node;
}

/** Decodes your encoded data to tree. */
struct TreeNode* deserialize(char * data) {
    data++;//[
    int temp;
    struct TreeNode * root = NULL;
    if(*data >= '0' && *data <= '9'){
        temp = getint(&data);
        data++;
    }else {
        return NULL;
    }
    root = getNewnode(temp);

    Queue *q = init(maxn);
    push(q, root);
    while(!empty(q) && strlen(data) > 0){
        struct TreeNode *cur = top(q);
        pop(q);
        //printf("%d ",cur->val);
        printf(" ||%s|| ", data, strlen(data));
        if(*data >= '0' && *data <= '9'){
            temp = getint(&data);
            cur->left = getNewnode(temp);
            push(q,cur->left);
            data++;
        }else {
            //printf(" ||%s|| ", data);
            cur->left = NULL;
            data+= 5;//"null,"
        }

        if(*data >= '0' && *data <= '9'){
            temp = getint(&data);
            cur->right = getNewnode(temp);
            push(q,cur->right);
            data++;
        }else {
            //printf(" ??%s?? ", data);
            cur->right = NULL;
            data+= 5;//"null,"
        }
        //printf("|%d ",cur->val);
    }
    preorder(root);
    return root;
}

int main(){
    char str[] = "[1,2,3,null,null,4,5]";
    deserialize(str);


    return 0;
}


