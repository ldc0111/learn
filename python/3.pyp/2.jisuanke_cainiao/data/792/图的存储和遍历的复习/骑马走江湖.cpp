#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max 110
#define INT_MAX 0x3f3f3f3f
typedef struct map{
    char ma[max][max];
    int dis[max][max];
}map;
typedef struct Node{
    int x,y;
}Node;

int dir[4][2] = {
    1,0,0,1,
    -1,0,0,-1
};
int dirr[8][2] = {
    2,1,2,-1,1,2,-1,2,
    -2,1,-2,-1,1,-2,-1,-2
};


void init(map *mp,int n, int m) {
    memset(mp->ma, 0, sizeof(mp->ma));
    memset(mp->dis, -1, sizeof(mp->dis));
}
/*
void  dfs(map *mp, int x, int y,int *min_ans) {
    for (int i  = 0; i < 4; i++) {
        int a = x + dir[i][0];
        int b = y + dir[i][1];
        //printf("1: i %d  : x: %d y: %d %c\n",i, x, y, mp->ma[a][b]);
        if (mp->ma[a][b] == 0 || mp->ma[a][b] == '#') continue;//是墙
        //printf("2 :i %d  : x: %d y: %d %c\n",i, x, y, mp->ma[a][b]);
        for (int j = 0; j < 2; j++) {
            if(2 * i + j > 8 || 2 * i + j < 0) break;
            int xx = x + dirr[2 * i + j][0];
            int yy = y + dirr[2 * i + j][1];
            //printf("j1 :x %d y %d  dis: %d xx %d yy %d %c\n", x, y, mp->dis[x][y], xx, yy,mp->ma[xx][yy]);
            if (mp->ma[xx][yy] == 0 || mp->ma[xx][yy] == '#' || mp->dis[xx][yy] != -1) continue;//是墙//走过
            //printf("j2 :x %d y %d  dis: %d xx %d yy %d %c\n", x, y, mp->dis[x][y], xx, yy,mp->ma[xx][yy]);
            mp->dis[xx][yy] = mp->dis[x][y] + 1;
            if(mp->ma[xx][yy] == 'e') {
                *min_ans = *min_ans < mp->dis[xx][yy] ? *min_ans : mp->dis[xx][yy];
            }
            dfs(mp,xx,yy,min_ans);
            mp->dis[xx][yy] = -1;//回溯
        }
    }
    return ;
}*/
void output(map *mp, int n, int m) {
    for (int i = 5; i < n + 5; i++) {
        for (int j = 5; j < m + 5; j++) {
            printf("%d ",mp->dis[i][j]);
        }
        printf("\n");
    }
    //printf('\n');
    return ;
}
int bfs(map *mp,int x,int y,int n, int m) {
    int min_ans = INT_MAX;
    Node *q = (Node *)calloc(sizeof(Node), n * m);
    int head = 0,tail = 0;
    q[tail].x = x;
    q[tail++].y = y;
    while (head < tail) {
        int nowx = q[head].x;
        int nowy = q[head++].y;
        //printf("nowx %d nowy %d\n",nowx,nowy);
        for (int i = 0; i < 4; i++) {
        	int a = nowx + dir[i][0];
        	int b = nowy + dir[i][1];
         	if (mp->ma[a][b] == 0 || mp->ma[a][b] == '#') continue;//是墙
        	for (int j = 0; j < 2; j++) {
            	int xx = nowx + dirr[2 * i + j][0];
            	int yy = nowy + dirr[2 * i + j][1];
                
                if (mp->ma[xx][yy] == 0 || mp->ma[xx][yy] == '#' || mp->dis[xx][yy] != -1) continue;//是墙//走过
                //printf("xx %d yy %d\n",xx,yy);
                mp->dis[xx][yy] = mp->dis[nowx][nowy] + 1;
				if(mp->ma[xx][yy] == 'e') {
                	min_ans = min_ans < mp->dis[xx][yy] ? min_ans : mp->dis[xx][yy];
            	}
                q[tail].x = xx;
                q[tail++].y = yy;
        	}
    	}
        //output(mp,n,m);
    }
    return min_ans == INT_MAX ? -1 : min_ans;
}

void start(map *mp, int n, int m, int *x, int *y) {
    int flag = 1;
    for (int i = 5; i < n + 5 && flag; i++) {
        for (int j = 5; j < m + 5 && flag; j++) {
            if(mp->ma[i][j] == 's'){
                *x = i;
                *y = j;
                flag = 0;
            }
        }
    }
    return ;
}


int main() {
    int n,m;
    while (scanf("%d %d", &n,&m) != EOF) {
        map mp;
        init(&mp,n,m);
        for (int i = 5; i < n + 5; i++) {
            scanf("%s",mp.ma[i] + 5);
        }
        int x,y,ans = INT_MAX;
        start(&mp, n, m, &x, &y);
        mp.dis[x][y] = 0;
        //dfs(&mp,x,y,&ans);
        //printf("%d %d\n", x,y);
        printf("%d\n", bfs(&mp,x,y,n,m));
        
    }
    return 0;
}