#*************************************************************************
#	> File Name: tssk.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年08月26日 星期日 15时52分05秒
#*************************************************************************

#!/bin/bash
dates=`date +%Y-%m-%d__%H:%M:%S`
tesk=(`df -m|grep '^/dev'|awk '{printf "1 %10s %10s %10s %10s\n",$6,$2,$3,$5}'`)
total=''
toused=''
touper=''
#$echo ${#tesk[@]}
for ((i = 0 ; i < ${#tesk[@]}; i += 5)) do
    ((total += ${tesk[i + 2]}))
    ((toused += ${tesk[i + 3]}))
    #echo !
done
#echo $total
#echo $toused
touper=$[ $toused*100/$total ]
#echo $touper
for ((i = 0; i < ${#tesk[@]}; i += 5)) do
    printf "%s\t1\t%20s\t%s\t%s\t%s\n" $dates ${tesk[i + 1]} ${tesk[i + 2]} ${tesk[i + 3]} ${tesk[i + 4]}
    #printf "%20s 1 %20s %20s %20s %20s\n",$dates,${tesk[i + 1]},${tesk[i + 2]},${tes[i + 3]},${tesk[i + 4]}
done
printf "%s\t0\t%20s\t%s\t%s\t%s%%\t\n" $dates disk $total $toused $touper

