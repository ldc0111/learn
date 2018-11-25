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
aveload=(` cat /proc/loadavg |cut -d " " -f1-3 `)
totusd=(`df -m|grep '^/dev'|awk 'BEGIN{total=""; used=""} {total += $2; used += $3} END{print total " " used}'`)
totusd[1]=$[ ${totusd[1]} * 100 / ${totusd[0]} ]
mem=( `cat /proc/meminfo |head -n3` )
mem[0]=$[ ${mem[4]} * 100 / ${mem[1]} ]
temperature=$[`cat /sys/class/thermal/thermal_zone0/temp` / 1000]

tscm=( `echo 1|awk -v ts=$totusd[1] -v tc=$temperature -v tm=${mem[0]} \
    'BEGIN{tsc[0]="normal"; tsc[1]="note"; tsc[2]="waring"} \
    {ts=(ts > 80) + (ts > 90); tc=(tc > 50) + (tc > 70); tm=(tm >70) + (tm > 80)} \
    END{printf "%s %s %s",tsc[ts],tsc[tc], tsc[tm]}'` )

echo "$dates $st $os $v $longtime ${aveload[0]} ${aveload[1]} ${aveload[2]} ${totusd[0]} ${totusd[1]}% ${mem[1]} ${mem[0]}% $temperature ${tscm[0]} ${tscm[1]} ${tscm[2]}"
