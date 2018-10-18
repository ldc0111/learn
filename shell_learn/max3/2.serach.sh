#*************************************************************************
#	> File Name: 2.serach.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年10月15日 星期一 10时56分28秒
#*************************************************************************

#!/bin/bash

pi_cmd="
grep -EIHron "[a-zA-Z]+" './' |awk -F ':' '{print length(\$3)  \$0 }'|sort -r -t "." -k 1 -g|head -3
"



for i in `seq 1 10` ; do
    echo  "pi$i"
    ssh -t Tesla@pi${i} ${pi_cmd}
    echo  "\n"
done 
