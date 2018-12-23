#*************************************************************************
#	> File Name: pihealthd_tesla_m.start.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年12月23日 星期日 15时12分33秒
#*************************************************************************

#!/bin/bash
if [[ ! -e /etc/pihealthd_tesla.pid ]] ; then
    touch /etc/pihealthd_tesla.pid
fi 

pre_pid=`cat /etc/pihealthd_tesla.pid`

if test -n $pre_pid ; then 
    ps -ef |grep ${pre_pid} |grep pihealthd_tesla > /dev/null 
    if [[ $? == 0 ]]; then
        echo "Pihealthd_tesla has already started."
        exit 0
    else
        echo "Pihealthd_tesla is starting."
        ./master/pihealthd_tesla > /dev/null 
        echo "Pihealthd_tesla started."
    fi 
else 
    echo "Pihealthd_tesla is starting."
    ./master/pihealthd_tesla > dev/null
    echo "Pihealthd_tesla started."
fi 
pid=`ps -ef | awk '{if ($8 == "pihealthd_tesla") printf $2}'`
echo $pid > /etc/pihealthd_tesla.pid
