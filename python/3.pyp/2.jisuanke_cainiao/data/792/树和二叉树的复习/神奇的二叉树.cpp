#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
}Node;

Node* init(int data){
    Node *node = (Node *)malloc(sizeof(Node));
    node->data=  data;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

Node *build(char pre_str[],char in_str[],int len){
    Node *node = init(pre_str[0] - 'a');
    int pos = strchr(in_str,pre_str[0]) - in_str;
    if(pos  > 0){
        node->lchild = build(pre_str +1, in_str,pos);
    }
    if(len - pos - 1 > 0){
        node->rchild = build(pre_str + pos + 1,in_str + pos + 1, len-pos -1);
    }
    return node;
}
void preorder(Node *node){
    printf("%c", node->data + 'a');
    if (node->lchild != NULL) {
        preorder(node->lchild);
    }
    if (node->rchild != NULL) {
        preorder(node->rchild);
    }
}
void postorder(Node * node){
    if(node->lchild != NULL){
        postorder(node->lchild);
    }
    if(node->rchild != NULL){
        postorder(node->rchild);
    }
    printf("%c",node->data + 'a');
}
void ppostorder(Node * node){
    if(node->rchild != NULL){
        ppostorder(node->rchild);
    }
    if(node->lchild != NULL){
        ppostorder(node->lchild);
    }
    printf("%c",node->data + 'a');
}
int main(){
    char  pre_str[55];
    char in_str[55];
    scanf("%s", pre_str);
    scanf("%s", in_str);
    Node *root = NULL;
    root = build(pre_str, in_str,strlen(pre_str));
    //preorder(root);
    postorder(root);
    printf("\n");
    ppostorder(root);
    printf("\n");
    return 0;
}