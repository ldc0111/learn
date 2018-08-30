时间

```shell
 date +%Y-%m-%d__%H:%M:%S
```

主机名

````shell
hostname   uname-n
````

os版本

```
uname -o
```

内核版本

````
uname -r
````

运行时间

````
uptime
uptime -p|tr " |" "_"
up_1_hour__34_minutes

````

平均负载

````
uptime|awk '{print $8 " "$9 " "$10}'
0.03, 0.02, 0.00

````





````
磁盘总量　磁盘已用总量
df -m|grep '^/dev'|awk 'BEGIN{total="";used="";} {total += $2; used += $3} END{printf "%s %s\n",total,used}'
470793 12754

````

````
内存总量　内存已用量
cat /proc/meminfo |head -n3
MemTotal:        8052580 kB
MemFree:         3671884 kB
MemAvailable:    5357268 kB

````

温度

````
cat /sys/class/thermal/thermal_zone0/temp 
41000

````

''