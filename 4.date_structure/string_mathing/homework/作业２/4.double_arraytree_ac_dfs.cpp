/*************************************************************************
	> File Name: 4.double_arraytree_ac_dfs.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月23日 星期三 17时45分13秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define BASE 'a'
#define SIZE 26

typedef struct Node{
    int flag;
    struct Node *next[SIZE];
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


void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}
///////////////////////////////////////////
typedef struct DANode{
    int base,check,fail;
}DANode;

DANode *getNewDANode(int n){
    return (DANode *)calloc(sizeof(DANode), n);
}
int get_base(Node *node, DANode *data) {
    int base = 1,flag = 0;
    while (!flag) {
        base++;
        flag = 1;
        for (int i = 0; i < SIZE; i++) {
            if (node->next[i] == NULL) continue;//没有这个儿子节点返回
            if (data[base + i].check == 0) continue;//没有信息返回
            //运行到这一行的条件是,有data[base + i].check 有信息也就是有父亲节点
            //所以我们把flag置为0,当flag位0时表示可以进行下一次循环,然后我们跳出for循环
            //因为已经没有必要继续下去了,以这个base为下标的不能存储所有儿子节点
            flag = 0;
            break;
        }
    }
    return base;
}



void  build(Node *node, DANode * data, int ind) {
    if(node == NULL) return ;
    if (node->flag) data[ind].check = -data[ind].check;
    //表示儿子独立成词
    data[ind].base = get_base(node, data);
    for (int i = 0; i < SIZE; i++) {
        if (node->next[i] == NULL) continue;
        data[data[ind].base + i].check = ind;
        //儿子节点记录父亲节点的下标信息
    }
    for (int i = 0; i < SIZE; i++) {
        if (node->next[i] == NULL) continue;
        build(node->next[i],data,data[ind].base + i);
    }
    return ;
}

int searchD(DANode *data, const char *str) {
    int p = 1;
    for (int i = 0; str[i]; i++) {
        int delta = str[i] - BASE;
        //节点是那个字符的信息
        int check = abs(data[data[p].base + delta].check);
        //儿子节点的父亲
        if (check - p) return 0;
        //如果父亲是这个节点的儿子,则check等于p,if条件位0,
        p = data[p].base + delta;
        //坐标后移
    }
    return data[p].check < 0;
}
int has_child(DANode *trie, int p, int i) {
    return abs(trie[trie[p].base + i].check) == p;
}

void build_ac(DANode *trie, int cnt) {
    int *queue = (int *)calloc(sizeof(int), cnt + 5);
    int head = 0, tail = 0;
    queue[tail++] = 1;
    while (head < tail) {
        int now = queue[head++];
        for (int i = 0; i < SIZE; i++) {
            if (!has_child(trie, now, i)) continue;
            int p = trie[now].fail;
            while (p && !has_child(trie, p, i)) p = trie[p].fail;
            if (p == 0) p = 1;
            else p = trie[p].base + i;
            trie[trie[now].base + i].fail = p;
            queue[tail++] = trie[now].base + i;
        }
    }
}
// 建立编号为ind节点的孩子的失败指针, 前提是编号为ind的节点失败指针已经建立了
void build_acdfs(DANode *trie,int ind) {
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
int match(DANode *trie, const char *str) {
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
    Node *root = getNewNode();
    int n = 0,cnt1 = 1;
    char str[50];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        cnt1 += insert(root,str);
    }
    DANode *trie = getNewDANode(cnt1 * 10);
    build(root,trie,1);
    build_ac(trie, cnt1 * 10);
    //build_acdfs(trie,1);
    while (scanf("%s", str)) {
        printf("search %s = %d\n", str, match(trie, str));
    }
    clear(root);
    return 0;
}


