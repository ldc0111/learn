/*************************************************************************
	> File Name: text.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月04日 星期四 17时52分37秒
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

int main() {
    return RUN_ALL_TEST();
}
