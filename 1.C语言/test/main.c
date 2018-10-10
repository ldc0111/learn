/*************************************************************************
	> File Name: main.c
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月07日 星期日 11时28分49秒
 ************************************************************************/

#include<stdio.h>
#include "is_prime.h"
#include "add.h"
#include "test.h"

#ifdef TESTFUNC
#include "testadd.h"
#include "testis_prime.h"
#endif




int main(){
    printf("hello, world\n");
    return RUN_ALL_TEST(); 
}
