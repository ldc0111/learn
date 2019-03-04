/*************************************************************************
	> File Name: test.h
	> Author: ldc
	> Mail: 
	> Created Time: 2018年10月05日 星期五 15时17分05秒
 ************************************************************************/

#ifndef _TEST_H
#define _TEST_H
#include <stdlib.h>

//测试结构体
struct TestFuncData{
    int total, expect;
    //总量和成功量
};

//声明一个函数指针传递的参数是,链表节点
typedef void (*test_func_t)(struct TestFuncData *);

//链表节点
struct FuncData {
    const char *a_str, *b_str;//函数名
    test_func_t func;//函数指针
    struct FuncData *next;//链表指针
};
//增加链表节点的函数,参数有函数名,和需要测试的函数指针
void addFuncData(const char *a, const char *b, test_func_t func);
//声明一个函数
int RUN_ALL_TEST();


//声明一个函数 
//__attribute__让下面那个函数比主函数先运行
//生成一个增加函数
//函数内部调用增加链表节点函数
//1讨论为什么要在函数内部调用那个函数,
//因为测试是多种函数一起编译,这样就可以重复的调用addFuncData
//最后一行生成一个函数头,注意函数的参数是测试结构体
//注意这个是多行宏定义
#define TEST(a,b) \
    void a##_haizeix_##b(struct TestFuncData *); \
    __attribute__((constructor)) \
    void ADDFUNC_##a##_haizeix_##b() { \
        addFuncData(#a, #b, a##_haizeix_##b); \
    } \
    void a##_haizeix_##b(struct TestFuncData *__data)


//判断该是否相等,ret是局部变量
//注意最外面有()
#define EXPECT_EQ(a, b) ({ \
    int ret; \
    printf("%s == %s %s\n", #a, #b, (ret = (a == b)) ? "True" : "False"); \
    __data->total += 1; \
    __data->expect += ret; \
})

#define EXPECT_GT(a, b) ({ \
    int ret; \
    printf("%s > %s %s\n", #a, #b, (ret = (a > b)) ? "True" : "False"); \
    __data->total += 1; \
    __data->expect += ret; \
})

#define EXPECT_LT(a, b) ({ \
    int ret; \
    printf("%s < %s %s\n", #a, #b, (ret = (a < b)) ? "True" : "False"); \
    __data->total += 1; \
    __data->expect += ret; \
})

#define EXPECT_NE(a, b) ({ \
    int ret; \
    printf("%s != %s %s\n", #a, #b, (ret = (a != b)) ? "True" : "False"); \
    __data->total += 1; \
    __data->expect += ret; \
})

#define EXPECT_GE(a, b) ({ \
    int ret; \
    printf("%s >= %s %s\n", #a, #b, (ret = (a >= b)) ? "True" : "False"); \
    __data->total += 1; \
    __data->expect += ret; \
})

#define EXPECT_LE(a, b) ({ \
    int ret; \
    printf("%s <= %s %s\n", #a, #b, (ret = (a <= b)) ? "True" : "False"); \
    __data->total += 1; \
    __data->expect += ret; \
})

#endif
