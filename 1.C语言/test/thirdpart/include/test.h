/*************************************************************************
	> File Name: test.h
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月04日 星期四 17时53分30秒
 ************************************************************************/

#ifndef _TEST_H
#define _TEST_H
#include <stdlib.h>


struct TestFuncDate{
    int total,expect_cnt;
};


#define EXPECT(func,value) ({\
    int temp;\
    printf("%s == %s %s\n", #func, #value, ((temp = (func == value)) ? "True" : "False"));\
    __date->total++;\
    __date->expect_cnt += temp;\
})

typedef void (*test_func_t)(struct TestFuncDate * );
typedef struct FuncDate{
    const char *a_str,*b_str;
    test_func_t func;
    struct FuncDate *next;
}FuncDate;

void getFuncDate(const char *a,const char *b,test_func_t func);

#define TEST(a, b) \
   void a##_haizei_##b(struct TestFuncDate * );\
    __attribute__((constructor))\
    void ADDFUNC ##a##_haizei_##b(){\
        getFuncDate(#a, #b,a##_haizei_##b);\
    }\
    void  a##_haizei_##b(struct TestFuncDate *__date)

int RUN_ALL_TEST();


#endif





