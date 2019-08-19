/*************************************************************************
	> File Name: 3.hafuman.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年08月18日 星期日 22时26分39秒
 ************************************************************************/

#include <iostream>
#include <string.h>
using namespace std;


typedef struct Node{
    int key,freq;
    struct Node *lchild, *rchild;
}Node;


Node *getNewNode(int key, int freq) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->freq = freq;
    p->lchild = p->rchild = NULL;
    return p;
}
int swap_node(Node **p, Node **q) {
    Node *temp = *p;
    *p = *q;
    *q = temp;
    return 1;
}

Node* build_huffman(Node **arr,int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 2 ; j++) {
            if (arr[j]->freq < arr[n - i - 1]->freq) {
                swap_node(arr + j, arr + n - i - 1);
            }
            if (arr[j]->freq < arr[n - i - 2]->freq) {
                swap_node(arr + j,arr + n - i - 2);
            }
        }
        Node *temp = getNewNode(0,arr[n - i - 1]->freq + arr[n - i - 2]->freq);
        temp->lchild = arr[n - i - 1];
        temp->rchild = arr[n - i - 2];
        arr[n - i - 2] = temp;
    }
    return arr[0];
}




void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
}



void extract_code(Node *root, char (*code)[20], int k, char *buff) {
    buff[k] = 0;
    if (root->key) {
        strcpy(code[root->key], buff);
        return ;    
    }
    buff[k] = '0';
    extract_code(root->lchild, code, k + 1, buff);
    buff[k] = '1';
    extract_code(root->rchild, code, k + 1, buff);
    return ;
}



int main() {
    int n;
    scanf("%d", &n);
    Node **arr = (Node **)malloc(sizeof(Node *) *n);
    Node *root;
    for (int i = 0; i < n; i++) {
        char key[10];
        int freq;
        scanf("%s%d", key,&freq);
        arr[i] = getNewNode(key[0],freq);
    }
    root = build_huffman(arr,n);
    
}
