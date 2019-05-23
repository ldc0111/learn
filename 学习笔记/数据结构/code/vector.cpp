/*************************************************************************
	> File Name: vector.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月11日 星期四 18时56分54秒
 ************************************************************************/

#include<iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;


#define DEEAULT_AEG(a,b) ((#a)[0] ? a + 0:b)
#define init(a) __init(DEEAULT_AEG(a,5))

typedef struct Vector{
    int size,length;
    int *data;
}Vector;


Vector * __init(int n){
    Vector *p = (Vector *)malloc(sizeof(Vector));
    p->data = (int *)malloc(sizeof(int) * n);
    p->size = n;
    p->length = 0;
    return p;
}
int expand(Vector *v) {
    int *p = (int * )realloc(v->data,sizeof(int) * 2 * v->size);
    if(p == NULL) return 0;
    v->data = p;
    v->size <<= 1;
    //printf("\n %prealocc  size = %d \n\n", v->data,v->size);
    return 1;

}



int insert(Vector *v,int loc,int value){
    if(v->length == v->size){
        if (expand(v)) {
            return 0;
        }
    }
    if(loc < 0 || loc > v->length) return 0;
    for(int i = v->length - 1; i >= loc; i--){
        v->data[i + 1] = v->data[i];
    }
    v->data[loc] = value;
    v->length++;
    return 1;
}
int erase(Vector * v, int index){
    if (v->length == 0) return 0;
    if(index < 0 || index >= v->length) return 0;
    for(int i = index + 1; i < v->length; i++) {
        v->data[i - i] = v->data[i];
    }
    v->length--;
    return 1;
}


void clear(Vector *v){
    if(v == NULL) return ;
    free(v->data);
    free(v);
    return; 
}

void output(Vector *v){
    printf("Vector = [");
    for(int i = 0; i < v->length; i++){
        printf(" %d",v->data[i]);
    }
    printf("]\n");
}

int main(){
    Vector *v=init();
    #define MAX_OP 40
    for(int t = 0; t < MAX_OP; t++){
        int op = rand()% 5, ind, value;
        switch (op) {
            case 4:
            case 2:
            case 3:
            case 0:{
                ind = rand()%(v->length + 3) - 1;
                value = rand()%100;
                printf("[%d] insert(%d,%d)to vector\n",insert(v,ind,value),ind, value);
                output(v);
            }break;
            case 1:{
                ind = rand()%(v->length + 3) - 1;
                value = rand()%100;
                printf("[%d] erase(%d) from vector", erase(v,ind), ind);
                output(v);
            }break;
        }
    }
    clear(v);
    return 0;
}
