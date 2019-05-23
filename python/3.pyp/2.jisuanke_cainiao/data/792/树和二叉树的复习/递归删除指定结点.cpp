#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 10000
typedef struct Node {
    char data;
    struct Node *lchild,*rchild;
}Node;

Node* init(int data){
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}
Node * build(char str[], int l, int r){
    if(l > r){
        return NULL;
    }
    Node *node = init(str[l]);
    int pos = -1, temp_prior = 0,prior = INF - 1;
    for(int i = l; i <= r; i++){
        int cur_prior = INF;
        switch(str[i]){
            case '(': temp_prior += 100; break;
            case ')': temp_prior -= 100; break;
            case ',': cur_prior = temp_prior + 1; break;
        }
        if(cur_prior <= prior){
            prior = cur_prior;
            pos = i;
        }
    }
    if(pos  == -1){
        node->lchild = build(str,l + 2, r - 1);
        return node;
    }else{
        node->lchild = build(str,l + 2,pos - 1);
        node->rchild = build(str,pos + 1,r - 1);
    }
    return node;
}

void priorder(Node *node){
    if(node == NULL) return ;
    printf("%c", node->data);
    priorder(node->lchild);
    priorder(node->rchild);
}
Node* find_clear(Node *node, char ch){
    if(node == NULL) return NULL;
    if(node->data == ch){
        clear(node);
        return NULL;
    }
    node->lchild = find_clear(node->lchild,ch);
    node->rchild = find_clear(node->rchild,ch);
    return node;
}

void clear(Node *node){
    if(node == NULL) return ;
    clear(node->lchild);
    clear(node->rchild);
    free(node);
    return ;
}
void ppriorder(Node *node){
    if(node == NULL) return ;
    printf("%c",node->data);
    if(node->lchild != NULL || node->rchild != NULL){
        printf("(");
        ppriorder(node->lchild);
        node->rchild != NULL && printf(",");
        ppriorder(node->rchild);
        printf(")");
    }
}
int main(){
    char str[55], ch;
    scanf("%[^\n]s",str);
    getchar();
    scanf("%c",&ch);
    Node *root = build(str, 0,strlen(str) - 1);
    //printf(" %c " ,root->rchild->data);
    //priorder(root);
    //printf("\n");
    root = find_clear(root,ch);
    ppriorder(root);
    printf("\n");
    return 0;
}