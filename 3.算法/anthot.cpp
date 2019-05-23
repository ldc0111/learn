/*************************************************************************
	> File Name: anthot.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年11月12日 星期一 20时35分20秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define swap(a,b){\
    __typeof(a) __temp = a; a = b; b = __temp;\
}

typedef struct Point{
    int val,ind,spe;
}Point;

Point* init_point(int length){
    Point * po = (Point *)calloc(sizeof(Point),length);
    return po;
}

typedef struct Data{
    int indx,indy,len;
}Data;

typedef struct heap{
    Data *data;
    int size,count;
}heap;



void  quick_sort(Point * p, int l,int r){
    if(r <= l) return ;
    int x = l,y = r;
    Point z = p[l];
    while(x < y){
        while(x < y && p[y].val >= z.val) y--;
        if(x < y) p[x++] = p[y];
        while(x < y && p[x].val <= z.val ) x++;
        if(x < y) p[y--] = p[x];
    }
    p[x] = z;
    quick_sort(p, l, x - 1);
    quick_sort(p, x + 1, y);
}

void output(Point * p, int length){
    printf("point :[");
    for(int i = 0; i < length; i++){
        printf("%d ",p[i].val);
    }
    printf("]");
}
int main(){
    int n, l, t, a, b;
    scanf("%d%d%d", &n, &l, &t);
    Point *point = init_point(n);
    for(int i = 0; i < n; i++){
        scanf("%d%d", &a, &b);
        point[i].ind = i + 1;
        point[i].val = a;
        point[i].spe = b;
    }
    quick_sort(point, 0, n- 1);
    //output(point, n);
    
    return 0;
}
