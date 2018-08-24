### 一

#### 时间

```shell
dates=`date +"%Y_%m_%d_%H:%M:%S"`
```

总内存

````shell
zong=`free -m|awk 'NR == 2{print $2}'`
##输出第二行总内存
````

用的内存

````shell
yong=`free -m|awk 'NR == 2{print $2}'`
##输出用的内存
````

剩余内存

````shell
sheng=$[ $zong - $yong ]
## 计算剩余的内存
````

占的百分比

````shell
zhan=`echo "scale=1;$sheng*100 / $zong"|bc`
## 计算占有的百分比
````

动态百分比

```shell
dong=`echo "scale=1;0.3*$1+0.7*$zhan"|bc`
## 计算动态百分比
```





![](/home/tesla/Pictures/2018_8_241.png)





二



时间 用户总数 （非系统用户） 近期活跃用户（3） 具有root权限的用户 当前在线用户\_登录ip\_TTY

#### 时间

````shell
dates=`date +"%Y_%m_%d_%H:%M:%S"`

````

#### 用户总数

````shell
cat /ete/passwd|grep "bash"|cut -d ":" -f1|wc -w
##因为一般用户用的都是bash语言 选出bash开头的
## cut 截取 用户名，
## wc -w 统计单词数
````

#### 前三

````shell
 last|head -n-2|cut -d " " -f1|sort|uniq -c|sort -nr
 ##head -n-2 不显示莫尾两行
 ##sort 尾uniq做准备
 ## uniq -c 统计相同的单词
 ## sort排序以纯数字方式反向排序
````

#### 具有root权限的用户

````shell
cat /etc/group|grep "sudo"|cut -d ":" -f4
##在/etc/group里面记录的是所有用户组，
##选取有sudo 组的用户
##选取所有用户
````

#### 当前在线用户\_登录ip\_TTY

````shell
who|awk '{print $1 $5 $2}'|tr "(\|)" "_"
##列出当前所在的用户
##输出按序输出在线用户 登录ip tty 
##将（） 替换成_
````

![](/home/tesla/Pictures/201808242.png)