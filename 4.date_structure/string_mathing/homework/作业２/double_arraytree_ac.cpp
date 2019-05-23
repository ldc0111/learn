/*************************************************************************
	> File Name: double_arraytree_ac.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月20日 星期日 14时16分00秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define size 26

typedef struct Node {
    int flag;
    struct  Node *next[size];
} Node;

typedef struct DATNode{
    int base, check,fail;
}DATNode;


Node *getNewNode() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    return p;
}

void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < 26; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}

int insert(Node *node, const char *str){
    Node *p = node;
    int cnt = 0;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - 'a'] == NULL) {
            p->next[str[i] - 'a'] = getNewNode();
            cnt++;
        }
        p = p->next[str[i] - 'a'];
    }
    p->flag = 1;
    return cnt;
}
int getBase(Node *node, DATNode *trie) {
    int base =  0, flag = 0;
    while(!flag) {
        flag = 1;
        base += 1;
        for (int i = 0; i < size; i++) {
            if (node->next[i] == NULL) continue;
            if (trie[base + i].check == 0) continue;
            flag = 0;
            break;
        }
    }
    return base;
}


int Transform(Node *node, DATNode *trie, int ind) {
    if (ind == 1) trie[ind].check = 0;
    if(node->flag) trie[ind].check = -trie[ind].check;
    trie[ind].base = getBase(node, trie);
    for (int i = 0; i < size; i++) {
        if(node->next[i] == NULL) continue;
        trie[trie[ind].base + i].check = ind;
    }
    int ret = ind;
    for (int i = 0; i < size; i++) {
        if (node->next[i] == NULL) continue;
        int temp = Transform(node->next[i], trie, trie[ind].base + i);
        if(temp > ret) ret = temp;
    }
    return ret;
}


int search(DATNode *trie, const char *str) {
    int p = 1;
    for (int i = 0; str[i]; i++) {
        int delta = str[i] - 'a';
        int check = abs(trie[trie[p].base + delta].check);
        if(check - p) return 0;
        p = trie[p].base + delta;
    }
    return trie[p].check < 0;
}

int has_child(DATNode *trie, int p, int i) {
    return abs(trie[trie[p].base + i].check) == p;
}

//注意第一个节点的check的值是1 第一个节点的失败指针是0
void build_acdfs(DATNode *trie,int ind) {
    if(ind == 0) return ;//返回到根节点的失败指针
    if(trie[ind].fail == 0) build_acdfs(trie, abs(trie[ind].check));
    for (int i = 0; i < size; i++) {
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


int match_count(DATNode *trie, const char *str) {
    int ret = 0;
    int p = 1, q;
    while (str[0]) {
        while (p && !has_child(trie,p,str[0] - 'a')) p = trie[p].fail;
        if (p == 0) p = 1;
        else p = trie[p].base + str[0] - 'a';
        q = p;
        while (q) {
            ret += (trie[q].check < 0);
            q = trie[q].fail;
        }
        str++;
    }
    return ret;
}

int main() {
    int n, cnt = 1, cnt1 = 0, cnt2 = 0;
    char str[10000];
    Node *root = getNewNode();
    scanf("%d", &n);
    while (n--) {
        scanf("%s", str);
        cnt1 += insert(root, str);
    }
    DATNode *trie = (DATNode *)calloc(sizeof(DATNode), cnt1 * 10);
    cnt2 = Transform(root, trie, 1);
    build_acdfs(trie,1);
    scanf("%s",str);
    printf("%d\n",match_count(trie,str));
    /*
    printf("%d\n\n",cnt2);
    */
    /*
    for(int i = 0; i <= cnt2; i++) {
        printf("%d %d %d\n",i,trie[i].base,trie[i].check);
    }
    */
   /* 
    while (scanf("%s", str) != EOF) {
        printf("search %s = %d\n", str, search(trie,str));
    }
    */
    return 0;
}

