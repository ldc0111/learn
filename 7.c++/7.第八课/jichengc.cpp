/*************************************************************************
	> File Name: jichengc.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月16日 星期三 11时02分17秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////.h
void init_a();
void init_b();
void say_a();
void say_b();

////////////////



typedef struct A{
    int a,b;
}A;
typedef struct B{
    A parent;
    int c,d;
}B;


void init_a(A * thisa,int a, int b) {
    thisa->a = a;
    thisa->b = b;
}
void init_b(B *thisb, int a, int b, int c, int d){
    init_a(&thisb->parent, a,b);
    thisb->c = c;
    thisb->d = d;
    return ;
}
void say_a(){
    
}
void say_b(B *thisb){
    printf("%d %d %d %d\n", thisb->parent.a,thisb->parent.b,thisb->c,thisb->d);
    return ;
}
void freeb(B *thisb){
    free(thisb);
}
int main() {
    B temp;
    init_b(&temp,1,2,3,4);
    say_b(&temp);
    B cc;
    init_b(&cc, 111,1111,111111,1111111);
    say_b(&cc);
    return 0;
}



