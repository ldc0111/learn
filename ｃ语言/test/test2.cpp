/*************************************************************************
	> File Name: test2.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月04日 星期四 20时49分01秒
 ************************************************************************/

#include <stdio.h>
#include "test.h"

int add(int a, int b) {
    return a + b;
}

int is_prime(int x) {
    if (x <= 1) return 0;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}

TEST(test, is_prime_func) {
    EXPECT(is_prime(2), 0);
    EXPECT(is_prime(-2), 0);
    EXPECT(is_prime(15), 0);
    EXPECT(is_prime(9973), 1);
}

TEST(test, add_func) {

    EXPECT(add(1, 2), 3);
    EXPECT(add(3, 4), 7);
    EXPECT(add(2, 2), 4);
}
/*
void func(int *p = &(++num),int haa){
    printf("%d",*p);
    
}*/
/*
int main() {
    return RUN_ALL_TEST();
}
*/
//TEST(test, is_prime_func) {
//}

int main(){
    //char*p =&(fsdaf);
   // printf("%d",EXPECT(is_prime(2), 0));
    //EXPECT(add(1, 2), 3);
    //func("test", "is_prime_func");
    //func("test", "add_func");
    //func();
    return RUN_ALL_TEST();
    //return 0;
}
