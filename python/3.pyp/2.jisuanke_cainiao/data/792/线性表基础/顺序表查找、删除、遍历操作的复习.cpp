#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef struct Vector {
    int length,size;
    int *data;
} Vector;

void init(Vector *a,int size) {
    a->size = size;
    a->length = 0;
    a->data = (int *)malloc(sizeof(int) * size);
}

void expand(Vector *a) {
    int *old_data = a->data;
    a->size <<= 1;
    a->data = (int * )malloc(sizeof(int) * a->size);
    for(int i = 0; i < a->length; i++){
        a->data[i] = old_data[i];
    }
    free(old_data);
}

int insert(Vector *a,int loc,int value) {
    if(loc < 0 || loc > a->length){
        return 0;
    }
    if(a->length >= a->size){
        expand(a);
    }
    for(int i = a->length; i >loc; i--){
        a->data[i] = a->data[i - 1];
    }
    a->data[loc] = value;
    a->length++;
    return 1;
}

int search(Vector *a,int value) {
    for (int i = 0; i < a->length; i++) {
        if (a->data[i] == value) {
           return i; 
        }
    }
    return -1;
}

int delete_node(Vector *a,int index) {
    if(index < 0 || index > a->length){
        return 0;
    }
    for(int i = index + 1; i < a->length; i++){
        a->data[i - 1] = a->data[i];
    }
    a->length--;
    return 1;
}

void print(Vector *a) {
    for (int i = 0; i < a->length - 1; i++) {
        printf("%d ", a->data[i]);
    }
    printf("%d\n", a->data[a->length - 1]);
}

void clear(Vector *a) {
    free(a->data);
    free(a);
}

int main() {
    Vector *a = (Vector *)malloc(sizeof(Vector));
    init(a, 20);
    int n,x,y,z;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        int flag = 0;
        if(x == 1){
            scanf("%d%d",&y, &z);
            //printf("n = %d x = %d %d %d ",n,x,y,z);
            if(insert(a,y,z)) flag = 1;
        }else if(x == 2) {
            scanf("%d", &y);
            if(delete_node(a,y)) flag = 1;
        }else if(x == 3){
            scanf("%d",&y);
            if(search(a,y)!= -1) flag = 1;
        }else{
            flag = 2;
            print(a);
        }
        
        if(flag == 1){
            printf("success\n");
        }else if(flag == 0){
            printf("failed\n");
        }
    }
    return 0;
}
