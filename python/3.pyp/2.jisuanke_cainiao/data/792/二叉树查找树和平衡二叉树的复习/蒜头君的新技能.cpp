#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Node{
    int data;
    struct Node *lchild,*rchild;
}Node;

Node *init(int val) {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    p->data = val;
    return p;
}
Node *insert(Node *node, int val) {
    if (node == NULL) return init(val);
    else if (node->data == val) return node;
    else if (node->data > val) {
        node->lchild = insert(node->lchild,val);
    } else {
        node->rchild = insert(node->rchild,val);
    }
    return node;
}

void inorder(Node *node) {
    if (node == NULL) return ;
    inorder(node->lchild);
    printf("%d", node->data);
    if (node->lchild == NULL) {
        printf("(#,");
    } else {
        printf("(%d,",node->lchild->data);
    }
    if (node->rchild == NULL) {
        printf(" #)\n");
    } else {
        printf(" %d)\n",node->rchild->data);
    }
    inorder(node->rchild);
}

int main() {
    int n,a;
    Node *root = NULL;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        root = insert(root,a);
    }
    inorder(root);
    return 0;
}