#*************************************************************************
#	> File Name: cpui.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年08月27日 星期一 17时12分14秒
#*************************************************************************

#!/bin/bash
cpuzlog1=( `cat /proc/stat|head -n1|awk '{print $2" "$3" "$4" "$5" "$6" "$7" "$8}'` )
sys_id1=${cpuzlog1[3]}
total1=$( echo ${cpuzlog1[@]}|awk '{print $1+$2+$3+$4+$5+$6+$7}' )
#echo $sys_id1" "$total1
sleep 0.5
cpuzlog2=( `cat /proc/stat|head -n1|awk '{print $2" "$3" "$4" "$5" "$6" "$7" "$8}'` )
sys_id2=${cpuzlog2[3]}
total2=$( echo ${cpuzlog2[@]}|awk '{print $1+$2+$3+$4+$5+$6+$7}' )
#echo $sys_id2" "$total2

sys_id=`expr $sys_id2 - $sys_id1`
#echo $sys_id
total=`expr $total2 - $total1`
#echo $total
sys_usage=`expr "scale=3; $sys_id / $total * 100"|bc -l`
#echo $sys_usage
sys_Rate=`expr 100-$sys_usage|bc -l`
disp_sys_rate=`expr "scale=3; $sys_Rate / 1"|bc`
#echo $disp_sys_rate%
datess=`date +%Y-%m-%d__%H:%M:%S`
temperatur=`cat /sys/class/thermal/thermal_zone0/temp`

uptime |tr "," " "|awk -v rate=$disp_sys_rate -v dates=${datess} -v temperature=${temperatur} '
    BEGIN{temp="" ; ts[0]="normal"; ts[1]="note"; ts[2]="waring"; m1=""; m5=""; m15=""}
    {m1=$8; m5=$9; m15=$10}
    {temp=(temperature > 50000) + (temperature > 70000)}
    {temperature /= 1000}
    END{printf "%s %s %s %s %.2f %.2f°C %s",dates,m1,m5,m15,rate,temperature,ts[temp]}'



