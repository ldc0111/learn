#include <stdlib.h>
#include <string.h>
#include  <stdio.h>


int cnt = 0;
int f = 0;
typedef struct Node{
    char a;
    struct Node *lchild,*rchild;
}Node;

int find(Node *q,char a){
    for (int i = 0; i < cnt; i++) {
        //printf("q[%d]->a = %c, a= %c\n",i,q->a,a);
        if(q[i].a == a){
            return i;
        }
    }
    return -1;
}

void ppreorder(Node *node){
    if(node == NULL || cnt == 0) return ;
    printf("%c",node->a);
    
    if(node->lchild != NULL || node->rchild != NULL){
        printf("(");
        ppreorder(node->lchild);
        node->rchild != NULL && printf(",");
        ppreorder(node->rchild);
        printf(")");
    }
    return ;
}


int main(){
    Node root[100];
    char a[4];
    while (scanf("%s", a) != EOF) {
        if(a[0] == '^' && a[1] == '^') break;
        if(a[0] == '^' && a[1] != '^'){
            f = cnt;
            root[cnt].lchild = NULL;
            root[cnt].rchild = NULL;
            root[cnt++].a = a[1];
            continue;
        }
        root[cnt].a = a[1];
        root[cnt].lchild = NULL;
        root[cnt].rchild = NULL;
        int temp = find(root,a[0]);
        if(a[2] == 'L'){
            root[temp].lchild = &root[cnt];
        }else if (a[2] == 'R'){
            root[temp].rchild = &root[cnt];
        }
        cnt++;
    }
    
   // for(int i = 0; i < cnt; i++){
     //   printf("%c %p %p\n", root[i].a, root[i].lchild,root[i].rchild);
    //}
    ppreorder(&root[f]);
    printf("\n");
    return ;
}