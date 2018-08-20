### man手册中文化

> sudo apt-get install manpages-zh
>
> sudo gedit /etc/manpath.config
>
> 将所有的/usr/share/man替换为/usr/share/man/zh_CN
>
> 保存

### date时间显示

###  cal日历显示

### bc计算器

### [tab]按键

### man page

1. 用户在shell环境中可以操作的命令或可执行文件
2. 系统内核可调用的函数与工具
3. 一些常用的函数与函数库，大部分为c的函数库
4. 设备文件的说明，通常在/dev的文件
5. 配置文件或者是某些文件的格式
6. games
7. 惯例与协议等，例如Linux文件系统，网络协议，ascii code 等说明
8. 系统管理圆可用的管理命令
9. 跟kernei 有关的文件



* NAME 数据名称
* SYNOPSIS 简要 简短的命令执行语法
* DESCRIPTION 描述 较为完整的说明 重
* OPTIONS 选项列举的所有可用的选项说明 
* COMMANDS  命令 当这个程序（软件）在执行的时候，可以在此程序（软件）重执行的命令
* FILES 这个程序或数据所使用或参考或链接到的某些文件
* SEE ALSO这个命令或数据有关的其他说明
* EXAMPLE一些可以参考的范例
* BUGS是否有相关的错误
* AUTHORS



n 继续向下查询 N逆向查询   q退出 

### shutdown 关机 reboot 重启 

### 忘记root密码的设置

见鸟哥135pages



### ssh免密码登录

