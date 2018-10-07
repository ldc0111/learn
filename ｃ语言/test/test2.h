/*************************************************************************
	> File Name: test2.h
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月06日 星期六 11时22分45秒
 ************************************************************************/
#ifndef _TEST_H


int total = 0,expect_cnt = 0;

#define EXPECT(func,value) ({\
    int te;\
    te = ((func) == value) ? 1:0;\
    *(expectcnt) += te;\
    printf("%s == %d %s\n",#func,value,(te == 1 ? "True" : "False"));\
    (*top)++;\
})

#define TEST(test,functype) void  functype(int *top,int *expectcnt)


#define RUN_ALL_TEST() (\
    printf("[test,is_prime_func]\n"),\
    is_prime_func(&total,&expect_cnt),\
    printf("[ \033[1;32mPASS\033[0m ] total: %d, expect_cnt : %d\n",total,expect_cnt),\
    total = 0, expect_cnt = 0,\
    printf("[test,is_prime_func]\n"),\
    add_func(&total,&expect_cnt),\
    printf("[ \033[1;32mPASS\033[0m ] total: %d, expect_cnt : %d\n",total,expect_cnt),\
    1\
)

#define _TEST_H
#endif
