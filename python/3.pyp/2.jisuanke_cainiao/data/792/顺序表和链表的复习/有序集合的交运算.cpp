#include <stdio.h>
#include <stdlib.h>

typedef struct Vector{
    int size,length;
    int *data;
}Vector;

Vector *init(int size){
    Vector *p = (Vector *)malloc(sizeof(Vector));
    p->size = size;
    p->length = 0;
    p->data = (int *)malloc(sizeof(int) *size);
    return p;
}
int insert(Vector *v, int loc,int value) {
    if(loc < 0 || loc > v->length) {
        return 0;
    }
    for(int i = v->length; i > loc; i--){
        v->data[i] = v->data[i - 1];
    }
    v->data[loc] = value;
    v->length++;
    return 0;
}

void output(Vector *v){
    if(v->length == 0) return ;
    for(int i = 0; i < v->length - 1; i++){
        printf("%d ",v->data[i]);
    }
    printf("%d\n", v->data[v->length - 1]);
}
int search(Vector *v, int value){
    for(int i = 0; i < v->length; i++){
        if(v->data[i] == value){
            return i;
        }
    }
    return -1;
}


int main(){
    int n,m;
    scanf("%d", &n);
    Vector *v = init(n);
    for (int i = 0; i < n; i++) {
        int temp = 0;
        scanf("%d", &temp);
        insert(v,i,temp);
    }

    scanf("%d", &m);
    Vector *v2 = init(m);
    for (int i = 0; i < m; i++) {
        int temp = 0;
        scanf("%d", &temp);
        insert(v2,i,temp);
    }    
    //output(v);
    //output(v2);
    Vector *v3 = init(n > m ? n : m);
    for(int i = 0; i< v->length; i++){
        if(search(v2,v->data[i]) != -1){
            insert(v3,v3->length,v->data[i]);
        }
    }
    printf("%d\n",v3->length);
    output(v3);
    
    return 0;
}