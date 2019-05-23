#*************************************************************************
#	> File Name: scps.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年10月14日 星期日 15时55分57秒
#*************************************************************************

#!/bin/bash

for(( i = 1; i<= 10; i++)) do
    scp -r ./.ssh Tesla@pi${i}:/home/Tesla
done



#scp -r ssh Tesla@pi1:/home/Tesla/.ssh

