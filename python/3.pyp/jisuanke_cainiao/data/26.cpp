#include <stdio.h>
int main() {
    int temp = 0;
    char ch[100 * 101] = {0};
    int k = 0;
    while (scanf("%c",&ch[k++]) != EOF);
    for (int i = 0; i < k; i++) {
        if(ch[i] == 'r'){
            if (ch[i - 1] != '-') {
                temp |= 4;
            }else {
                temp &= 3;
            }
        } else if (ch[i] == 'w') {
            if (ch[i - 1] != '-') {
                temp |= 2;              
            }else {
                temp &= 5;
            }          
        } else if (ch[i] == 'x'){
            if (ch[i - 1] != '-') {
                 temp |=1;             
            }else {
                temp &= 6;
            }            
        }
    }
    printf("%d\n",temp);
    return 0;
}