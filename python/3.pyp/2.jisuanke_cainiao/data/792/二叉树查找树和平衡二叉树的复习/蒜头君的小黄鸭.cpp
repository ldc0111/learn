#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node{
    int key,size;
    struct Node *lchild, *rchild;
}Node;

Node *init(int val) {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    p->key = val;
    p->size = 1;
    return p;
}

void clear(Node *node) {
    if (node == NULL) return ;
    clear(node->lchild);
    clear(node->rchild);
    free(node);
    return ;
}

Node *insert(Node *node, int val) {
    if(node == NULL) return init(val);
    node->size++;
    if (node->key > val) {
        node->lchild = insert(node->lchild, val);
    }else {
        node->rchild = insert(node->rchild,val);
    }
    return node;
}
Node *pressor(Node *node) {
    Node *temp = node->lchild;
    while (temp->rchild != NULL) temp = temp->rchild;
    return temp;
}

Node *delete(Node *node,int val) {
    if(node == NULL) return NULL;
    node->size--;
    if(node->key > val) {
        node->lchild = delete(node->lchild, val);
    } else if (node->key < val) {
        node->rchild = delete(node->rchild, val);
    } else {
        if(node->lchild == NULL && node->rchild == NULL) {
            free(node);
            return NULL;
        } else if (node->lchild == NULL || node->rchild == NULL) {
            Node *temp = (node->lchild == NULL ? node->rchild : node->lchild);
            free(node);
            return temp;
        } else {
            Node *temp = pressor(node);
            node->key = temp->key;
            node->lchild = delete(node->lchild, temp->key);
        }
    }
    return node;
}

void inorder(Node *node) {
    if(node == NULL) return ;
    inorder(node->lchild);
    printf("%d %d\n", node->key, node->size);
    inorder(node->rchild);
}
int query(Node *node, int k) {
    int flag = (node->lchild == NULL ? 0 : node->lchild->size) + 1;
    if(flag == k) return node->key;
    else if (flag > k) return query(node->lchild, k);
    else return query(node->rchild,k - flag);
}

int main() {
    int n,m,val;
    Node *root = NULL;
    char flag[100];
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
       	root = insert(root,val);
    }
    //inorder(root);
    for (int i = 0; i < m; i++) {
        memset(flag,0,sizeof(flag));
        scanf("%s %d",flag, &val);
        if(strcmp(flag,"query") == 0) {
            val = root->size - val + 1;
            //printf("%d", val);
            printf("%d\n",query(root,val));
        }else if (strcmp(flag,"delete") == 0) {
        	root = delete(root,val);
        } else {
            root = insert(root,val);
        }
    }
    return 0;
}