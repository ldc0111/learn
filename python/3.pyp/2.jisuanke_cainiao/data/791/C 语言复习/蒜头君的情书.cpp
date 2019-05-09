#include <stdio.h>
#include <string.h>

const int MAX_LENGTH = 256;

char* get_letter(void) {
    static char letter[1000000];
    letter[999999] = ' ';
    char *p = letter;
    int size = MAX_LENGTH;
    while (feof(stdin) == 0) {
        if (size == 0) {
            break;
        }
        fgets(p, size + 1, stdin);
        while (*p != '\0') {
            p++;
            size--;
        }
    }
    return letter;
}

int main() {
    char *str = get_letter();

    char  st[MAX_LENGTH];
    //printf("%s\n",str);
    strcpy(st,str);
    int ans = 0;
    // 在此处添加你的代码
    char s[] = " ";
    for(int i = 0; i < strlen(str); i++){
        if(st[i] == '\t'|| st[i] == '\n'  || st[i] == '\t' || 
           st[i] == '\"' || st[i] == '\'' || st[i]==',' ||
           st[i] == '.'){
            st[i] = ' ';
        }
    }
    char *token = strtok(st,s);
    
    while(token != NULL){
        if(strcmp(token,"love") == 0) ans++;
        for(int i = 0; i < strlen(token); i++){
            printf("%c", token[i]);
        }
        printf("\n");
        token = strtok(NULL,s);
    }
    
    printf("%d\n", ans);
    puts(str);
    return 0;
}

#undef MAX_LENGTH
