/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define swap(a,b){\
  __typeof(a) __temp = a; a = b; b = __temp;\
}


typedef struct node{
    int xu,wei,su;
}node;


typedef struct heap{
    node *data;
    int cnt,size;
}heap;

heap * init(int n){
    heap * h = (heap *)malloc(sizeof(heap));
    h->data = (node *)malloc(sizeof(node) * (n + 1));
    h->cnt = 0;
    h->size = n;
    return h;
}
int empty(heap *h){
    return h->cnt <= 0;
}

void pop(heap *h){
    if(empty(h)) return ;
    h->data[1] = h->data[(h->cnt)--];
    int ind = 1;
    while((ind << 1)<= h->cnt){
        int temp = ind;
        if(h->data[temp].wei < h->data[ind << 1].wei || 
           h->data[temp].wei == h->data[ind << 1].wei && h->data[temp].xu > h->data[ind << 1].xu) temp = ind << 1;
        if((ind << 1 | 1) <= h->cnt && h->data[temp].wei < h->data[ind << 1 | 1].wei || 
           h->data[temp].wei == h->data[ind << 1 | 1].wei && h->data[temp].xu > h->data[ind << 1 | 1].xu) temp = ind << 1 | 1;
        if(temp == ind) break;
        swap(h->data[temp],h->data[ind]);
        ind = temp;
    }
}



void push(heap *h,node val){
    if(h->cnt >= h->size) return;
    h->data[++(h->cnt)] = val;
    int ind = h->cnt;
    while(ind > 1){
        if(h->data[ind].wei < h->data[ind >> 1].wei || 
           h->data[ind].wei == h->data[ind >> 1].wei && h->data[ind].xu > h->data[ind >> 1].xu)  break;
        swap(h->data[ind], h->data[ind >> 1]);
        ind >>= 1;
    }
}
node top(heap * h){
    return h->data[1];
}


void output(heap *h){
    printf("arr = [\n");
    for(int i = 1; i <= h->cnt; i++){
        printf("%d xu= %d wei = %d tiao = %d\n",i,h->data[i].xu,h->data[i].wei,h->data[i].su);
    }
    printf("]\n\n");
}
void weihu(heap *h){
    //for(int i = 1; i <= h->cnt; i++) h->data[i].wei += h->data[i].su;
    
    for(int i = h->cnt >> 1; i  >= 1; i--){
        int ind = i;
        while((ind << 1)<= h->cnt){
            int temp = ind;
            if(h->data[temp].wei < h->data[ind << 1].wei || 
               h->data[temp].wei == h->data[ind << 1].wei && h->data[temp].xu > h->data[ind << 1].xu) temp = ind << 1;
            if((ind << 1 | 1) <= h->cnt && h->data[temp].wei < h->data[ind << 1 | 1].wei || 
               h->data[temp].wei == h->data[ind << 1 | 1].wei && h->data[temp].xu > h->data[ind << 1 | 1].xu) temp = ind << 1 | 1;
            if(temp == ind) break;
            swap(h->data[temp],h->data[ind]);
            ind = temp;
        }
    }
    return ;
}

int main(){
    int ti = 0,k = 1;
    scanf("%d", &ti);
    
    while(k <= ti){
        int n = 0;
        scanf("%d", &n);
        heap *h = init(n);
        for(int i = 1; i <= n; i++){
            int a,b;
            scanf("%d %d", &a,&b);
            node te;
            te.xu = i; te.wei = a; te.su = b;
            push(h,te);
        }
        //output(h);
        //pop(h);
        //output(h);
        printf("Case #%d:\n",k);
        for(int i = 0; i < n; i++){
            node tt = top(h);
            printf("%d", tt.xu);
            i  != n - 1 && printf(" ");
            
            pop(h);
            weihu(h);
            //output(h);
        }
        printf("\n");
        
        k++;
    }
    return 0;
}*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define swap(a,b){\
  __typeof(a) __temp = a; a = b; b = __temp;\
}

typedef struct Node{
    int wei,xu;
}Node;
typedef struct heap{
    Node * data;
    int cnt,size;
}heap;

heap * init(int n){
    heap * h = (heap *)malloc(sizeof(heap));
    h->data = (Node *)calloc(sizeof(Node),(n + 1));
    h->cnt = 0;
    h->size = n;
    return h;
}
int empty(heap *h){
    return h->cnt <= 0;
}

void pop(heap *h){
    if(empty(h)) return ;
    h->data[1] = h->data[(h->cnt)--];
    int ind = 1;
    while((ind << 1)<= h->cnt){
        int temp = ind;
        if(h->data[temp].wei < h->data[ind << 1].wei || 
           h->data[temp].wei == h->data[ind << 1].wei && h->data[temp].xu > h->data[ind << 1].xu) temp = ind << 1;
        if((ind << 1 | 1) <= h->cnt && h->data[temp].wei < h->data[ind << 1 | 1].wei || 
           h->data[temp].wei == h->data[ind << 1 | 1].wei && h->data[temp].xu > h->data[ind << 1 | 1].xu) temp = ind << 1 | 1;
        if(temp == ind) break;
        swap(h->data[temp],h->data[ind]);
        ind = temp;
    }
}

void push(heap *h,Node val){
    if(h->cnt >= h->size) return;
    h->data[++(h->cnt)] = val;
    int ind = h->cnt;
    while(ind > 1){
        if(h->data[ind].wei < h->data[ind >> 1].wei || 
           h->data[ind].wei == h->data[ind >> 1].wei && h->data[ind].xu > h->data[ind >> 1].xu)  break;
        swap(h->data[ind], h->data[ind >> 1]);
        ind >>= 1;
    }
}
Node top(heap * h){
    return h->data[1];
}


void output(heap *h){
    printf("arr = [\n");
    for(int i = 1; i <= h->cnt; i++){
        printf("%d xu= %d wei = %d\n",i,h->data[i].xu,h->data[i].wei);
    }
    printf("]\n\n");
}



int main(){
    int ti = 0,k = 1;
    scanf("%d", &ti);
    
    while(k <= ti){
        int n = 0;
        scanf("%d", &n);
        heap *h[102];
        for(int i = 0; i < 102; i++){
            h[i] = init(n);
        }
        for(int i = 1; i <= n; i++){
            int a,b;
            scanf("%d %d", &a,&b);
            Node te;
            te.wei = a; te.xu = i;
            push(h[b],te);
        }
        printf("Case #%d:\n",k);
        int time = 0;
        for(int i = 0; i < n; i++){
            int index = 0;
            Node temp = {0,0};
            for(int j = 1; j <= 100; j++){
                if(!empty(h[j]) && (((top(h[j]).wei + time * j)  > (temp.wei + time * index))||
                  ((top(h[j]).wei + time * j) == (temp.wei + time * index) && (top(h[j]).xu)  < (temp.xu))) ){
                    //printf("%d %d |\n",top(h[j]).wei + time * j, temp.wei + time * index);
                    index = j;
                    temp = top(h[j]);
                    //printf("|%d %d|\n",index,top(h[j]).wei);
                }
            }
            printf("%d", temp.xu);
            i  != n - 1 && printf(" ");
            pop(h[index]);
            time += 1;
        }        
        printf("\n");
        k++;
    }
    return 0;
}




