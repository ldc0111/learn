### 第一个

#### 磁盘信息获取

````shell
#!/bin/bash
df -m|grep '^/dev'|awk 'BEGIN{total="" ; used=""; p="" } { total= total +$2 ; used = used + $3 ; printf "%s\t1\t%20s\t%s\t%s\t%s\n",dates,$6,$2,$3,$5} END{p=used *100 /total ; printf "%s\t0\t%20s\t%s\t%s\t%.0d%%\t\n",dates,"disk",total,used,p}' dates=`date +%Y-%m-%s__%H:%M:%S`
##df　-m 获取磁盘信息
## grep 筛选出以/ｄｅｖ 开头的
##awk处理数据
## 获取外部变量时间信息

````

![](/home/tesla/Pictures/jietu/20180828122710.png)

#### 第二个

##### 系统运行概况

时间

````shell
date=`date +%Y-%m-%d__%H:%M:%S`
````



主机名

````shell
st=`hostname`
````



os版本

````shell
os=`uname -o`
````

内核版本

````shell
v=`uname -r`
````

运行时间

````shell
longtime=`uptime -p|tr " " "_"`
````

平均负载

````shell
aveload=( `cat /proc/loadavg |cut -d " " -f1-3 ` )
````

磁盘总量 磁盘已用

````shell
totusd=(`df -m|grep '^/dev'|awk 'BEGIN{total=""; used=""} {total += $2; used += $3} END{print total " " used}'`)
totusd[1]=$[ ${totusd[1]} * 100 / ${totusd[0]} ]

````



内存大小内存已用

````shell
mem=( `cat /proc/meminfo |head -n3` )
mem[0]=$[ ${mem[4]} * 100 / ${mem[1]} ]
````



cpu温度

````shell
temperature=$[`cat /sys/class/thermal/thermal_zone0/temp` / 1000]
````



磁盘报警级别,内存报警级别,cpu报警级别

````shell
tscm=( `echo 1|awk -v ts=$totusd[1] -v tc=$temperature -v tm=${mem[0]} \
    'BEGIN{tsc[0]="normal"; tsc[1]="note"; tsc[2]="waring"} \
    {ts=(ts > 80) + (ts > 90); tc=(tc > 50) + (tc > 70); tm=(tm >70) + (tm > 80)} \
    END{printf "%s %s %s",tsc[ts],tsc[tc], tsc[tm]}'` )

#ts　tc tm　的计算非常棒
````

![](/home/tesla/Pictures/jietu/20180828125027.png)

#### 第三个

##### cpu信息获取

cpu占用率

````shell
cpuzlog1=( `cat /proc/stat|head -n1|awk '{print $2" "$3" "$4" "$5" "$6" "$7" "$8}'` )
sys_id1=${cpuzlog1[3]}
total1=$( echo ${cpuzlog1[@]}|awk '{print $1+$2+$3+$4+$5+$6+$7}' )
sleep 0.5
cpuzlog2=( `cat /proc/stat|head -n1|awk '{print $2" "$3" "$4" "$5" "$6" "$7" "$8}'` )
sys_id2=${cpuzlog2[3]}
total2=$( echo ${cpuzlog2[@]}|awk '{print $1+$2+$3+$4+$5+$6+$7}' )

sys_id=`expr $sys_id2 - $sys_id1`
total=`expr $total2 - $total1`
sys_usage=`expr "scale=3; $sys_id / $total * 100"|bc -l`
sys_Rate=`expr 100-$sys_usage|bc -l`
disp_sys_rate=`expr "scale=3; $sys_Rate / 1"|bc`
````

温度

````shell
temperatur=`cat /sys/class/thermal/thermal_zone0/temp`
````



时间

````shell
datess=`date +%Y-%m-%d__%H:%M:%S`
````

负载和数据处理

````shell
cat /proc/loadavg |awk -v rate=$disp_sys_rate -v dates=${datess} -v temperature=${temperatur} '
    BEGIN{temp="" ; ts[0]="normal"; ts[1]="note"; ts[2]="waring"; m1=""; m5=""; m15=""}
    {m1=$1; m5=$2; m15=$3}
    {temp=(temperature > 50000) + (temperature > 70000)}
    {temperature /= 1000}
    END{printf "%s %s %s %s %.2f %.2f°C %s\n",dates,m1,m5,m15,rate,temperature,ts[temp]}'
````

![](/home/tesla/Pictures/jietu/20180828130417.png)