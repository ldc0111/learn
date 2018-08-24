#!/bin/bash

dates=`date +"%Y_%m_%d_%H:%M:%S"`
zong=`free -m|awk 'NR == 2{print $2}'`
yong=`free -m|awk 'NR == 2{print $3}'`
sheng=$[ $zong - $yong ]
zhan=`echo "scale=1;$sheng*100 / $zong"|bc`
dong=`echo "scale=1;0.3*$1+0.7*$zhan"|bc`

echo "$dates  ${zong}M  ${sheng}M  ${zhan}%  ${dong}%"
