#*************************************************************************
#	> File Name: gesiofsysop.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年08月26日 星期日 18时10分00秒
#*************************************************************************
#General situation of system operation
#!/bin/bash
dates=`date +%Y-%m-%d__%H:%M:%S`
st=`hostname`
os=`uname -o`
v=`uname -r`
longtime=`uptime -p|tr " " "_"`
#aveload=(`uptime|tr "," " "|awk '{print $8 " "$9 " "$10}'`)
aveload=(` cat /proc/loadavg |cut -d " " -f1-3 `)
totusd=(`df -m|grep '^/dev'|awk 'BEGIN{total=""; used=""} {total += $2; used += $3} END{print total " " used}'`)
totusd[1]=$[ ${totusd[1]} * 100 / ${totusd[0]} ]
mem=( `cat /proc/meminfo |head -n3` )
mem[0]=$[ ${mem[4]} * 100 / ${mem[1]} ]
temperature=$[`cat /sys/class/thermal/thermal_zone0/temp` / 1000]

if [[ ${totusd[1]}  < 80 ]] ; then
    ts=normal
elif [[ ${totusd[1]}  < 90 ]] ; then
    ts=note
else
    ts=waring
fi 

if [[ $temperature  < 50 ]] ; then
    tc=normal
elif [[ $temperature  < 70 ]] ; then
    tc=note
else
    tc=waring
fi 

if [[ ${mem[0]}  < 70 ]] ; then
    tm=normal
elif [[ ${mem[0]}  < 80 ]] ; then
    tm=note
else
    tm=waring
fi 
echo "$dates $st $os $v $longtime ${aveload[0]} ${aveload[1]} ${aveload[2]} ${totusd[0]} ${totusd[1]}% ${mem[1]} ${mem[0]}% $temperature $ts $tc $tm"
