/*************************************************************************
	> File Name: acxiansuohua.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月20日 星期日 11时10分56秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 26;
const char BASE = 'a';
const int MAX_SIZE = 200000;
const int MAX_LEN = 200000;
char str_buffer[200005];

typedef struct TrieNode {
    int count;
    struct TrieNode** childs;
    struct TrieNode* fail;
} TrieNode, *Trie;

TrieNode* new_node() {
    TrieNode *p = (TrieNode *)malloc(sizeof(TrieNode));
    p->childs = (TrieNode **)malloc(sizeof(TrieNode *) * SIZE);
    for (int i = 0; i < SIZE; i++) {
        p->childs[i] = NULL;
    }
    p->fail = NULL;
    p->count = 0;
    return p;
}

void clear(TrieNode *node) {
    if (node == NULL) return ;
    for (int i = 0; i < SIZE; i++) {
        if (node->childs[i] == NULL) continue;
        clear(node->childs[i]);
    }
    free(node->childs);
    free(node);
    return ;
}

void insert(TrieNode *trie, const char *buffer) {
    TrieNode *p = trie;
    for (int i = 0; i < strlen(buffer); i++) {
        if (p->childs[buffer[i] - BASE] == NULL) {
            p->childs[buffer[i] - BASE] = new_node();
        }
        p = p->childs[buffer[i] - BASE];
    }
    p->count++;
    return ;
}

void build_automaton(TrieNode *node) {
    TrieNode **queue = (TrieNode **)calloc(sizeof(TrieNode *), 200000);
    int head = 0,tail = 0;
    queue[tail] = node;
    while (head < tail) {
        TrieNode *now = queue[head++];
        for (int i = 0; i < SIZE; i++) {
            if (now->childs[i] == NULL) {
                if(now != node) now->childs[i] = now->fail->childs[i];
                continue;
            }
            TrieNode *p = (now->fail ? now->fail->childs[i] : node);
            //while (p && p->childs[i] == NULL) p = p->fail;
            if (p == NULL) p = node;
            now->childs[i]->fail = p;
            queue[tail++] = now->childs[i];
        }
        /*
        for (int i = 0; i < SIZE && now != node; i++) {
            if (now->childs[i]) continue;
            now->childs[i] = now->fail->childs[i];//？
        }
        */

    }
    free(queue);
}

int match_count(TrieNode *ac_tree, const char *str) {
    int ret = 0;
	TrieNode *p = ac_tree, *q;
	while (str[0]) {
        p = p->childs[str[0] - 'a'];
		//while (p && p->childs[str[0] - 'a'] == NULL) p = p->fail;
        //if (p == NULL) p = ac_tree;
        //else p = p->childs[str[0] - 'a'];
        q = p;
		while (q) ret += q->count, q = q->fail;
        if (p == NULL) p = ac_tree;
		str++;
	}
	return ret;
}

int main() {
    Trie root = new_node();
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        char pattern[MAX_LEN];
        scanf("%s", pattern);
        insert(root, pattern);
    }
    build_automaton(root);
    scanf("%s", str_buffer);
    printf("%d\n", match_count(root, str_buffer));
    //clear(root);
    return 0;
}
