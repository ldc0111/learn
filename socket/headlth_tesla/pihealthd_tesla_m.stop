#*************************************************************************
#	> File Name: pihealthd_tesla_m.stop.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年12月23日 星期日 15时32分41秒
#*************************************************************************

#!/bin/bash  
pid=`ps -ef |awk '{if ($8 == "pihealthd_tesla") print $2}'`
kill -p  $pid
echo "Stopped."
