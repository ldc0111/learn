/*************************************************************************
	> File Name: test.cpp
	> Author: hug
	> Mail:   hug@haizeix.com
	> Created Time: 日 10/21 10:51:22 2018
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string.h>
typedef struct Vector {
    char **data;
    char *name;
    int size, cnt;
} Vector;

Vector *init(int n) {
    Vector *vec = (Vector *)malloc(sizeof(Vector));
    vec->data = (char **)malloc(sizeof(char *) * n);
    vec->size = n;
    vec->cnt = 0;
    return vec;
}

void push_back(Vector *vec, const char *str) {
    if (vec->cnt == vec->size) return ;
    vec->data[vec->cnt++] = strdup(str);
    return ;
}

void clear(Vector *vec) {
    if (vec == NULL) return ;
    free(vec->data);
    free(vec);
    return ;
}

Vector *getVector(char *str) {
    int n = 0;
    for (int i = 0; str[i]; i++) {
        n += str[i] == '/';
    }
    Vector *vec = init(2 * n + 1);
    push_back(vec, "/");
    str++;
    char *now = str;
    while (now[0]) {
        while (str[0] && str[0] != '/') str++;
        if (str[0] == '/') {
            str[0] = 0;
            push_back(vec, now);
            push_back(vec, "/");
            str++;
        } else {
            push_back(vec, now);
        }
        now = str;
    }
    return vec;
}

void output(Vector *vec) {
    printf("[");
    for (int i = 0; i < vec->cnt; i++) {
        i && printf(" | ");
        printf("%s", vec->data[i]);
    }
    printf("]\n");
    return ;
}

int getType(const char *str) {
    if (strcmp(str, "<int>") == 0) return 1;
    if (strcmp(str, "<str>") == 0) return 2;
    if (strcmp(str, "<path>") == 0) return 3;
    return 0;
}

int match_node(const char *p, const char *t) {
    int type = getType(p);
    switch (type) {
        case 0: return strcmp(p, t) == 0 ? type : -1;
        case 1: {
            for (int i = 0; t[i]; i++) {
                if (t[i] < '0' || t[i] > '9') return -1;
            }
            return type;
        } break;
        case 2: 
        case 3: return type;
    }
    return -1;
}

int match(Vector *v1, Vector *v2) {
    if (v2->cnt < v1->cnt) return 0;
    for (int i = 0; i < v1->cnt; i++) {
        int type;
        if ((type = match_node(v1->data[i], v2->data[i])) == -1) return 0;
        if (type == 3) return 1;
    }
    return v1->cnt == v2->cnt;
}

Vector *rules[105];

int main() {
    int n, m;
    char str[1000];
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        rules[i] = getVector(str);
        scanf("%s", str);
        rules[i]->name = strdup(str);
    }
    for (int i = 0; i < m; i++) {
        scanf("%s", str);
        Vector *now = getVector(str);
        int j = 0;
        while (j < n && match(rules[j], now) == 0) ++j;
        if (j == n) {
            printf("404\n");
        } else {
            printf("%s\n", rules[j]->name);
        }
    }
    return 0;
}
