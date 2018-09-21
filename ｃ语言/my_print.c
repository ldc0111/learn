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
int my_printf1(const char *frm, ...){
    int cnt = 0;
    va_list arg;
    va_start(arg, frm);
    //printf("%c",frm[0]);

    for (int i = 0, cnt = 0; frm[i]; i++, cnt++) {
        switch (frm[i]) {

            case '%' : {
                i++;
                
                switch (frm[i]) {
                    
                    case 'd' : {
                        long long  temp = va_arg(arg, int), x = 0;
                        //printf("%d\n", temp);
                        if(temp < 0){
                            putchar('-');
                            temp = -temp;
                        }
                        for(int  j = pow(10,(int)floor(log10(temp))); j > 0;j /= 10){
                           // printf("temp = %d j = %d  %%%d\n", temp, j, temp / j);
                            putchar(temp / j+'0');
                            temp %= j;
                        }
                    } break;
                default: 
                     fprintf(stderr, "error: unkonw %%%c\n", frm[i]);
                     exit(1);
                }
            } break;
            
            default:
                putchar(frm[i]);
        }

    }
    //va_end(arg);
    return cnt;
}



int main(){
    int n = 123;
    //my_printf1("hello");
    my_printf1("n = %d\n", n);
    my_printf1("n = %d\n", 12000);
    my_printf1("n = %d\n", -567);
    my_printf1("n = %d\n", INT32_MIN);//特殊判断，或者换用更大的数据类型
    my_printf1("n = %d\n", INT32_MAX);
    return 0;
}
