#include <stdio.h>
#include <stdlib.h>
int escape(int **maze, int n, int m,
			    int ip, int mp) {
    #define max(a,b) ((a) > (b) ? (a) : (b))
    //printf("%d\n",maze[1][1]);//1
    maze[1][1] += ip;
    if(maze[1][1] <= 0) return -1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i == 1 && j == 1) continue;
            else if (i == 1) { //第一行
                maze[i][j] = (maze[i][j - 1] == -1 ? -1 : maze[i][j] + maze[i][j - 1]);
                if (maze[i][j]  <= 0) maze[i][j] = -1;
                continue;
            } else if (j == 1){ //第一列
                maze[i][j] = (maze[i - 1][j] == -1 ? -1: maze[i][j] + maze[i - 1][j]);
                if (maze[i][j] <= 0) maze[i][j] = -1;
                continue;
            }
            int temp = max(maze[i - 1][j], maze[i][j - 1]);
            if(temp <= 0 || maze[i][j] + temp <= 0) {
                maze[i][j] = -1;
                continue;
            }
            maze[i][j] += temp;
            if (maze[i][j] > mp) maze[i][j] = mp;
        }
    }
    
    return maze[n][m];
}
int main() {
	int n, m, v, c;
	scanf("%d %d %d %d", &n, &m, &v, &c);
	int  **a = malloc(sizeof(int*) * (n + 1));
	for (int i = 0; i <= n; ++i) {
		a[i] = malloc(sizeof(int) * (m + 1));
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			scanf("%d", &a[i][j]);
		}
	}
	printf("%d\n", escape(a, n, m, v, c));
	return 0;
}