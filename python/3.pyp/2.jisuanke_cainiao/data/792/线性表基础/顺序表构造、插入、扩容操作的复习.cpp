#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef struct Vector {
    int length,size;
    int *data;
} Vector;

void init(Vector *v,int size) {
    v->size = size;
    v->length = 0;
    v->data = (int *)malloc(sizeof(int) * v->size);
}

void expand(Vector *v) {
    printf("expand\n");
    int *old_data = v->data;
    v->size  <<= 1;
    v->data = (int *)malloc(sizeof(int) * v->size);
    for(int i = 0; i < v->length; i++){
        v->data[i] = old_data[i];
    }
    free(old_data);
}

int insert(Vector *v, int loc, int value) {
    if(loc < 0 || loc > v->length){
        return ERROR;
    }
    if(v->length >= v->size){
        expand(v);
    }
    for(int i = v->length; i > loc; i--){
        v->data[i] = v->data[i - 1];
    }
    v->data[loc] = value;
    v->length++;
    return OK;
}


void clear(Vector *v) {
    free(v->data);
    free(v);
}

int main() {
    Vector *a = (Vector *)malloc(sizeof(Vector));
    init(a, 5);
    int n;
    int b,c;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &b, &c);
        if (insert(a, b, c)) {
            printf("success\n");
        }else{
            printf("failed\n");
        }
    }

    return 0;
}