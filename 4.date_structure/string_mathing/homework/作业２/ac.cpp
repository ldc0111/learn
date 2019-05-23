/*************************************************************************
	> File Name: ac.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月22日 星期二 21时25分33秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 26
//正确代码
typedef struct Node {
    int flag;
    struct Node *next[SIZE];
} Node;

typedef struct DATNode {
    int base, check, fail;
} DATNode;

Node *getNewNode() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    return p;
}

void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < SIZE; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}

int insert(Node *node, const char *str) {
    Node *p = node;
    int cnt = 0;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - 'a'] == NULL) {
            p->next[str[i] - 'a'] = getNewNode();
            cnt += 1;
        }
        p = p->next[str[i] - 'a'];
    }
    p->flag = 1;
    return cnt;
}

int getBase(Node *node, DATNode *trie) {
    int base = 1, flag = 0;
    while (!flag) {
        flag = 1;
        base += 1;//base是从2开始的
        for (int i = 0; i < SIZE; i++) {
            if (node->next[i] == NULL) continue;
            if (trie[base + i].check == 0) continue;
            flag = 0;
            break;
        }
    }
    return base;
}

int Transform(Node *node, DATNode *trie, int ind) {
    if (node == NULL) return 0;
    if (ind == 1) trie[ind].check = 0;
    if (node->flag) trie[ind].check = -trie[ind].check;
    trie[ind].base = getBase(node, trie);
    for (int i = 0; i < SIZE; i++) {
        if (node->next[i] == NULL) continue;
        trie[trie[ind].base + i].check = ind;
    }
    int cnt = ind;
    for (int i = 0; i < SIZE; i++) {
        if (node->next[i] == NULL) continue;
        int temp = Transform(node->next[i], trie, trie[ind].base + i);
        if (temp > cnt) cnt = temp;
    }
    return cnt;
}

int search(DATNode *trie, const char *str) {
    int p = 1;
    for (int i = 0; str[i]; i++) {
        int delta = str[i] - 'a';
        int check = abs(trie[trie[p].base + delta].check);
        if (check - p) return 0;
        p = trie[p].base + delta;
    }
    return trie[p].check < 0;
}

int has_child(DATNode *trie, int p, int i) {
    return abs(trie[trie[p].base + i].check) == p;
}

// 建立编号为ind节点的孩子的失败指针, 前提是编号为ind的节点失败指针已经建立了
void build_acdfs(DATNode *trie,int ind) {
    if(ind == 0) return ;//返回到根节点的失败指针
    if(trie[ind].fail == 0) build_acdfs(trie, abs(trie[ind].check));
    for (int i = 0; i < SIZE; i++) {
        int childind = trie[ind].base + i;
        if (!has_child(trie, ind, i)) continue;
        if (trie[childind].fail) continue;//失败指针已经建立不用再次建立
        int p = trie[ind].fail;
        while (p && !has_child(trie, p, i)) {
            if (trie[p].fail == 0) build_acdfs(trie,abs(trie[p].check));
            p = trie[p].fail;
        }
        if (p == 0) p = 1;
        else p = trie[p].base + i;
        trie[childind].fail = p;
        build_acdfs(trie,childind);
    }
}

int match(DATNode *trie, const char *str) {
    int cnt = 0;
    int p = 1, q;
    while (str[0]) {
        while (p && !has_child(trie, p, str[0] - 'a')) p = trie[p].fail;
        if (p == 0) p = 1;
        else p = trie[p].base + str[0] - 'a';
        q = p;
        while (q) {
            cnt += (trie[q].check < 0);
            q = trie[q].fail;
        }
        str++;
    }
    return cnt;
}

int main() {
    int n, cnt1 = 1, cnt2 = 0;
    char str[100];
    Node *root = getNewNode();
    scanf("%d", &n);
    while (n--) {
        scanf("%s", str);
        cnt1 += insert(root, str);
    }

    DATNode *trie = (DATNode *)calloc(sizeof(DATNode), cnt1 * 10);
    cnt2 = Transform(root, trie, 1);
    build_acdfs(trie, 1);
    for(int i = 0; i <= cnt2; i++) {
        printf("%d %d %d\n",i,trie[i].base,trie[i].check);
    }    
    scanf("%s", str);
    printf("matchcount : %d\n", match(trie, str));
    clear(root);
    return 0;
}