> A为本地主机(即用于控制其他主机的机器) ;
> B为远程主机(即被控制的机器Server), 假如ip为172.24.253.2 ;
> A和B的系统都是Linux
>
> 在A上的命令:
>
> ssh-keygen -t rsa (连续三次回车,即在本地生成了公钥和私钥,不设置密码)
>
> ssh root@172.24.253.2 "mkdir .ssh;chmod 0700 .ssh" (需要输入密码， 注:必须将.ssh的权限设为700)
>
> scp ~/.ssh/id_rsa.pub root@172.24.253.2:.ssh/id_rsa.pub (需要输入密码)
>
> 在B上的命令:
>
> touch /root/.ssh/authorized_keys (如果已经存在这个文件, 跳过这条)
>
> chmod 600 ~/.ssh/authorized_keys  (# 注意： 必须将~/.ssh/authorized_keys的权限改为600, 该文件用于保存ssh客户端生成的公钥，可以修改服务器的ssh服务端配置文件/etc/ssh/sshd_config来指定其他文件名）
>
> cat /root/.ssh/id_rsa.pub  >> /root/.ssh/authorized_keys (将id_rsa.pub的内容追加到 authorized_keys 中, 注意不要用 > ，否则会清空原有的内容，使其他人无法使用原有的密钥登录)



### change group    change own    change mod

chgrp chown chmod

改变用户所属组，改变所属用户，改变文件的权限

### FHS目录定义

1. /bin 系统有很多放置执行文件的目录，但/bin比较特殊。因为/bin放置的是单用户维护模式下还能够被操作系统操作的命令，在/bin下面的命令可以被root与一般账号所使用，主要有cat chmod chown date mv mkdir cp bash 

2. /boot 这个目录主要放置开机会使用到的文件，包括Linux内核文件及开机菜单与开机所需的配置文件

   linux kernel 常用的文件名为vmlinuz,如果使用的是grub 这个引导装载程序，则会存在/boot/grub/这个目录

3. /dev在linux系统上，任何设备与接口都是以文件的形式存在与这个目录当中的。你只要通过这个目录下面的某个文件，就等于访问某个设备。比较重要的文件有/dev/null, dev/zero, /dev/tty, /dev/lp\*, /dev/hd, /dev/sd\*

4. /etc 系统主要的配置文件几乎都放置在这个目录内，例如人员的账号密码文件，各种服务的起始文件等，一般来说这个目录下的各个文件是可以让一般用户查阅的，但是只有root有权利修改，FHS建议不要放置可执行文件，在这个目录中

5. /home这是系统默认的用户住文件夹，在你创建一个一般账号时默认的用户主文件夹都会规范到这里来，比较重要的是，主文件夹有两种代号，～：代表目前这个用户的主文件夹，～dmtsai：则代表dmtsai的主文件夹

6. /lib系统的函数库非常多，而/lib放置的则是开机时会用到的函数库，以及在/bin 或/sbin下面的命令会调用函数库而已，什么是函数库呢？ 你可以将它想想成是外挂，某些命令必须要有这些外挂才能够顺里完成程序的执行之意，尤其重要的是/lib/modules/这个目录，，因为该目录会放置内核相关的模块

7. /media media是媒体文件 英文顾名思意，这个/media 下面放置的就是可删除的设备，包括软盘，光盘，dvd等设备都暂时挂载于此，

8. /mnt如果你想暂时挂载某些额外的设备，一般建议你可以放置到这个目录中，在比较早的时候，这个目录的用途与media相同，只是有了/media之后，这个目录就用来暂时挂载了

9. /opt这个是给第三方软件放置的目录，

10. /root系统管理员的主文件夹，之所以放在这里，是因为如果进入单用户维护模式而仅挂载根目录时，该目录就能够拥有root的主文件夹，，所以我们会希望root的主文件夹与跟目录放置在同一个分区

11. /sbin linux有非常多的命令是用来设置系统环境的，这些命令只有root才能够利用来，设置系统，其他用户最多只能用来查询而已，放在/sbin下面的为开机过程中所需要的，里面包括了开机，修复，还原系统所需要的命令

12. /srv srv可以视为“service”的缩写，是一些网络服务启动之后，这些服务所需要取用的数据目录，常见的服务例如www.FTP 等

13. /tmp 这是让一般用户或者正在执行的程序放置文件的地方，这个目录是任何人都能访问，所以你需要定期清理一下，

### 版本查看　uname -r

lsb_release -a



### cd change directory



### pwd



### mkdir

-p 多级创建

-ｍ 加权限

#### rmdir 删除空目录  -p 多层删除



### ls

递全排属色号那



### cp [-adfilprsu] 源文件　目标文件

递属比链



### rm -irf

### mv -ifu

### basename  dirname

纯碎的字符串检查

###　文件内容查阅

* cat:由第一行开始显示内容
* tac 从最后一行开始显示，可以看出tac 是ｃａｔ的到写形式
* nl显示的时候顺便显示行号、\** 上下左右宽　
* more 一页一页的文件内容显示
* less 与more类似，但是比more更好的是，他可以往前翻页
* head只看头几行
* tail 只看尾几行
* od 以二进制的方式读取文件内容

````shell
#显示行号指定几行
man ls|nl -b a -w 8 -n rz|head -120|tail -20
````



### touch 修改文件时间或者创建新文件

* modification time (mtime) 当该文件“内容”更改时，就会更改这个时间
* status time (ctime) 状态被改变时，会改变，像是权限与属性被更改了，都会更新这个时间，像是权限与属性
* access time　(atime) 当”文件的内容被取用“时，就会更新这个读取时间



### ｕmask －ｓ 用户所在的新建目录时默认的权限是什么 显示的是拿掉的分数

或者修改权限

### 文件隐藏属性　chattr lsattr

只能ａ加不能删，ｉ不能写，不能删，删，牛逼哄哄　ｐ183

### SUID SGID SBIT

* setUID　s　出现在文件上时，ＳＵＩＤ只对二进制程序有　效执行者将有该程序所有者的权限　passwd
* setGID    s   出现在文件夹上时，用户有rx时可以进入该目录，，进入后用户的有效组会变成目录的有效组
* setBIT　ｔ  出现在文件夹上，除了和管理员和本用户，别的用户不能删除本用户的东西



### sudo apt-cache search ifconfig*

### which寻找执行文件 whereis寻找特定文件　locate 加上部分文件名就可以包括文件夹下的所有文件(数据库中查找　updatedb)



### find[PATH]- [op]-[action] 有时间参数截取时间段 用户　组　权限　命令　打印 大小

* mtime 天
* atime
* ctime





### df

