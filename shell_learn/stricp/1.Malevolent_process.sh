#*************************************************************************
#	> File Name: Malevolent_process.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年09月12日 星期三 20时20分08秒
#*************************************************************************

#!/bin/bash


data1=(`ps -aux --sort=pid |awk '$3 > 50{printf "%d,",$2}'`)
#echo ${data1[@]}
sleep 5
dates=`date +%Y-%m-%d__%H:%M:%S`
ps -aux --sort=pid|awk -v datess=$dates -v data2=${data1[*]} 'BEGIN{temp=0;split(data2,data,",")} 
{
    if ($2 > data[temp]){
        temp++
    }else if($2 == data[temp] && $3 > 50){
    printf "%s %s %d %s %.2f%% %.2f%%\n", datess,$11,$2,$1,$3,$4
   }
}'


