#include <stdio.h>
int main() {
    char ch[500] = {0};
    int arr[32] = {0},bits[32] = {0};
    scanf("%s",ch);
    for (int i = 1;ch[i - 1]; i++) {
        arr[i % 32] += ch[i -1];
    }
    for(int i = 0; i < 32; i++) {
        bits[i] = arr[31 - i]^(arr[i] << 1);
        bits[i] = bits[i] % 85 + 34;
        printf("%c",bits[i]);
    }
    printf("\n");
    return 0;
}