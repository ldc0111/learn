#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Vector{
    int size,length;
    int *data;
}Vector;

Vector * init(int size){
    Vector *p = (Vector *)malloc(sizeof(Vector));
    p->size = size;
    p->length = 0;
    p->data = (int *)malloc(sizeof(int) *size);
    return p;
}

int insert(Vector *v,int loc,int value){
    if(loc < 0 || loc > v->length){
        return 0;
    }
    for(int i = v->length; i > loc; i--){
        v->data[i] = v->data[i - 1];
    }
    v->data[loc] = value;
    v->length++;
    return 1;
}
void output(Vector *v){
    for(int i = 0; i< v->length - 1; i++){
        printf("%d ", v->data[i]);
    }
    printf("%d\n", v->data[v->length - 1]);
}

int main(){
    int n,a,b,c;
    int ans = 0;
    scanf("%d", &n);
    Vector *v = init(n);
    Vector *v2 =init(n);
    for(int i = 0; i < n; i++){
        scanf("%d%d",&a,&b);
        insert(v,i,a);
        insert(v2,i,b);
    }
    scanf("%d", &c);
    //output(v);
    //output(v2);
    for(int i = 0; i< n; i++) {
        ans += v->data[i] * pow(c,v2->data[i]);
    }
    printf("%d\n",ans);
    
    return 0;
}