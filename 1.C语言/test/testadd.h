/*************************************************************************
	> File Name: testadd.h
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月07日 星期日 11时48分25秒
 ************************************************************************/

#ifndef _TESTADD_H
#define _TESTADD_H
TEST(test, add_func) {
    EXPECT(add(1, 2), 3);
    EXPECT(add(3, 4), 7);
    EXPECT(add(2, 2), 4);
}

#endif
