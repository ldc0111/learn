#*************************************************************************
#	> File Name: pi.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年10月14日 星期日 23时22分19秒
#*************************************************************************

#!/bin/bash
name="./serach.sh"
for i in `seq 1 10`; do
    scp $name Tesla@pi$i:.
    ssh Tesla@pi$i "bash $name > ./out.log"
    scp Tesla@pi$i:./out.log ./piout/pi$i.out
done
