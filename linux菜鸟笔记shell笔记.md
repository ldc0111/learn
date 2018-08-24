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



#### grep

```shell
grep -n 'the' regular_express.txt 
8:I can't finish the test.
12:the symbol '*' is represented as start.
15:You are the best is mean you are the no. 1.
16:The world <Happy> is the same with "glad".
18:google is the best tools for search keyword.

grep -n -v 'the' regular_express.txt 
1:"Open Source" is a good mechanism to develop programs.
2:apple is my favorite food.
3:Football game is not use feet only.
4:this dress doesn't fit me.
5:However, this dress is about $ 3183 dollars.
6:GNU is free air not free beer.
7:Her hair is very beauty.
9:Oh! The soup taste good.
10:motorcycle is cheap than car.
11:This window is clear.
13:Oh!	My god!
14:The gd software is a library for drafting programs.
17:I like dog.
19:goooooogle yes!
20:go! go! Let's go.
21:# I am VBird
22:

#不论大小写
grep -in 'the' regular_express.txt 
8:I can't finish the test.
9:Oh! The soup taste good.
12:the symbol '*' is represented as start.
14:The gd software is a library for drafting programs.
15:You are the best is mean you are the no. 1.
16:The world <Happy> is the same with "glad".
18:google is the best tools for search keyword.

grep -n 't[ae]st' regular_express.txt 
8:I can't finish the test.
9:Oh! The soup taste good.

grep -n 'oo' regular_express.txt 
1:"Open Source" is a good mechanism to develop programs.
2:apple is my favorite food.
3:Football game is not use feet only.
9:Oh! The soup taste good.
18:google is the best tools for search keyword.
19:goooooogle yes!


#oo前面没有g
grep -n '[^g]oo' regular_express.txt 
2:apple is my favorite food.
3:Football game is not use feet only.
18:google is the best tools for search keyword.
19:goooooogle yes!

grep -n '[^a-z]oo' regular_express.txt 
3:Football game is not use feet only.


grep -n '[0-9]' regular_express.txt 
5:However, this dress is about $ 3183 dollars.
15:You are the best is mean you are the no. 1.

grep -n '[^[:lower:]]oo' regular_express.txt 
3:Football game is not use feet only.

grep -n '[[:digit:]]' regular_express.txt 
5:However, this dress is about $ 3183 dollars.
15:You are the best is mean you are the no. 1.


grep -n '^[a-z]' regular_express.txt 
2:apple is my favorite food.
4:this dress doesn't fit me.
10:motorcycle is cheap than car.
12:the symbol '*' is represented as start.
18:google is the best tools for search keyword.
19:goooooogle yes!
20:go! go! Let's go.

 grep -n '^the' regular_express.txt 
12:the symbol '*' is represented as start.

#不想要开头是英文字母的
grep -n '^[^a-zA-Z]' regular_express.txt 
1:"Open Source" is a good mechanism to develop programs.
21:# I am VBird

#行尾部是.
grep -n '\.$' regular_express.txt 
1:"Open Source" is a good mechanism to develop programs.
2:apple is my favorite food.
3:Football game is not use feet only.
4:this dress doesn't fit me.
10:motorcycle is cheap than car.
11:This window is clear.
12:the symbol '*' is represented as start.
15:You are the best is mean you are the no. 1.
16:The world <Happy> is the same with "glad".
17:I like dog.
18:google is the best tools for search keyword.
20:go! go! Let's go.

grep -n '^$' regular_express.txt 
22:
#不要空白行，和注释开头的行
grep -v "^$" regulat_express.txt| grep -v "^#"
#.代表一定有一个任意字符的意思
 grep -n 'g..d' regular_express.txt 
1:"Open Source" is a good mechanism to develop programs.
9:Oh! The soup taste good.
16:The world <Happy> is the same with "glad".

# * 代表重复前面一个0到无穷多次的意思， 为组合形态
 grep -n 'ooo*' regular_express.txt 
1:"Open Source" is a good mechanism to develop programs.
2:apple is my favorite food.
3:Football game is not use feet only.
9:Oh! The soup taste good.
18:google is the best tools for search keyword.

grep -n 'g.*g' regular_express.txt 
1:"Open Source" is a     good mechanism to develop prog    rams.
14:The    gd software is a library for drafting prog    rams.
18:goog    le is the best tools for search keyword.
19:goooooog   le yes!
20:go! go! Let's g    o.


grep -n 'o\{2,5\}g' regular_express.txt 
18:google is the best tools for search keyword.
19:goooooogle yes!

grep -n 'go\{2,5\}g' regular_express.txt 
18:google is the best tools for search keyword.

grep -n 'go\{2,\}g' regular_express.txt 
18:google is the best tools for search keyword.
19:goooooogle yes!

```



