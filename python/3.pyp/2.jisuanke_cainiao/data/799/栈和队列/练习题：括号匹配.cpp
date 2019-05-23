#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
    int first, second;
} Pair;
/** Pair 的定义如下
 * typedef struct {
 *     int first, second;
 * } Pair;
 */
Pair* bracketsPairs(char *str) {
    if (str == NULL) return NULL;
    if (str[0] == ')') return NULL;
    int len = strlen(str), tail = -1, ind = 0, pin = -1;
    int *sta = (int *)malloc(sizeof(int) * strlen(str));
    Pair *pa = malloc((len >> 1) * sizeof(Pair));
    sta[++tail] = (ind++) + 1;
    while (ind  < len) {
        if (str[ind] == '(') {
            sta[++tail] = (ind++) + 1;//进栈
        } else {
            if (tail < 0) {
                    return NULL;
            }
            else {
                //pa = realloc(pa,(pin + 1) * sizeof(Pair));
                pa[++pin].first = sta[tail--];
                pa[pin].second = (ind++) + 1;
            }
        }
    }
    if (tail >= 0) return NULL;
    return pa;
}
int main() {
    char str[50010];
    scanf("%s", str);
    Pair* result = bracketsPairs(str);
    if (!result) {
        puts("No");
    } else {
        puts("Yes");
        for (int i = 0; i < strlen(str) / 2; ++i) {
            printf("%d %d\n", result[i].first, result[i].second);
        }
        free(result);
    }
    return 0;
}