/*************************************************************************
	> File Name: 3.double_arraytree_ac_dfs.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月23日 星期三 16时45分26秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define BASE 'a'
#define SIZE 26

typedef struct Node{
    int flag;
    struct Node *next[SIZE],*fail;
}Node;

Node *getNewNode() {
    return (Node *)calloc(sizeof(Node), 1);
}

int insert(Node *node, const char *str) {
    Node *p = node;
    int cnt = 0,ind = 0;
    while (str[0]) {
        ind = str[0] - BASE;
        if (p->next[ind] == NULL) {
            p->next[ind] = getNewNode();
            cnt++;
        }
        p = p->next[ind];
        str++;
    }
    p->flag= 1;
    return cnt;
}
int search(Node *node, const char *str) {
    Node *p = node;
    int ind = 0;
    while (p && str[0]) {
        ind = str[0] - BASE;
        p=p->next[ind];
        str++;
    }
    return (p && p->flag);
}
void build_ac(Node *root) {
    #define MAX_N 1000
    if (root == NULL) return ;
    Node **queue = (Node **)malloc(sizeof(Node*) * MAX_N);
    int head = 0,tail = 0;
    queue[tail++] = root;
    while (head < tail) {
        Node *new_node = queue[head++];
        for (int i = 0; i < SIZE; i++) {
            if (new_node->next[i] == NULL) continue;
            Node *p = new_node->fail;
            while (p && p->next[i] == NULL) p = p->fail;
            if (p == NULL) new_node->next[i]->fail = root;
            else new_node->next[i]->fail = p->next[i];
            queue[tail++] = new_node->next[i];
        }
    }
    #undef MAX_N
    return ;
}
int search_ac(Node *root, const char *str) {
    if(root == NULL) return 0;
    Node *p = root;
    int cnt = 0;
    for (int i = 0; str[i]; i++) {
        while (p && p->next[str[i] - BASE] == NULL) p = p->fail;
        if(p == NULL) p = root;
        else p = p->next[str[i] - BASE];
        Node *q = p;
        while (q) {
            cnt += q->flag;
            q = q->fail;
        }
    }
    return cnt;
}

void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}
int main() {
    Node *root = getNewNode();
    int n = 0;
    char str[50];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        insert(root,str);
    }
    build_ac(root);
    while (scanf("%s", str)) {
        printf("search %s = %d\n", str, search_ac(root, str));
    }
    clear(root);
    return 0;
}

