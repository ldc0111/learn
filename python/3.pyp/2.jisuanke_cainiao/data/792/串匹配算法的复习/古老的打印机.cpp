#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define base 'a'
#define count 26
#define max(a,b) ((a) > (b) ? (a) : (b))
typedef struct Node{
    int flag;
    struct Node **next;
}Node;

Node *get_new_node(){
    Node *p = (Node *)calloc(sizeof(Node), 1);
    p->next = (Node **)calloc(sizeof(Node), count);
    return p;
}

void clear(Node *root){
    if (root == NULL) return ;
    for (int i = 0; i < count; i++) {
        clear(root->next[i]);
    }
    free(root->next);
    free(root);
    return ;
}
void insert(Node *root, const char *str) {
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - base] == NULL) p->next[str[i] - base] = get_new_node();
        p = p->next[str[i] - base];
    }
    //这一步没啥用
    p->flag = 1;
    return ;
}
void  preorst(Node *root, int *cnt) {
    if (root == NULL) return ;
    for (int i = 0; i < count; i++) {
        if (root->next[i] == NULL) continue;
        (*cnt)++;
        preorst(root->next[i], cnt);
    }
    (*cnt)++;
    return ;
}


int main(){
    int n = 0;
    int cnt = 0;
    int stmax = 0;
    Node *root = get_new_node();
    char str[100];
    while(scanf("%d", &n) != EOF) {
        cnt = 0;
        stmax = 0;
        root = get_new_node();
        
        for (int i = 0; i < n; i++) {
            scanf("%s", str);
            stmax = max(stmax,strlen(str));
            insert(root,str);
        }
        preorst(root,&cnt);
        if (n == 0){
            printf("0\n");
        } else {
            printf("%d\n", cnt + n - stmax -  1);
        }
        clear(root);
    }
    return 0;
}