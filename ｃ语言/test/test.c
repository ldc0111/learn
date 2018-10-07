/*************************************************************************
	> File Name: test.c
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月07日 星期日 14时13分55秒
 ************************************************************************/

#include<stdio.h>
#include "test.h"
static FuncDate *FuncDate_head = NULL;

void getFuncDate(const char *a,const char *b,test_func_t func){
    FuncDate *p = (FuncDate *)malloc(sizeof(FuncDate));
    p->a_str = a;
    p->b_str = b;
    p->func = func;
    p->next = FuncDate_head;
    FuncDate_head = p;
    return ;
}

int RUN_ALL_TEST(){
    FuncDate ret;
    ret.next = NULL;
    for(FuncDate * p = FuncDate_head,*q; p; p = q) {
        q = p->next;
        p->next = ret.next;
        ret.next = p;
    }
    FuncDate_head = ret.next;
    
    char color[3][100] = {
        "[ \033[1;32m%.2lf%\033[0m ] total:%d, expect_cnt : %d \n",
        "[ \033[0;31m%.2lf%\033[0m ] total:%d, expect_cnt : %d \n",
        "[ \033[1;31m%.2lf%\033[0m ] total:%d, expect_cnt : %d \n",
    };
    for(FuncDate *p = FuncDate_head; p;p = p->next) {
        struct TestFuncDate date = {0,0};
        printf("[%s %s]\n",p->a_str,p->b_str);
        p->func(&date);
        int index = 0;
        double rate = date.expect_cnt * 1.0/date.total * 100;
        if(rate  < 100) index = 1;
        if(rate < 50) index = 2;
        printf(color[index], rate, date.total, date.expect_cnt);
    }
    return 0;
}

