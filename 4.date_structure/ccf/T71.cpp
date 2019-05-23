/*************************************************************************
> File Name: T71.cpp
> Author: ldc
> Mail: litesla
> Created Time: 2018年10月28日 星期日 09时41分14秒
************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct vector{
    char **data;
    char *name;
    int count, size;
}Vector;


Vector* init(int size){
    Vector *v = (Vector *)malloc(sizeof(Vector));
    v->data = (char **)malloc(sizeof(char*) * size);
    v->size = size;
    v->count = 0;  
    return v;
}

void push_back(Vector *v,const char *val){
    if(v->count == v->size) return ;
    v->data[v->count++] = strdup(val);
    return ;
}

Vector * getVector(char *str){
    int n = 0;
    for(int i = 0; str[i]; i++){
        n += str[i] == '/';
    }
    Vector *vec = init(2 *n + 1);
    push_back(vec,"/");
    str++;
    char *now = str;
    while(now[0]){
        while(str[0] && str[0] != '/') str++;
        if(str[0] == '/'){
            str[0] = 0;
            push_back(vec,now);
            push_back(vec,"/");
            str++;
        } else{
            push_back(vec,now);
        }
        now = str;
    }
    return vec;
}

int getType(const char *str){
    if(strcmp(str, "<int>") == 0) return 1;
    if(strcmp(str, "<str>") == 0) return 2;
    if(strcmp(str, "<path>") == 0) return 3;
    return 0;
}


int match_node(const char *p, const char *t){
    int type = getType(p);
    switch(type){
        case 0:return strcmp(p,t) == 0 ? type:-1;
        case 1:{
            for(int i = 0; t[i]; i++){
                if(t[i] < '0' || t[i] > '9') return -1;
            }
            return type;
        }break;
        case 2:
        case 3: return type;
    }
    return -1;
}



int match(Vector *v1,Vector *v2){
    if(v2->count < v1->count) return 0;
    for(int i = 0; i < v1->count; i++){
        int type;
        if((type = match_node(v1->data[i], v2->data[i])) == -1) return 0;
        if(type == 3) return 1;
    }
    return v1->count == v2->count;
}

void intprint(char *ch){
    int temp = 0;
    while(*ch){
        temp = temp * 10 + (*ch - '0');
        ch++;
    }
    printf("%d",temp);
}

int isint(char *ch){
    while(*ch){
        if(*ch  < '0' || *ch > '9')  return 0;
        ch++;
    }
    return 1;
}
void pathprint(Vector *n, int i){
    for(int j = i; j < n->count; j++){
        printf("%s",n->data[j]);
    }
}

void print(Vector *n,Vector *p){
    for(int i = 0; i < p->count; i++){
        int type = getType(p->data[i]);
        type != 0 && printf(" ");
        if(type == 1){
            intprint(n->data[i]);
        }else if(type == 2){
            if(isint(n->data[i])){
                intprint(n->data[i]);
            }else{
                printf("%s",n->data[i]);
            }
        }else if(type == 3){
            pathprint(n,i);
        }
    }
    printf("\n");
}

void output(Vector *vec){
    printf("[");
    for(int i = 0; i < vec->count; i++){
        i && printf(" | ");
        printf("%s", vec->data[i]);
    }
    printf("]\n");
    return ;
}



Vector *rules[105];

int main(){
    int n,m;
    char str[1000];
    scanf("%d%d",&n,&m);
    for(int i = 0; i < n; i++){
        scanf("%s", str);
        rules[i] = getVector(str);
        scanf("%s",str);
        rules[i]->name = strdup(str);
    }
    //for(int i = 0; i < n; i++){
    //    output(rules[i]);
    //}
    
    for(int i = 0; i < m; i++){
        scanf("%s",str);
        Vector *now = getVector(str);
        int j = 0;
        while(j < n && match(rules[j], now) == 0) ++j;
        if(j == n){
            printf("404\n");
        } else {
            printf("%s",rules[j]->name);
            print(now,rules[j]);
        }
    }


    return 0;
}
