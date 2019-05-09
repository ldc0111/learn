#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define swap(a,b) {\
    __typeof(a) __temp = a; a = b; b = __temp;\
}
typedef struct heap{
    double *data;
    int size,cnt;
}heap;
int empty(heap * h){
    return h->cnt <= 0;
}


heap * init(int size){
    heap *h = (heap *)malloc(sizeof(heap));
    h->data = (double *)malloc(sizeof(double) * (size + 1));
    h->cnt = 0;
    h->size = size;
    return h;
}
void push(heap *h, double value){
    if(h->cnt == h->size) return ;
    h->data[++(h->cnt)] = value;
    int ind = h->cnt;
    while(ind > 1){
        if((h->data[ind] - h->data[ind >> 1]) <= 0) break;
        swap(h->data[ind], h->data[ind >> 1]);
        ind >>= 1;
    }
}
double top(heap *h){
    return h->data[1];
}
void pop(heap *h){
    if(empty(h)) return ;
    h->data[1] = h->data[(h->cnt)--];
    int ind = 1;
    while((ind << 1) <= h->cnt){
        int temp = ind;
        if((h->data[temp] - h->data[ind << 1]) < 0) temp = ind << 1;
        if((ind << 1 | 1) <= h->cnt && (h->data[temp] - h->data[ind << 1 | 1]) < 0) temp = ind << 1 | 1;
        if(temp == ind) break;
        swap(h->data[temp], h->data[ind]);
        ind = temp;
    }
}

void clear(heap *h){
    free(h->data);
    free(h);
    return ;
}

void output(heap *h){
    printf("arr = [");
    for(int i = 1; i <= h->cnt; i++){
        printf(" %lf",h->data[i]);
        i == h->cnt && printf(" ]\n");
    }
    return ;
}


int main(){
    int n;
    scanf("%d", &n);
    heap *h = init(n);
    for (int i = 0; i < n; i++){
        double temp;
        scanf("%lf", &temp);
        push(h,temp);
    }
    //output(h);
    //pop(h);
    //output(h);
    for(int i = 0; i < n - 1; i++){
        double a = top(h);
        pop(h);
        double b = top(h);
        pop(h);
        a = pow(a * b * b, 1.0/3);
        push(h,a);
        //output(h);
    }
    printf("%0.5lf",top(h));
    return 0;
}