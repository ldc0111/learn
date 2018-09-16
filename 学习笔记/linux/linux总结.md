###　目录结构



###　文件类型

1. l
2. d
3. pipe
4. link(软链接　硬链接)
5. block
6. c
7. socket

文件存储：



###　配置文件

系统初始化

````shell
/etc/inintab  运行级别　　控制台数量
/etc/timezone　市区
/etc/inetd.conf　超级进程
````

文件系统

````shell
/etc/fstab 开机时挂载的文件系统
/etc/mtab　　当前挂载的文件系统
````

用户系统

````shell
/etc/passwd    用户信息
/etc/shadow　 　用户密码
/etc/group　　　群组信息
/etc/gshadow　　群组密码
/etc/sudoers　　ｓｕｄｏer列表
````

ｓｈｅｌｌ

````
/etc/shells　　　可用ｓｈｅｌｌ列表
/etc/inputrc　　ｒｅａｄｌｉｎｅ控件设定
/etc/profile　　用户首选项
/etc/bashrc　　ｂａｓｈ配置文件

bash
profile
bash.bashrc
bash.bash.logout
bash.profile
bash.logout
inputrc
````

系统环境

````
/etc/environment  环境变量
/etc/updatedb.conf 文件检索数据配置
/etc/issue　　　　　　发行信息
/etc/screenrc     屏幕设定
````

网络

````
/etc/iftab　　　　　网卡ｍａｃ地址
/etc/hosts　　　　　主机列表
/etc/hostname　　　主机名
/etc/resolv.conf　域名解析服务器地址
/etc/network/interfaces　网卡配置文件
````

用户配置文件

.bash_rc .bash_profile  .bash_logout

###　软件管理

```
apt-get install *
apt-get --purge remove *
apt-get update *
apt-get upgrade *
apt-cache search a|grep

apt-get automove
apt-get install -f /修复依赖关系

```



###　环境变量

ＰＴＴＨ

ＨＯＭＥ

ＳＨＥＬＬ

ＬＯＮＧ

ＨＩＳＴＳＩＺＥ



###　命令

1. bg

2. fg

3. jobs

4. id

5. apt-get install / remove / update/ upgrade / search

6. uptime

7. who

8. last

9. date

10. w

11. whoami

12. logname

13. uname      -a

14. cal

15. cd

16. mkdir

17. rmdir

18. pwd

19. ls

20. rm

21. basename  |dirname

22. cp

23. mv

24. cat

25. nl

26. less

27. tail

28. tac

29. more

30. head

31. touch  修改文件时间

32. chattr

33. lsattr

34. which

35. locate　数据库

36. whereis　数据库

37. updatedb

38. find

39. stat

40. cut

41. sort

42. uniq

43. split

44. tr

45. grep

46. wc

47. tee

48. xargs

49. su

50. passwd

51. chsh

52. useradd

53. id

54. sudo

55. gpasswd

56. usermod

57. userdel

58. free

59. dstat

60. htop

61. nmon

62. pstree

63. kill

64. top

65. ps

66. pgrep

67. pkill

    