#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *lchild, *rchild, *f;
}Node;

Node* init(int key, Node *f) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = NULL;
    p->rchild = NULL;
    p->f = f;
    return p;
}

Node* insert(Node *root, int key) {
    if (root == NULL) return init(key, root);
    //if (root->key == key) return root;
    if (root->key > key) root->lchild = insert(root->lchild, key);
    else if(root->key < key) root->rchild = insert(root->rchild, key);
    return root;
}

Node* search(Node *root, int key) {
    if (root == NULL || root->key == key) return root;
    else if (root->key > key) {
        return search(root->lchild, key);
    }else {
        return search(root->rchild, key);
    }
    return NULL;
}

void output(Node *root) {
    if (root == NULL) return ;
    output(root->lchild);
    printf("%d ", root->key);
    output(root->rchild);
    return ;
}

void clear(Node *node) {
    if (node != NULL) {
        if (node->lchild != NULL) {
            clear(node->lchild);
        }
        if (node->rchild != NULL) {
            clear(node->rchild);
        }
        free(node);
    }
}

int main() {
    Node *binarytree = NULL;
    init(100, binarytree);
    binarytree = NULL;
    int n, a;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        binarytree = insert(binarytree, a);
   }
    scanf("%d", &a);
    if (search(binarytree, a) != NULL) {
        printf("search success!\n");
    } else {
        printf("search failed!\n");
    }
    output(binarytree);
    printf("\n");
    clear(binarytree);
    return 0;
}