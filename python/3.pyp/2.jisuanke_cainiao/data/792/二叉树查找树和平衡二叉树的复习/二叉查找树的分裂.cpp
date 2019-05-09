#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Node{
    int data;
    struct Node *lchild, *rchild;
}Node;

Node *init(int val) {
    Node *temp = (Node *)calloc(sizeof(Node), 1);
    temp->data = val;
    return temp;
}
int getint(char *arr,int *ind) {
    int temp = 0;
    while(arr[*ind] >= '0' && arr[*ind] <= '9') {
        temp = temp * 10 + arr[(*ind)++] - '0';
    }
    //printf("[%d]",temp);
    return temp;
}

Node *build_tree(Node *root, char *arr,int *ind) {
    if (arr[*ind] == 0) return NULL;
    if (arr[*ind] == '-') {//是占位符符号
        (*ind)++;
    }
    if(arr[*ind] >='0' && arr[*ind] <= '9') {//是一个值的情况下
        int val = getint(arr,ind);
        root = init(val);
    }
    if(arr[*ind] == ','){//是逗号的情况下
        return root;
    }
    if(arr[*ind] == '(') {//是括号的情况下
        (*ind)++;
        root->lchild = build_tree(root->lchild, arr, ind);
        if(arr[*ind] == ',') {
            (*ind)++;
            root->rchild = build_tree(root->rchild, arr, ind);
        }
        (*ind)++;//＇)＇
    }
    return root;
}


void splittree(Node *root, Node **mitree, Node **matree,int n) {
    //printf("%d ",root->data);
    if(root->data <= n) {
        *mitree = init(root->data);
        if (root->lchild != NULL) splittree(root->lchild, &((*mitree)->lchild), matree, n);
        if (root->rchild != NULL) splittree(root->rchild, &((*mitree)->rchild), matree, n);
    } else {
        *matree = init(root->data);
        if (root->lchild != NULL) splittree(root->lchild, mitree, &((*matree)->lchild), n);
        if (root->rchild != NULL) splittree(root->rchild, mitree, &((*matree)->rchild), n);
    }
    return ;
}


void inorder(Node *root) {
    if (root == NULL) return ;
    inorder(root->lchild);
    printf("%d ", root->data);
    inorder(root->rchild);
}
void preorder(Node *root) {
    if (root == NULL) {
        printf("-");
        return ;
    }
    printf("%d", root->data);
    if(root->lchild == NULL && root->rchild == NULL) return ;
    if (root->lchild != NULL || root->rchild != NULL) printf("(");
    preorder(root->lchild);
    if (root->rchild != NULL)printf(",");
    preorder(root->rchild);
    if (root->lchild != NULL || root->rchild != NULL) printf(")");
    return ;
}

int main() {
    char *arr = (char *)calloc(sizeof(char),1000);
    int n,ind = 0;
    Node *root = NULL;
    Node *mitree = NULL;
    Node *matree = NULL;
    scanf("%[^\n]s",arr);
    scanf("%d",&n);
    if(arr[0] != 0)	root = build_tree(root,arr,&ind);
    //inorder(root);
    
    if (arr[0] != 0)splittree(root, &mitree, &matree,n);
    //inorder(mitree);
    if(arr[0] != 0){
    	if (mitree != NULL) preorder(mitree);
    	printf("\n");
    	if (matree != NULL) preorder(matree);
    	printf("\n");
    }
    //inorder(matree);
    
    
    return 1;
}