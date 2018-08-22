## bash shell

### 变量

#### 变量基础

* 什么是变量

  > 用一个简单的字眼替代比较复杂的或者是比较容易变动的数据

* 变量的设置规则

  > 1. 以等号链接，不能有空格，不能有特殊字符
  >
  > 2. 变量只能是英文字母与数字，但是开头字符不能是数字
  >
  > 3. 变量内容若有空格符可以使用双引号“”，单引号，将变量内容括起来
  >
  >    > 但是双引号内的特殊字符，仍保持原本的特性，
  >    >
  >    > 单引号的特殊字符则为一搬字符
  >
  > 4. 可以使用转义字符”\“将特殊字符将转化成一般字符
  >
  > 5. 在遗传命令中，还需要通过其他命令提供的信息，可以使用反单引号”\`命令\`“或”$（命令）“
  >
  > 6. 若该变量为了增加变量内容时，则可以用”$变量名称“或${变量}累加内容
  >
  >    > PATH="$PATH:/home/bin"
  >
  > 7. 若该变量需要在其他子进程执行，则需要以export 来使变量变成环境变量
  >
  >    > export PATH
  >
  > 8. 通常大写字符Wie系统默认变量，自行设置变量可以使用小写字符，方便判断
  >
  > 9. 取消变量的方法为”unset 变量名称“，取消

* 获取版本信息 uname -r

* 查看环境变量 env export  

* 用set查看所有变量（含环境变量与自定义变量）

* PS1命令提示符

* $ 关于本shell的回传码

* ？(关于上个执行命令的回传码)

* 影响显示结果的语系变量 locale

#### 变量键盘读取，数组与声明：read array daclare

````shell
read [] variable
-p:后面可以接提示付
-t:等待秒数
read named
》
declare/typeset
如果后面不加参数，declare会将所有变量内容都调出来
-a：将后面的名为valiable的变量定义成为数组，（array）类型
-i: 将后面名为valiable 的变量定义为整形数字
-x: 用法与export一样，就是将后面的variable 变成环境变量
-r: 将变量设置成为readonly 类型，该变量不可被更改内容，也不能重设
sum = 200 + 200 + 50
echo $sum //200 + 200 + 50
declare -i sum
echo $sum// 450

````

### 数组设置 array[index]="sdf"

echo ${array[index]

### 与文件系统级程序的限制关系 ulimit



### 变量的删除，代替与替换

​    删除

````shell
path=$PATH
echo $path
/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games:/sbin:/usr/sbin
echo ${path/*usr/local/bin:}
local/bin:/sbin
echo ${path#/*usr/local/bin:}
/usr/bin:/bin:/usr/local/games:/usr/games:/sbin:/usr/sbin

 echo ${path#/*:}
/usr/bin:/bin:/usr/local/games:/usr/games:/sbin:/usr/sbin
删除掉最短的那一个一个
echo ${path##/*:}
/usr/sbin
删除调最长的那个

echo ${path%:*}

/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games:/sbin
echo ${path%%:*}
/usr/local/bin

````

​    替换

```
echo ${path/sbin/SBIN}
/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games:/SBIN:/usr/sbin

```

> 变量替换方式 p315

替换 

````shell
echo $username
username=${username-root}
echo $username
root
username="tesla"
echo $username
tesla
````



### 变量别名的设置 alias unalias

````
alias lm= 'ls -l'
````



### 历史命令 history

* n: 数字 显示最近的n行
* -c：将目前的shell中所有的history 内容全部清除
* -a 将新增的history 命令新增入histfiles 中，若没有加 histfiles，则默认写实/.bashrc_history
* -r：将histfiles的内容读到目前这个shell的histor记忆中
* -w：将目前的history记忆内容写入histfiles



```
！number  执行第几条命令的意思
!command  执行最近的一command开头的命令
！！执行上一个命令

```

统一账号多次登录bash问题，最后一个把之前的都覆盖掉

### bash shell的操作环境

#### 路径与命令查找顺序

1. 以相对/绝对路径执行命令，例如 “/bin/ls”或“./ls”
2. 由alias找到命令来执行
3. 有bash内置的（builtin）命令来执行
4. 通过$PASH 这个变量的顺序找到的第一个命令来执行vim 





#### bash环境的配置文件

1. /etc/profile /etc/inouttrc   /etc/profile/*.sh  /etc/sysconfig/i18n 

2. ~/.bash_profile  ~/.bashrc    /etc/bashrc

3. 开始操作bash

配置完成之后用source将配置文件读入目前的shell文件



终端机的环境配置：stty set

stty  -a



#### 数据流重定向

标准输入，标准输出，标准错误

/dev/null黑洞  

命令执行判断依据：；，&& ||

### 管道

#### cat

-d 后面接分隔符 与-f 一起使用 

-f 依据-d的分隔符将一段信息切割成段，用-f取出第几段的意思

-c 以字符的单位取出固定字符区间



#### grep

正向，反向选择，忽略大小写



#### sort

忽略大小写排序

````shell
last|cut -d " " -f1| sort|uniq 

reboot
tesla
wtmp


last|cut -d " " -f1| sort|uniq -c
      1 
      9 reboot
     13 tesla
      1 wtmp

````

#### wc

````shell
last|grep [a-zA-Z]| grep -v "wtmp"|wc -l
22
cat /etc/manpath.config |wc
    131     715    5174
   行数    字数    字符数
````

### tee双向重定向

定向的同时，输出到 标准输出

### 字符串替换命令 tr col join paste expand



````shell
last| tr [a-z] [A-Z]
TESLA    TTY6                          WED AUG 22 19:30   STILL LOGGED IN
TESLA    TTY5                          WED AUG 22 19:24   STILL LOGGED IN
TESLA    TTY1         :0               WED AUG 22 19:00   STILL LOGGED IN

cat /etc/passwd|tr -d ":"
rootx00root/root/bin/bash
daemonx11daemon/usr/sbin/usr/sbin/nologin

-s将多个连续的字符串当成一个处理
last| tr -s " " " "
tesla tty6 Wed Aug 22 19:30 still logged in
tesla tty5 Wed Aug 22 19:24 still logged in

````

col  -t将tab键换成空格键，-b在文字内有反斜杠（/）时，仅保存反斜杠最后的那个字符



join 是将两个文件中有相同数据的那一行加在一起，他 -t -i -1 -2

paste 直接将两行贴在一起，中介用tab键隔开

expand 就是将【tab】按键转成空格键，

切割命令 split 如果 一个文件太大了便携式设备就无法复制，所以split可以将文件分成若干个小文件

-b 切割成的文件大小   -l以行数来切割成为小文件 

```
split -b 300k /exc/termcap termcap
ls termcap
termcapaa
termcapab
termcapac
cat termcap*>> termcap
```

xargs 读入stdin的数据，并且以空格付或断行符进行分析 以空格将数据分割

````
cut -d ":" -f1 /etc/passwd |head -n 3|xargs
root daemon bin

````



\- 符号 在管道中应用， 将生成文件的操作 发给stdout

````shell
tar -cfv - /home|tar -xvf - 
这个是将home下的文件打包，但是不记录打包文件，而是传送到stdout中去后一个的stdin中去 经过管道后 后一个的tar  -提取stdout，因此就不用使用文件了
````



