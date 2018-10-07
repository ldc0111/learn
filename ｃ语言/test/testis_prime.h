/*************************************************************************
	> File Name: testis_prime.h
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月07日 星期日 11时49分47秒
 ************************************************************************/

#ifndef _TESTIS_PRIME_H
#define _TESTIS_PRIME_H
TEST(test, is_prime_func) {
    EXPECT(is_prime(2), 0);
    EXPECT(is_prime(-2), 0);
    EXPECT(is_prime(15), 0);
    EXPECT(is_prime(9973), 1);
}



#endif
