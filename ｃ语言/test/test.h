/*************************************************************************
	> File Name: test.h
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月04日 星期四 17时53分30秒
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
#define max_size 1000

typedef void (*funcp)(int *,int *);

struct Node{
//    funcp *p[max_size];
    int t;
}node;
int num = 0;

#define test int * p = &(++num),

#define TEST(test,functype) void  functype(int *top,int *expectcnt,test)


#define RUN_ALL_TEST() (\
    printf("[test,is_prime_func]\n"),\
    is_prime_func(&total,&expect_cnt),\
    printf("[ \033[1;32mPASS\033[0m ] total: %d, expect_cnt : %d\n",total,expect_cnt),\
    printf("%d\n",num),\
    1\
)

#define _TEST_H
#endif





