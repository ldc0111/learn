#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct hashtable{
    char **elem;
    int size;
}HashTable;
void init(HashTable *h, int n) {
    h->size = n;
    h->elem = (char **)malloc(sizeof(char *) * h->size);
    for(int i = 0; i < h->size; i++) {
        h->elem[i] = NULL;
    }
    return ;
}

int hash(HashTable * h, char value[]) {
    int code = 0;
    for(size_t i = 0; i < strlen(value); i++){
        code = (code * 256 + value[i] + 128) % h->size;
    }
    return code;
}
int search(HashTable *h, char value[], int *pos){
    *pos = hash(h,value);
    while(h->elem[*pos] != NULL && strcmp(h->elem[*pos],value) != 0) {
        *pos = (*pos + 1) % h->size;
    }
    if(h->elem[*pos] != NULL && strcmp(h->elem[*pos],value) == 0) {
        return 1;
    } else {
        return 0;
    }
}
int insert(HashTable *h, char value[], int *pos){
    search(h,value,pos);
    h->elem[*pos] = (char *)malloc(strlen(value) + 1);
    strcpy(h->elem[*pos],value);
    return 1;
}

void xiao(char buffer[]) {
    for (int i = 0; buffer[i]; i++) {
        if(buffer[i] >= 'A' && buffer[i] <= 'Z') {
            buffer[i]+= ('a' - 'A');
        }
    }
    return ;
}


int main(){
    int n;
    char buffer[105];
    scanf("%d",&n);
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    init(h, 10 * n);
    
    for(int i = 0; i < n; i++){
        scanf("%s",buffer);
        xiao(buffer);
       int pos;
        
        if(search(h,buffer,&pos)) {
            printf("Yes\n");
        } else {
            printf("No\n");
            insert(h,buffer,&pos);
        }
    }
    
    
    return ;
}