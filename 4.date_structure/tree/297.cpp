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
    q->data = (struct TreeNode **)calloc(sizeof(struct TreeNode*),length);
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
    printf("Queue = [ head %d tail %d: ",q->head,q->tail); 
    for(int i = q->head; i <= q->tail; i++){
        printf("%d ",q->data[i]->val);
    }
    printf("]\n");
}
//////////////////////////////////////////////////////////////
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
    int temp  = 0,flag = 1;
    if((**arr) == '-') flag = -1,(*arr)++;
    while((**arr) >= '0' && (**arr) <= '9') {
        temp = temp * 10 + **arr - '0';
        (*arr)++;
    }
    return temp * flag;
}

struct TreeNode * getNewnode(int value){
    struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    node->val = value;
    node->left = node->right = NULL;
    return node;
}
/////////////////////////////////////////////////////////////////////
int dep(struct TreeNode *root){
    if(root == NULL) return 0;
    int l = dep(root->left),r = dep(root->right);
    return (l > r ? l: r) +1;
}
void cha(char *ch, int val){
    int i = 0,j = 0,flag = 1;
    int a[20];
    if(val < 0) val = -val,flag = -1;
    while(val){
        a[i++] = val % 10 + '0';
        val /= 10;
    }
    a[i] = 0;
    if(flag == -1){
        ch[j++] = '-';
    }
    while(i--){
        ch[j++] = a[i];
    }
    ch[j] = 0;
}
/** Encodes a tree to a single string. */
char* serialize(struct TreeNode* root) {
    if(root == NULL) return NULL;
    int de = dep(root) - 1,post = 1,temp = 0;
    char *a = (char *)calloc(sizeof(char),maxn);
    char ch[20];
    Queue *q = init(100); 
    push(q,root);
    cha(ch,root->val);
    strcat(a,ch);
    ch[0] = ',';
    while(!empty(q)){//层
        temp = 0;
        while(post--){//个
            output(q);
            printf("top : %d %d %d de %d\n",top(q)->val, top(q)->left == NULL, top(q)->right == NULL,de);
            if(top(q)->left == NULL && de > 0){
                strcat(a, ",null");
            }else if(top(q)->left != NULL){
                cha(ch+1,top(q)->left->val);
                strcat(a,ch);
                push(q,top(q)->left);
                temp++;
            }
            if(top(q)->right == NULL && de > 0){
                strcat(a, ",null");
            }else if(top(q)->right != NULL){
                cha(ch + 1,top(q)->right->val);
                strcat(a,ch);
                push(q,top(q)->right);
                temp++;
            }
            pop(q);
        }
        de--;
        post = temp;
    }
    return a;
}

/** Decodes your encoded data to tree. */
struct TreeNode* deserialize(char* data) {
    if(data == NULL) return NULL;
    //printf("%s\n",data);
    int temp;
    struct TreeNode * root = NULL;
    if(*data != 'n'){
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
        if(*data != 'n' && strlen(data) > 0){
            temp = getint(&data);
            cur->left = getNewnode(temp);
            push(q,cur->left);
            data++;
        }else {
            cur->left = NULL;
            data+= 5;//"null,"
        }

        if(*data != 'n' && strlen(data) > 0){
            temp = getint(&data);
            cur->right = getNewnode(temp);
            push(q,cur->right);
            data++;
        }else {
            cur->right = NULL;
            data+= 5;//"null,"
        }
    }
    //preorder(root);
    return root;
}




int main(){
    char str[80] = "1,2,3,5,null,null,4";
    struct TreeNode * root = deserialize(str);
    preorder(root);
    printf("\n");
    printf("%s",serialize(root));
    return 0;
}


