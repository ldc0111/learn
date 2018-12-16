/*************************************************************************
	> File Name: 2.AVL.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年12月15日 星期六 20时44分46秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



#define max(a, b) ({\
    __typeof(a) _a = (a);\
    __typeof(a) _b = (b);\
    _a > _b ? _a : _b;\
})
typedef struct Node{
    int key, h;
    struct Node *lchild, *rchild;
}Node;

Node *NIL;
__attribute__((constructor))
void init_nil() {
    NIL = (Node *)malloc(sizeof(Node));
    NIL->key = 0;
    NIL->lchild = NIL->rchild = NIL;
    NIL->h = 0;
}
Node *init(int key){
    Node *p = (Node *)malloc(sizeof(Node));
    p->lchild = p->rchild = NIL;
    p->h = 1;
    p->key = key;
    return p;
}
void clear(Node *root){
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}
Node *left_rotate(Node *root){
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    root->h = max(root->lchild->h, root->rchild->h) + 1;
    temp->h = max(temp->lchild->h, temp->rchild->h) + 1;
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    root->h = max(root->lchild->h, root->rchild->h) + 1;
    temp->h = max(temp->lchild->h, temp->rchild->h) + 1;

    return temp;
}


Node *maintain(Node *root) {
    if (abs(root->lchild->h - root->rchild->h) < 2) return root;
    if (root->lchild->h > root->rchild->h) {
        //不会越界
        if(root->lchild->lchild->h < root->lchild->rchild->h) {
            //小左旋
            root->lchild = left_rotate(root->lchild);
        }
        //大右旋
        root = right_rotate(root);
    } else {
        if(root->rchild->lchild->h > root->rchild->rchild->h) {
            //小右旋
            root->rchild = right_rotate(root->rchild);
        }
        //大左旋
        root = left_rotate(root);
    }
    return root;
}



Node *insert(Node *root, int key) {
    if (root == NIL){
        return init(key);
    }
    if (root->key == key) return root;
    if (root->key  < key) {
        root->rchild = insert(root->rchild, key);
    } else {
        root->lchild = insert(root->lchild, key);
    }
    root->h = max(root->lchild->h, root->rchild->h) + 1;//如果没有节点防止错误，所以设置ＮＩＬ
    return maintain(root);
}
void output(Node *root) {
    if (root == NIL) return ;
    printf("(%d, %d, %d)\n", root->key, root->lchild->key, root->rchild->key);
    output(root->lchild);
    output(root->rchild);
    return ;
}

int main(){
    srand(time(0));
    Node *root = NIL;
    for (int i = 1; i <= 5; i++) {
        root = insert(root, i);
        output(root);
        printf("--------------\n");
    }
    clear(root);
    /*
    root = NIL;
    int n = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int key = rand() % 30;
        root = insert(root, key);
        printf("-----------\n");
    }*/
    return 0;
}