### sed

```shell
nl /etc/passwd |sed '2,5d'
     1	root:x:0:0:root:/root:/bin/bash
     6	games:x:5:60:games:/usr/games:/usr/sbin/nologin
     7	man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
##删除第二行
nl /etc/passwd |sed '2d'
     1	root:x:0:0:root:/root:/bin/bash
     3	bin:x:2:2:bin:/bin:/usr/sbin/nologin

##删除第三行到最后一行
nl /etc/passwd |sed '3,$d'
     1	root:x:0:0:root:/root:/bin/bash
     2	daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
##在第一行后面加上一个dirnk tea
nl /etc/passwd |sed '1adrink tea'
     1	root:x:0:0:root:/root:/bin/bash
drink tea
     2	daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin

nl /etc/passwd |sed '2,5c No 2-5 number'
     1	root:x:0:0:root:/root:/bin/bash
No 2-5 number
     6	games:x:5:60:games:/usr/games:/usr/sbin/nologin
     
 nl /etc/passwd |sed -n '2,3p'
     2	daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
     3	bin:x:2:2:bin:/bin:/usr/sbin/nologin


ifconfig| grep 'inet[^0-9]'
        inet 127.0.0.1  netmask 255.0.0.0
        inet 192.168.1.156  netmask 255.255.255.0  broadcast 192.168.1.255

ifconfig| grep 'inet[^0-9]'|sed 's/^.*inet //g'
127.0.0.1  netmask 255.0.0.0
192.168.1.156  netmask 255.255.255.0  broadcast 192.168.1.255

ifconfig| grep 'inet[^0-9]'|sed 's/^.*inet //g'|sed 's/netmask.*//g'
127.0.0.1  
192.168.1.156  

ifconfig| grep 'inet[^0-9]'|sed 's/^.*inet //g'|sed 's/netmask.*//g'|\
> sed -n '2p'
192.168.1.156  

#将尾部的.$替换成！
 sed -i 's/\.$/\!/g' regular_express.txt 


```

#### awk 

NF 每一行的字段数，
NR 目前awk 所处理的是第几行 数据

FS 目前的分割字符，默认是空格键



````shell
last -n 5|awk '{print $1 "\t" $3}'
tesla1	:1
tesla	:0
reboot	boot
tesla	:0
reboot	boot
	
wtmp	Tue

last -n 5|awk '{print $1 "\t lines:" NR "\t columes: " NF}'
tesla1	 lines:1	 columes: 10
tesla	 lines:2	 columes: 10
reboot	 lines:3	 columes: 10
tesla	 lines:4	 columes: 10
reboot	 lines:5	 columes: 11
	 lines:6	 columes: 0
wtmp	 lines:7	 columes: 7

cat /etc/passwd|awk '{FS=":"} $3 < 10 {print $1 "\t" $3}'
root:x:0:0:root:/root:/bin/bash	
daemon	1
bin	2
sys	3
sync	4
games	5
man	6

````



### diff  以行来比较

````shell
 cat /etc/passwd > passwd.old
 
 cat /etc/passwd|\
> sed -e '4d' -e '6c no six line' > passwd.new


diff passwd.old  passwd.new 
4d3
< sys:x:3:3:sys:/dev:/usr/sbin/nologin
6c5
< games:x:5:60:games:/usr/games:/usr/sbin/nologin
---
> no six line

````

#### cmp以字节来比较

````shell
cmp passwd.old  passwd.new 
passwd.old passwd.new 不同：第 120 字节，第 4 行

````

patch 更新wenjian

````shell
diff -Naur passwd.old passwd.new  > passwd.patch

cat passwd.patch 
--- passwd.old	2018-08-23 20:48:45.118994612 +0800
+++ passwd.new	2018-08-23 20:48:07.730739226 +0800
@@ -1,9 +1,8 @@
 root:x:0:0:root:/root:/bin/bash
 daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
 bin:x:2:2:bin:/bin:/usr/sbin/nologin
-sys:x:3:3:sys:/dev:/usr/sbin/nologin
 sync:x:4:65534:sync:/bin:/bin/sync
-games:x:5:60:games:/usr/games:/usr/sbin/nologin
+no six line
 man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
 lp:x:7:7:lp:/var/spool/lpd:/usr/sbin/nologin
 mail:x:8:8:mail:/var/mail:/usr/sbin/nologin

 patch -p0 < passwd.patch 
patching file passwd.old

#恢复更新
 patch -R -p0 < passwd.patch 
patching file passwd.old

````



### tr打印

