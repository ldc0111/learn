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
    struct TrieNode *father;
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
        p->next[str[i]-BASE]->father = p;
        p = p->next[str[i] - BASE];
    }
    p->flag++;
    return ;
}

void build_automaton(TrieNode *node) {
    if (node == NULL) return ;
    if (node->fail == NULL) build_automaton(node->father);
    for (int i = 0; i < SIZE; i++) {
        if (node->next[i] == NULL) continue;
        if (node->next[i]->fail) continue;
        Node *p = node->fail, *pre_p = node;
        while (p && p->next[i] == NULL) {
            if (p->fail == NULL) build_automaton(p->father);
            pre_p = p;
            p = p->fail;
        }
        if (p == NULL) p = pre_p;
        else p = p->next[i];
        node->next[i]->fail = p;
        build_automaton(node->next[i]);
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
            cnt += q->flag;
            q = q->fail;
        }
    }
    return cnt;
}

int main() {
    int n;
    Trie root = new_node();
    char str[200005];
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