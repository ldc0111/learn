/*************************************************************************
	> File Name: 2.build_tree.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年08月18日 星期日 21时35分59秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <iostream>
using namespace std;
typedef struct Node{
    int key;
    struct Node *lchild, *rchild;
}Node;

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild;
    return p;
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

Node *build(const char *str) {
   if (str == NULL) return NULL;
    Node *root = NULL,*p = NULL;
    stack<Node *> s;
    int k = 0;
    while (str[0]){
        switch(str[0]) {
            case '(':{
                s.push(p);
                k = 0;
            }break;
            case ',':{
                k = 1;

            }break;
            case ')':{
            }break;
            case ' ': break;
            default: {
                p = getNewNode(str[0]);
                if (root == NULL) root = p;
                if (s.empty()) break;
                if (k == 0) s.top()->lchild = p;
                else s.top()->rchild = p;
            }break;
        }
        str++;
    }
    return root;
}

void output(Node *root, const char *last_output) {
    if (root == NULL) return ;
    printf ("%c ", root->key);
    output(root->lchild, "");
    output(root->rchild, "");
    printf ("%s",last_output);
}

int main(){
    char str[100];
    Node *root = NULL;
    while (scanf("%[^\n]s",str) != EOF) {
        getchar();
        output(root = build(str), "\n");
        clear(root);
    }
    return 0;
}
