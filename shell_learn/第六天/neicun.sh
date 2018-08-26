#!/bin/bash

#dates=`date +"%Y_%m_%d_%H:%M:%S"`
#arr=(`free -m|awk 'NR == 2{print $2 " " $3}'`)
#echo ${arr[0]} ${arr[1]}
#yong=`free -m|awk 'NR == 2{print $3}'`
#remainder=$[ ${arr[0]} - ${arr[1]} ]
#occupancy=`echo "scale=1;$remainder*100 / ${arr[0]}"|bc`
#dynanic=`echo "scale=1;0.3*$1+0.7*$occupancy"|bc`
#echo $1
#echo "$dates  ${arr[0]}M  ${remainder}M  ${occupancy}%  ${dynanic}%"

free|awk 'BEGIN{remainder="" ; occupancy="" ; dynanic=""} NR == 2{remainder=$2 - $3 ; occupancy=remainder * 100/$2; dynanic = 0.3*la + 0.7*occupancy ; printf "%s\t%sM\t%sM\t%.1f%%\t%.1f%%\n",dates,$2,$3,occupancy,dynanic}' dates=`date +"%Y_%m_%d_%H:%M:%S"` la=$1
