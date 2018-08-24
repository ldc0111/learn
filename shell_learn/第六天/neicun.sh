#!/bin/bash

dates=`date +"%Y_%m_%d_%H:%M:%S"`
zong=`free -m|awk 'NR == 2{print $2 " " $3}'|cut -d " " -f1`
yong=`free -m|awk 'NR == 2{print $2 " " $3}'|cut -d " " -f2`
sheng=$[ $zong - $yong ]
zhan=`echo "scale=1;$yong*100 / $sheng"|bc`
dong=`echo "scale=1;0.3*$1+0.7*$zhan"|bc`

echo "$dates  ${zong}M  ${sheng}M  ${zhan}%  ${dong}%"
