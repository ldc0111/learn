/*************************************************************************
	> File Name: acfuxi.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月20日 星期日 10时13分23秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 26;
const char BASE = 'a';

#define Node TrieNode

typedef struct TrieNode {
    int flag;
    struct TrieNode *fail;
    struct TrieNode **next;
} TrieNode, *Trie;

TrieNode* new_node() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    p->next = (Node **)calloc(sizeof(Node *), SIZE);
    return p;
}

void clear(Trie root) {
    if (root == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(root->next[i]);
    }
    free(root);
    return ;
}

void insert(Trie root, const char *str) {
    if (root == NULL) root = new_node();
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - BASE] == NULL) p->next[str[i] - BASE] = new_node();
        p = p->next[str[i] - BASE];
    }
    p->flag += 1;
    return ;
}

void build_automaton(Trie root) {
    if (root == NULL) return ;
    Node **queue = (Node **)malloc(sizeof(Node *) * 100003);
    int head = 0,tail = 0;
    queue[tail++] = root;
    while (head < tail) {
        Node *node = queue[head++];
        for (int i = 0; i < SIZE; i++) {
            if (node->next[i] == NULL) continue;
            Node *p = node->fail;
            while (p && p->next[i] == NULL) p = p->fail;
            if (p == NULL) node->next[i]->fail = root;
            else node->next[i]->fail = p->next[i];
            queue[tail++] = node->next[i];
        }
    }
    return ;
}

int match_count(Trie root, const char *text) {
    if (root == NULL) return 0;
    int cnt = 0;
    Node *p = root;
    for (int i = 0; text[i]; i++) {
        while (p && p->next[text[i] - BASE] == NULL) p = p->fail;
        if (p == NULL) p = root;
        else p = p->next[text[i] - BASE];
        Node *q = p;
        while (q) {
            if (q->flag) cnt += q->flag;
            q = q->fail;
        }
    }
    return cnt;
}

int main() {
    int n;
    Trie root = new_node();
    char str[100003];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        insert(root,str);
    }
    scanf("%s",str);
    build_automaton(root);
    printf("%d\n", match_count(root, str));
    return 0;
}
