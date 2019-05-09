#include <stdio.h>
#include <stdlib.h>
typedef struct vector{
    int size,length;
    int *data;
}*Vector,vector;
Vector init(int size){
    Vector p = (Vector)malloc(sizeof(vector));
    p->size = size;
    p->length = 0;
    p->data = (int *)malloc(sizeof(int ) * size);
    return p;
}
int insert(Vector v,int loc,int value) {
    if(v == NULL) return 0;
    if (loc < 0 || loc > v->length) {
        return 0;
    }
    for(int i = v->length; i > loc; i--){
        v->data[i] = v->data[i - 1];
    }
    v->data[loc] = value;
    v->length++;
    return 1;
}


void output(Vector v){
    for (int i = 0; i< v->length - 1; i++) {
        printf("%d ", v->data[i]);
    }
    printf("%d\n",v->data[v->length - 1]);
}
void zuoyionce(Vector v){
    v->data[v->length] = v->data[0];
    for(int i = 0; i < v->length; i++){
        v->data[i] = v->data[i + 1];
    }
}
void zuoyi(Vector v, int k) {
    for(int i = 0; i < k; i++){
        zuoyionce(v);
    }
    return 0;
}

int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    Vector v = init(n + 1);
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        insert(v,i,a);
        //output(v);
    }
    zuoyi(v, k);
    output(v);
    return 0;
}