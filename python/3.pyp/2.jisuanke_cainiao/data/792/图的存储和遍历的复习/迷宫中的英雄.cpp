#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char map[30][30];
int flag[30][30];
int dir[4][2] = {
    1,0,0,1,
    -1,0,0,-1
};
typedef struct Node{
    int x, y;
}Node;

typedef struct Queue{
    Node *data;
    int head,tail;
}Queue;
Queue *init(int n) {
    Queue *q = (Queue *)calloc(sizeof(Queue),1);
    q->data = (Node *)calloc(sizeof(Node), n);
    return q;
}
int push(Queue *q, int x,int y) {
    q->data[(q->tail)].x = x;
    q->data[(q->tail)++].y = y;
}
/*
Node top(Queue * q) {
    q->data[q->head];
}*/
void pop(Queue *q) {
    (q->head)++;
}

int empty(Queue *q) {
    return q->head == q->tail;
}

void clear(Queue *q) {
    free(q->data);
    free(q);
}
int search(Queue *q, int t,int n,int m) {
    int x = 0,y = 0;
    while(!empty(q)) {
        Node temp;
        temp.x = q->data[q->head].x;
        temp.y = q->data[q->head].y;
        pop(q);
        for (int i = 0; i < 4; i++) {//
            x = temp.x + dir[i][0];
            y = temp.y + dir[i][1];
            //if(x == 0 || y == 0 || x == n + 1 || y == m + 1) continue;//越界
            if(map[x][y] == '*' || map[x][y] == 0) continue;//墙
            if(flag[x][y] != -1) continue;//走过,
            flag[x][y] = flag[temp.x][temp.y] + 1;
            if(flag[x][y] > t) break;//步数过多
            if(map[x][y] == 'P') return 1;
            push(q,x,y);
        }
    }
    return 0;
}

int str(char *s,char ch) {
    for (int i = 0; s[i]; i++) {
        if(s[i] == ch) return i;
    }
    return -1;
}

int main() {
    int n, m, t;
    Queue *q = 0;
    while (scanf("%d%d%d",&n, &m, &t) != EOF) {
        q = init(n * m);
        if (n == 0 && m == 0 && t == 0) break;
        memset(map, 0, sizeof(map));
        memset(flag, -1, sizeof(flag));
        
        for (int i = 1; i <= m; i++) {
            scanf("%s",map[i] + 1);
            
            int y = str(map[i] + 1, 'S') + 1;
            if (y > 0) {
                push(q,i,y);
                flag[i][y] = 0;
            }
        }
        if(search(q,t,n,m)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
        clear(q);
    }
    return 0;
}