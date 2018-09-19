##　任务需求

### ls

![](/home/tesla/github/learn/ｃ语言/ls实现/深度截图_选择区域_20180917155442.png)

### ls -a

![](/home/tesla/github/learn/ｃ语言/ls实现/深度截图_选择区域_20180917155541.png)

### ls -l

![](/home/tesla/github/learn/ｃ语言/ls实现/深度截图_选择区域_20180917155718.png)

### ls －ａｌ

![](/home/tesla/github/learn/ｃ语言/ls实现/深度截图_选择区域_20180917154954.png)



````shell
ls -a -l
ls -l -a
ls -al
ls -la
ls -a
ls -l
````

##　任务所需知识

1. 获取文件信息
2. 配色问题

###　头文件

````cpp
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

````

参考网址

https://blog.csdn.net/u013007900/article/details/51019433

https://wenku.baidu.com/view/9c92849b998fcc22bdd10d24.html

## 任务思路





##　任务实现