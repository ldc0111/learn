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
home bash 100

sudo


 last tesla4|wc -l
5
last tesla4|sed -n '2p'
tesla4   pts/1                         Sun Aug 26 12:40 - 12:41  (00:01)
s
````

