#include <stdio.h>
int main() {
    int n;
    char * ch[100 * 100] = {0};
    int maxhead = 0, maxtail = 0,temp = 0,j = 0;
    int head = 0;
    scanf("%d", &n);
    scanf("%c", ch[0]);
    while (scanf("%c", &ch[j++]) != EOF);
    for (int i = 0; i < j; i++) {
        if(ch[i] == '\n'){
            if(temp > maxtail - maxhead) {
                maxhead = head;
                maxtail = head + temp;
            }
            head = i + 1;
            temp =  0;
        }else {
            temp++;
        }
    }
    //printf("%d %d\n",maxhead,maxtail);
    for (int i = maxhead; i < maxtail; i++) {
        printf("%c",ch[i]);
    }
    printf("\n");
    return 0;
}