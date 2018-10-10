/*************************************************************************
	> File Name: my_print.c
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月20日 星期四 20时28分22秒
 ************************************************************************/

#include<stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>

int print_int(int x,int flag){
    if(x == 0){
        flag && putchar('0');
        return !!(flag);
    }
    int temp = x,ret = 0,digit = 0;
    x = 0;
    if (temp < 0) temp = -temp,putchar('-');
    while(temp){
        x = x * 10 + temp % 10;
        temp /= 10;
        digit++;
    }
    while(digit--){
        putchar(x % 10 + '0');
        x /= 10;
        ret++;
    }
    return ret;
}



int my_printf1(const char *frm, ...){
    int cnt = 0;
    va_list arg;
    va_start(arg, frm);

    for (int i = 0; frm[i]; i++, cnt++) {
        switch (frm[i]) {

            case '%' : {
                i++;
                
                switch (frm[i]) {   
                    case 'd' : {
                        int temp = va_arg(arg,int);
                        int p1 = temp /10, p2 =temp % 10;
                        if(temp < 0){
                            p1 = -p1,p2 = -p2;
                            putchar('-'); cnt++;
                        }
                        cnt += print_int(p1,0);
                        cnt += print_int(p2,1);
                    } break;
                default: 
                     fprintf(stderr, "error: unkonw %%%c\n", frm[i]);
                     exit(1);
                }
            } break;     
        default:
            putchar(frm[i]);
            cnt++;
        }
    }
    //va_end(arg);
    return cnt;
}



int main(){
    int n = 123;
    //printf("%ld\n",pow(10,(long long)floor(log10(0))));
    my_printf1("hello\n");
    my_printf1("n = %d\n", n);
    my_printf1("n = %d\n", 12000);
    my_printf1("n = %d\n",0);
    my_printf1("n = %d\n", -567);
    my_printf1("n = %d\n", INT32_MIN);//特殊判断，或者换用更大的数据类型
    my_printf1("n = %d\n", INT32_MAX);
    return 0;
}
