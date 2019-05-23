/*************************************************************************
> File Name: rbt.cpp
> Author: ldc
> Mail: litesla
> Created Time: 2019年02月17日 星期日 18时07分31秒
************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define RED 0
#define BLACK 1
#define DOUBLE_BLACK 2

typedef struct RBTNode{
    int key,color;//0 red 1 black 2 double black
    struct RBTNode *lchild, *rchild;
}RBTNode;



RBTNode *NIL;
__attribute__((constructor))
void init_NIL() {
    NIL = (RBTNode *)malloc(sizeof(RBTNode));
    NIL->key = -1;
    NIL->color = BLACK;
    NIL->rchild = NIL->rchild = NIL;
    return ;
}


RBTNode *init(int key) {
    RBTNode *p = (RBTNode *)malloc(sizeof(RBTNode));
    p->key = key;
    p->lchild = p->rchild = NIL;
    p->color = RED;
    return p;
}

void clear(RBTNode *node) {
    if (node == NIL) return ;
    clear(node->lchild);
    clear(node->rchild);
    free(node);
}

int has_red_child(RBTNode *root) {
    return root->lchild->color == RED || root->rchild->color == RED;

}

RBTNode *left_rotate(RBTNode *node) {
    RBTNode *temp = node->rchild;
    node->rchild = temp->lchild;
    temp->lchild = node;
    return temp;
}

RBTNode *right_rotate(RBTNode *node) {
    RBTNode *temp = node->lchild;
    node->lchild = temp->rchild;
    temp->rchild = node;
    return temp;
}
RBTNode *insert_maintain(RBTNode *root) {
    if (!has_red_child(root)) return root;//没有红色孩子不失衡
    if (root->lchild->color == RED && root->rchild->color == RED) {//如果左右孩子都为红色
        if (!has_red_child(root->lchild) && !has_red_child(root->rchild)) return root;//如果没有红色孙子不失衡，不调整
    } else if (root->lchild->color == RED && has_red_child(root->lchild)) {//如果左支出现双红
        if (root->lchild->rchild->color == RED) {//如果是ＬＲ型双红
            root->lchild = left_rotate(root->lchild);//进行小左旋
        }
        root = right_rotate(root);//大右旋
    } else if (root->rchild->color == RED && has_red_child(root->rchild)) {//如果右支出现双红
        if (root->rchild->lchild->color == RED) {//如果是ＲＬ型
            root->rchild = right_rotate(root->rchild);//进行小右旋
        }
        root = left_rotate(root);/大左旋
    }else {
        return root;
    }
    root->color = RED;//红色上顶
    root->lchild->color = root->rchild->color = BLACK;//黑色下沉
    return root;
}
//调整方式从底层到上层

RBTNode *__insert(RBTNode *root, int key) {
    if (root == NIL) return init(key);
    if (root->key == key) return root;
    else if (root->key > key) {
        root->lchild = __insert(root->lchild, key);
    } else {
        root->rchild = __insert(root->rchild, key);
    }
    return insert_maintain(root);
}
RBTNode *insert(RBTNode *root, int key) {
    root = __insert(root, key);
    root->color = BLACK;//有可能变红
    return root;
}
RBTNode *predecessor(RBTNode *root) {//寻找前驱节点
    RBTNode *temp = root->lchild;
    while (temp->rchild !=NIL) temp = temp->rchild;
    return temp;
}
RBTNode *erase_maintain(RBTNode *root) {
    if (root->lchild->color != DOUBLE_BLACK && root->rchild->color != DOUBLE_BLACK) return root;
    if ((root->lchild->color == DOUBLE_BLACK && !has_red_child(root->rchild))||
        (root->rchild->color == DOUBLE_BLACK && !has_red_child(root->lchild))
       ) {
           root->color += 1;
           root->rchild->color -= 1;
           root->lchild->color -= 1;
           return root;

       }
    if (root->lchild->color == DOUBLE_BLACK) {
        if (root->rchild->color == RED) {
            root = left_rotate(root);
            root->color = BLACK;
            root->lchild->color = RED;
            return erase_maintain(root->lchild);
        }
        /*
        if (!has_red_child(root->rchild)) {
        root->color += 1;
        root->lchild->color -= 1;
        root->rchild->color -= 1;
        return root;
        }*/
        root->lchild->color = BLACK;
        if (root->rchild->rchild->color != RED) {
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = BLACK;
            root->rchild->rchild->color = RED;
        }
        root = left_rotate(root);
        root->color = root->lchild->color;
        root->lchild->color = root->rchild->color = BLACK;
    } else {
        if (root->lchild->color == RED) {
            root = right_rotate(root);
            root->color = BLACK;
            root->rchild->color = RED;
            return erase_maintain(root->rchild);
        }
        /*
        if (!has_red_child(root->lchild)) {
        root->color += 1;
        root->rchild->color -= 1;
        root->lchild->color -= 1;
        return root;
        }*/
        root->rchild->color = BLACK;
        if (root->lchild->lchild->color != RED) {
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = BLACK;
            root->lchild->lchild->color = RED;
        }
        root = right_rotate(root);
        root->color = root->rchild->color;
        root->rchild->color = root->lchild->color = BLACK;
    }
return root;
}


RBTNode *__erase(RBTNode *root, int key) {
    if (root == NIL) return NIL;
    if (root->key > key) {
        root->lchild = __erase(root->lchild,key);
    } else if (root->key < key) {
        root->rchild = __erase(root->rchild,key);
    } else {
        /*
        if (root->lchild == NIL && root->rchild == NIL) {
        NIL->color += root->color;
        free(root);
        return NIL;
    } else */
        if (root->lchild == NIL || root->rchild == NIL) {
            //0//1
            RBTNode *temp = (root->lchild == NIL ? root->rchild : root->lchild);
            temp->color += root->color;
            free(root);
            return temp;
        } else {
            RBTNode *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = __erase(root->lchild,temp->key);
        }
    }
    return erase_maintain(root);
}

RBTNode *erase(RBTNode *root, int key) {
    root = __erase(root,key);
    root->color = BLACK;
    return root;
}


void output(RBTNode *root) {
    if (root == NIL) return ;
    printf("(%d %d %d)",root->key, root->lchild->key, root->rchild->key);
    output(root->rchild);
    output(root->lchild);
}


int main() {
    srand(time(0));
    int op,val;
    RBTNode *root = NIL;
    #define MAX_OP 20 
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 5, val = rand() % 100;
        switch(op) {
            case 0:
            printf("delete val %d from RBT\n", val);
            break;
            case 1:
            case 2:
            case 3:
            case 4:{
                printf("insert val %d from RBT\n",val);
                root = insert(root,val);
            }
        }
        output(root);
    }
    return 0;
}
