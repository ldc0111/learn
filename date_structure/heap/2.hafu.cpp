/*************************************************************************
	> File Name: 2.hafu.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月31日 星期三 23时26分53秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define swap(a,b){\
    __typeof(a) __temp = a; a = b; b = __temp;\
}


typedef struct node{
    int key,freq;
    struct node *lchild; *rchild;
}node;

typedef struct heap{
    node *data;
    int size,cnt;
}heap;

heap * init(int n){
    heap *p = (heap * )malloc(sizeof(heap));
    p->data = (node *)malloc(sizeof(node) * (n + 1));
    p->data.lchlid = p->data.rchlid = NULL:
    p->cnt = 0;
    p->size = n;
    return p;
}
int empty(heap *h){
    return h->cnt <= 0;
}
void push(heap *h, node val){
    if(h->cnt >= h->size) return;
    h->data[++(h->cnt)] = val;
    int ind = h->cnt;
    while (ind > 1) {
        if (h->data[ind].freq > h->data[ind >> 1].freq) break;
        swap(h->data[ind], h->data[ind >> 1]);
        ind >>= 1;
    }
}
node top(heap *h){
    return h->data[1];
}
void  pop(heap *h){
    if(empty(h)) return ;
    h->data[1] = h->data[(h->cnt)--];
    int ind = 1;
    while((ind << 1) <= h->cnt){
        int temp = ind;
        if(h->data[temp].freq > h->data[ind << 1].freq) temp = ind << 1;
        if((ind << 1 | 1) <= h->cnt && h->data[temp].freq > h->data[ind << 1 | 1].freq) temp = ind << 1|1;
        if(temp == ind) break;
        swap(h->data[temp], h->data[ind]);
        ind = temp;
    }
    return ;
}




int main(){
    int n;
    scanf("%d", &n);
    heap *h = init(n);
    for(int i = 0; i < n; i++){
        char a[10];
        int b;
        scanf("%s%d",a,&b);
        node te;
        te.key = a[0];te.freq = b;
        push(h,te);
    }
    builld_haffman()
    return 0;
}
