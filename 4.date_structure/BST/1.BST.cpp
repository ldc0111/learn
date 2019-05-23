/*************************************************************************
	> File Name: 1.BST.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年12月13日 星期四 16时21分22秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef struct BSTNode{
    int key;//键值
    struct BSTNode *lchild, *rchild;//左右孩子
}BSTNode;

//根据键值创建节点
BSTNode *init(int key) {
    BSTNode *p = (BSTNode *)malloc(sizeof(BSTNode));
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}
//插入节点
BSTNode *insert(BSTNode *root, int key) {
    if (root == NULL) return init(key);
    if (root->key == key) return root;
    if (key < root->key) root->lchild = insert(root->lchild,key);
    else root->rchild = insert(root->rchild, key);
    return root;
}

//查找ｎｏｄｅ左孩子的最右边的节点，返回节点值
BSTNode *predecesor(BSTNode *node) {
    BSTNode *temp = node->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp;
}
//删除根据键值删除节点
BSTNode *delete_node(BSTNode *root, int key) {
    if (root == NULL) return root;
    if (root->key == key) {
        if (root->lchild == NULL && root->rchild == NULL) {
            free(root);
            return NULL;
            //度为０
        }else if (root->lchild == NULL || root->rchild == NULL){
            BSTNode * temp = root->lchild ? root->lchild : root->rchild;
            free(root);
            return temp;
            //度为１
        }else {
            BSTNode *temp = predecesor(root);
            temp->key ^= root->key;
            root->key ^= temp->key;
            temp->key ^= root->key;
            root->lchild = delete_node(root->lchild, key);
            //度为２
        }
    } else {
        //不等于的情况
        if (root->key < key) root->rchild = delete_node(root->rchild, key);
        else root->lchild = delete_node(root->lchild, key);
    }
    return root;
}

void output(BSTNode *root) {
    if (root == NULL) return ;
    output(root->lchild);
    printf("%d ", root->key);
    output(root->rchild);
    return ;
}



int main() {
    srand(time(0));
    BSTNode *root = NULL;
    #define OP_NUM 20 
    for (int i = 0; i < OP_NUM; i++) {
        int key = rand() % 30;
        root = insert(root, key);
        printf("insert %d to tree\n", key);
        output(root), printf("\n");
    }
    
    for (int i = 0; i < OP_NUM; i++) {
        int key = rand() % 30;
        root = delete_node(root, key);
        printf("delete %d from tree\n",key);
        output(root); printf("\n");
    }
    return 0;
}
