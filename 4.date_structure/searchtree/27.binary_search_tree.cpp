/*************************************************************************
	> File Name: 27.binary_search_tree.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月20日 星期日 18时55分06秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct Node{
    int key;
    struct Node *lchild, *rchild;
}Node;


Node *getNewNode(int key) {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    p->key = key;
    return p;
}
Node *insert(Node *root, int key) {
    if (root == NULL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key > key) root->lchild = insert(root->lchild,key);
    else root->rchild = insert(root->rchild, key);
    return root;
}

Node *predeccessor(Node *node) {
    Node *temp = node->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp;
}

Node *earse(Node *root, int key) {
    if (root == NULL) return root;
    if (root->key < key) {
        root->rchild = earse(root->rchild, key);
    } else if (root->key > key) {
        root->lchild = earse(root->lchild, key);
    } else {
        if (root->lchild == NULL && root->rchild == NULL) {
            free(root);
            return NULL;
        } else if (root->lchild == NULL || root->rchild == NULL){
            Node *temp = (root->lchild ? root->lchild : root->rchild);
            free(root);//返回儿子
            return temp;
        } else {
            Node *temp = predeccessor(root);//去左子树找最大的
            root->key = temp->key;//覆盖
            root->lchild = earse(root->lchild, temp->key);//删除那个值
        }
    }
    return root;
}

int search(Node *root, int key) {
    if (root == NULL) return 0;
    if (root->key == key) return 1;
    return (root->key > key ? search(root->lchild, key):search(root->rchild, key));
}

void clear(Node *node) {
    if (node == NULL) return ;
    clear(node->lchild);
    clear(node->rchild);
    free(node);
    return ;
}


void output(Node *root) {
    if (root == NULL) return ;
    output(root->lchild);
    printf("%d ",root->key);
    output(root->rchild);
}

int main() {
    srand(time(0));
    int op, val;
    #define MAX_OP 20
    #define MAX_N 15
    Node *root = NULL;
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 6;
        val = rand() % MAX_N;
        switch(op) {
            case 0:{
                printf("search %d = %d\n",val, search(root, val));
            }break;
            case 1:{
                printf("erase %d from BST\n", val);
                root = earse(root,val);
            }break;
            default:{
                printf("insert %d from BST\n",val);
                root = insert(root, val);
            }break;
        }
        output(root);
        printf("\n");
    }
    clear(root);
    return 0;
}
