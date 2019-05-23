#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef struct SBTNode {
    int data, size;
    struct SBTNode *lchild, *rchild, *father;
}SBTNode;

SBTNode* init(int init_data, int init_size, SBTNode *init_father);

SBTNode *NIL;

void init_NIL() {
    NIL = (SBTNode *)malloc(sizeof(SBTNode));
    NIL->data = 0;
    NIL->size = 0;
    NIL->lchild = NIL;
    NIL->rchild = NIL;
    NIL->father = NULL;
}

SBTNode* init(int init_data, int init_size, SBTNode *init_father) {
    SBTNode *node = (SBTNode *)malloc(sizeof(SBTNode));
    node->data = init_data;
    node->size = init_size;
    node->lchild = NIL;
    node->rchild = NIL;
    node->father = init_father;
    return node;
}

SBTNode * left_rotate(SBTNode * node) {
    SBTNode *temp = node->rchild;
    node->rchild = temp->lchild;
    temp->lchild->father = node;
    temp->lchild = node;
    temp->father = node->father;
    node->father = temp;
    temp->size = node->size;
    node->size = node->lchild->size + node->rchild->size + 1;
    return temp;
}

SBTNode * right_rotate(SBTNode * node) {
    SBTNode *temp = node->lchild;
    node->lchild = temp->rchild;
    temp->rchild = node;
    temp->rchild = node;
    temp->father = node->father;
    node->father = temp;
    temp->size = node->size;
    node->size = node->lchild->size + node->rchild->size + 1;
    return temp;
}

SBTNode * maintain(SBTNode * node, int flag) {
    if (flag == 0) {
        if (node->lchild->lchild->size > node->rchild->size) {
            node = right_rotate(node);
        } else if (node->lchild->rchild->size > node->rchild->size) {
            node->lchild = left_rotate(node->lchild);
            node = right_rotate(node);
        } else {
            return node;
        }
    } else {
        if (node->rchild->rchild->size > node->lchild->size) {
            node = left_rotate(node);
        } else if (node->rchild->lchild->size > node->lchild->size){
            node->rchild = right_rotate(node->rchild);
            node = left_rotate(node);
        } else {
            return node;
        }
    }
    node->lchild = maintain(node->lchild, 0);
    node->rchild = maintain(node->rchild, 1);
    node = maintain(node, 0);
    node = maintain(node, 1);
    return node; 
}

SBTNode * insert(SBTNode * node, int value) {
    node->size++;
    if (value > node->data) {
        if (node->rchild == NIL) {
            node->rchild = init(value, 1, node);
        } else {
            node->rchild = insert(node->rchild, value);
        }
    } else {
        if (node->lchild == NIL) {
            node->lchild = init(value, 1, node);
        } else {
            node->lchild = insert(node->lchild, value);
        }
    }
    return maintain(node, value > node->data);
}

SBTNode * search(SBTNode * node, int value) {
    if (node == NIL || node->data == value) {
        return node;
    } else if (value > node->data) {
        if (node->rchild == NIL) {
            return NIL;
        } else {
            return search(node->rchild, value);
        }
    } else {
        if (node->lchild == NIL) {
            return NIL;
        } else {
            return search(node->lchild, value);
        }
    }
}

SBTNode *insert_node(SBTNode * node, int value) {
    if (node == NULL) {
        node = init(value, 1, NULL);
        return node;
    }
    if (search(node, value) != NIL) {
        return node;
    }
    return insert(node, value);
}


SBTNode * predecessor(SBTNode * node) {
    SBTNode * temp = node->lchild;
    while (temp != NIL && temp->rchild != NIL) {
        temp = temp->rchild;
    }
    return temp;
}

SBTNode * successor(SBTNode * node) {
    SBTNode * temp = node->rchild;
    while (temp != NIL && temp->lchild != NIL) {
        temp = temp->lchild;
    }
    return temp;
}

void remove_node(SBTNode * delete_node) {
    SBTNode * temp = NIL;
    if (delete_node->lchild != NIL) {
        temp = delete_node->lchild;
        temp->father = delete_node->father;
        delete_node->lchild = NIL;
    }
    if (delete_node->rchild != NIL) {
        temp = delete_node->rchild;
        temp->father = delete_node->father;
        delete_node->rchild = NIL;
    }
    if (delete_node->father->lchild == delete_node) {
        delete_node->father->lchild = temp;
    } else {
        delete_node->father->rchild = temp;
    }
    temp = delete_node;
    while (temp != NULL) {
        temp->size--;
        temp = temp->father;
    }
    delete_node->lchild = NIL;
    delete_node->rchild = NIL;
    free(delete_node);
}

int delete_tree(SBTNode *node, int value) {
    SBTNode * delete_node, * current_node;
    current_node = search(node, value);
    if (current_node == NIL) {
        return ERROR;
    }
    if (current_node->lchild != NIL) {
        delete_node = predecessor(current_node);
    } else if (current_node->rchild != NIL) {
        delete_node = successor(current_node);
    } else {
        delete_node = current_node;
    }
    current_node->data = delete_node->data;
    remove_node(delete_node);
    return OK;
}
// 可在以下自行定义遍历函数
void inorder(SBTNode *node) {
    if (node == NIL) return ;
    inorder(node->lchild);
    printf("%d ",node->data);
    inorder(node->rchild);
    return ;
}

void clear(SBTNode *node) {
    if (node != NIL) {
        if (node->lchild != NIL) {
            clear(node->lchild);
        }
        if (node->rchild != NIL) {
            clear(node->rchild);
        }
        free(node);
    }
}

int main() {
    init_NIL();
    SBTNode *binarytree = NULL;
    int n = 0,a;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        binarytree = insert_node(binarytree, a);
    }
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        if (delete_tree(binarytree,a)) {
            printf("delete success!\n");
        } else {
            printf("delete failed!\n");
        }
    }
    
    inorder(binarytree);    
    clear(binarytree);
    return 0;
}