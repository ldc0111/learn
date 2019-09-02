/*************************************************************************
	> File Name: 3.rbttree.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年07月09日 星期二 20时18分09秒
 ************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
        int key,color;
        struct Node *lchild, *rchild;

}Node;

Node *NIL;
__attribute__((constructor))
void init_NIL(){
        NIL = (Node*)malloc(sizeof(Node));
        NIL->key = 0;
        NIL->color = 1;
        NIL->lchild = NIL->rchild = NIL;

}

Node *init(int key) {
        Node *p = (Node *)malloc(sizeof(Node));
        p->key = key;
        p->color = 0;
        p->lchild = p->rchild = NIL;
        return p;

}

int has_red_child(Node *node) {
        return (node->lchild->color == 0 || node->rchild->color == 0);

}

Node *left_rotate(Node *node) {
        Node *temp = node->rchild;
        node->rchild = temp->lchild;
        temp->lchild = node;
        return temp;

}

Node *right_rotate(Node *node) {
        Node *temp = node->lchild;
        node->lchild = temp->rchild;
        temp->rchild = node;
        return temp;

}
Node *insert_maintain(Node *node) {
        if (!has_red_child(node)) return node;
    else if (node->lchild->color == 0 && node->rchild->color == 0) {
                if (!has_red_child(node->lchild) && !has_red_child(node->rchild)) return node;
            
    }else if (node->lchild->color == 0 && has_red_child(node->lchild)){
        if (node->lchild->rchild->color == 0) {
                        node->lchild = left_rotate(node->lchild);
                    
        }
                node = right_rotate(node);
            
    }else if (node->rchild->color == 0 && has_red_child(node->rchild)) {
        if (node->rchild->lchild->color == 0) {
                        node->rchild = right_rotate(node->rchild);
                    
        }
                node = left_rotate(node);
            
    } else {
                return node;
            
    }
        node->color = 0;
        node->lchild->color = node->rchild->color = 1;
        return node;

}

Node *__insert(Node *node, int key) {
        if (node == NIL) return init(key);
        else if (node->key == key) return node;
        else if (node->key > key) node->lchild = __insert(node->lchild, key);
        else node->rchild = __insert(node->rchild, key);
        return insert_maintain(node);

}

Node *insert(Node *node, int key){
        node = __insert(node, key);
        node->color = 1;
        return node;

}

Node *erase_maintain(Node *node) {
            #define maintain(a,b,c,d) ({\
                                               if (node->b->color == 0) {\
                                                                                    node = c(node);\
                                                                                    node->color = 1;\
                                                                                    node->a->color = 0;\
                                                                                    node->a = erase_maintain(node->a);\
                                                                                    return node;\
                                                                                }\
                                               node->a->color = 1;\
                                               if (!has_red_child(node->b)) {\
                                                                                        node->color += 1;\
                                                                                        node->b->color -= 1;\
                                                                                        return node;\
                                                                                    }else if (node->b->b->color != 0) {\
                                                                                                                                  node->b = d(node->b);\
                                                                                                                                  node->b->color = 1;\
                                                                                                                                  node->b->b->color = 0;\
                                                                                                                              }\
                                               node = c(node);\
                                               node->color = node->a->color;\
                                               node->lchild->color = node->rchild->color = 1;\
                                           })
        if (node->lchild->color != 2 && node->rchild->color != 2) return node;
    else if (node->lchild->color == 2){
                maintain(lchild, rchild, left_rotate, right_rotate);
            
    }else {
                maintain(rchild, lchild, right_rotate, left_rotate);
            
    }
        return node;

}

Node *pressor(Node *node) {
        Node *temp = node->lchild;
        while (temp->rchild != NIL) temp = temp->rchild;
        return temp;

}

Node *__erase(Node *node, int key) {
        if (node == NIL) return node;
        else if (node->key > key) node->lchild = __erase(node->lchild, key);
        else if (node->key < key) node->rchild = __erase(node->rchild, key);
    else {
        if (node->lchild == NIL || node->rchild == NIL) {
                        Node *temp = (node->lchild != NIL ? node->lchild : node->rchild);
                        temp->color += node->color;
                        free(node);
                        return temp;
                    
        }else {
                        Node *temp = pressor(node);
                        node->key = temp->key;
                        node->lchild = __erase(node->lchild, temp->key);
                    
        }
            
    }
        return erase_maintain(node);

}

Node *erase(Node *node, int key) {
        node = __erase(node,key);
        node->color = 1;
        return node;

}
void clear(Node *node) {
        if (node == NIL) return ;
        clear(node->lchild);
        clear(node->rchild);
        free(node);
        return ;

}

void output(Node *root) {
    if (root == NIL) return ;
    output(root->lchild);
    printf("%d %d %d %d\n", root->key, root->color, root->lchild->key, root->rchild->key);
    output(root->rchild);
}

int main() {
    Node *root = NIL;
    int a, b;
    while (scanf("%d%d",&a,&b)!= EOF) {
        if(a == 1) {
            root = insert(root,b);
        } else if (a == 2) {
            root = erase(root,b);
        } else {
            output(root);
        }
    }
    return 0;

}

