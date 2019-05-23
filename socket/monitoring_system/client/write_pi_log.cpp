/*************************************************************************
	> File Name: write_pi_log.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月30日 星期日 15时45分11秒
 ************************************************************************/

#include "../common/common.h"

int write_pi_log(char *pi_healthy_log, const char *format, ...){
    FILE *fp=fopen(pi_healthy_log,"a+");
    if (fp == NULL) {
        perror("fopen:");
        return -1;
    }
    va_list arg;
    va_start(arg,format);
    time_t time_log = time(NULL);
    struct tm* tm_log = localtime(&time_log);

    fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d ", tm_log->tm_year+1900,tm_log->tm_mon+1,tm_log->tm_mday,tm_log->tm_hour,tm_log->tm_min,tm_log->tm_sec);
    vfprintf(fp,format,arg);
    fflush(fp);
    fclose(fp);

}


int main(){
    char *host_t="192.168.1.155";
    write_pi_log("./pi_health_log.log","connection to %s %d success\n", host_t);
    return 0;
}
