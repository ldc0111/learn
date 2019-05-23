#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define swap(a,b){\
    __typeof(a) __temp = a; a = b; b = __temp;\
}


typedef struct sdata{
    int xu,wei,tiao;
}sdata;


typedef struct heap{
    sdata * data;
    int cnt,size;
}heap;


heap *init(int length){
    heap *h = (heap *)malloc(sizeof(heap));
    h->data = (sdata *)calloc(sizeof(sdata),(length + 1));
    h->cnt = 0;
    h->size = length;
    return h;
}


//按照位置和　序号设置优先级
void push(heap * h, sdata value){
    if(h->cnt >= h->size) return;
    h->data[++(h->cnt)] = value;
    int ind = h->cnt;
    while(ind > 1){
        if((h->data[ind].wei) > (h->data[ind >> 1].wei) || 
           (h->data[ind].wei == h->data[ind >> 1].wei && h->data[ind].tiao > h->data[ind >> 1].tiao)) break;
        swap(h->data[ind], h->data[ind >> 1]);
        ind >>= 1;
    }
    return ;
    
}
sdata top(heap * h){
    return h->data[1];
}
int empty(heap * h){
    return h->cnt <= 0;
}
void pop(heap * h){
    if(empty(h)) return ;
    h->data[1] = h->data[(h->cnt)--];
    int ind = 1;
    while(ind << 1 <= h->cnt){
        int temp = ind;
        if((h->data[temp].wei > h->data[ind << 1].wei) ||
          (h->data[temp].wei == h->data[ind << 1].wei && h->data[temp].tiao > h->data[ind << 1].tiao)) temp = ind << 1;
        if(((ind << 1 | 1) <= h->cnt) && ((h->data[temp].wei > h->data[ind << 1 | 1].wei) ||
          (h->data[temp].wei == h->data[ind << 1 | 1].wei && h->data[temp].tiao > h->data[ind << 1 | 1].tiao))) temp = ind << 1 | 1;
        if(temp == ind) break;
        swap(h->data[temp], h->data[ind]);
        ind = temp;
    }
    return ;
}
int count(heap *h){
    return h->cnt;
}


void output(heap *h){
    printf("arr = [\n");
    for(int i = 1; i <= h->cnt; i++){
        printf("%d xu= %d wei = %d tiao = %d\n",i,h->data[i].xu,h->data[i].wei,h->data[i].tiao);
    }
    printf("]\n\n");
}


int main(){
    int ti,n;
    scanf("%d", &ti);
    while(ti--){
        scanf("%d", &n);
        heap * h = init(n);
        int a,b;
        for(int i = 1; i <= n; i++){
            scanf("%d %d", &a,&b);
            sdata node;
            node.xu = i; node.wei = a;node.tiao = b;
            push(h,node);
        }
        //output(h);
        int ans = 0,time = 1, flag = 1;
        while(flag){
            if(time % 2 == 0 && count(h) == 1) flag = 0;
            if(time % 2 == 0){
                pop(h);
                //printf(" pop ");
                //output(h);
            }else{
                sdata node = top(h);
                node.wei += node.tiao;
                pop(h);
                push(h,node);
                //output(h);
            }
            time++;
        }
        printf("%d\n",top(h).wei);
    }
    return ;
}
/*
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int p, d;
    struct Node *lchild, *rchild;
} Node;

typedef struct Heap {
    Node **data;
    int size;
} Heap;

void init(Heap *h, int n) {
    h->data = (Node **)malloc(sizeof(Node *) * n);
    h->size = 0;
    return ;
}

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void push(Heap *h, Node *value) {
    h->data[h->size] = value;
    int current = h->size;
    int father = (current - 1) / 2;
    while (h->data[current]->p <= h->data[father]->p) {
        if (h->data[current]->p == h->data[father]->p && h->data[current]->d >= h->data[father]->d) break;
        swap(h->data[current], h->data[father]);
        current = father;
        father = (current - 1) / 2;
    }
    h->size++;
}

Node *top(Heap *h) {
     return h->data[0];
}

void update(Heap *h, int pos, int n) {
    int lchild = 2 * pos + 1, rchild = 2 * pos + 2;
    int min_value = pos;
    if (lchild < n && (h->data[lchild]->p < h->data[min_value]->p || 
        h->data[lchild]->p == h->data[min_value]->p && h->data[lchild]->d < h->data[min_value]->d)) {
        min_value = lchild;
    }
    if (rchild < n && (h->data[rchild]->p < h->data[min_value]->p || 
        h->data[rchild]->p == h->data[min_value]->p && h->data[rchild]->d < h->data[min_value]->d)) {
        min_value = rchild;
    }
    if (min_value != pos) {
        swap(h->data[pos], h->data[min_value]);
        update(h, min_value, n);
    }
}

void pop(Heap *h) {
    swap(h->data[0], h->data[h->size - 1]);
    h->size--;
    update(h, 0, h->size);
}

int heap_size(Heap *h) {
    return h->size;
}

void clear(Heap *h) {
    free(h->data);
    free(h);
}

int main() {
    int t, n, p, d;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
      scanf("%d", &n);
        Heap *heap = (Heap *)malloc(sizeof(Heap));
        init(heap, n);
        for (int i = 0; i < n; i++) {
            Node *node = (Node *)malloc(sizeof(Node));
            scanf("%d %d", &p, &d);
            node->p = p;
            node->d = d;
            push(heap, node);
        }
        int flag = 1;
        while (heap_size(heap) >= 1) {
            if (flag & 1) {
                heap->data[0]->p += heap->data[0]->d;
                update(heap, 0, heap_size(heap));
                flag += 1;
            } else {
                pop(heap);
                flag += 1;
            }
        }
        printf("%d\n", top(heap)->p);
    }
    return 0;
}*/


