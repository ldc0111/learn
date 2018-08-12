#!/bin/bash

val=`expr 2 + 2`
echo "两数之和：　$val"

#算数运算
a=10
b=20
val=`expr $a + $b`
echo "a + b: $val"

val=`expr $a - $b`
echo "a - b: $val"

val=`expr $b \* $a`
echo "b * a: $val"

val=`expr $a / $b`
echo "a / b: $val"


#关系运算
if [ $a == $b ]
then
    echo "a 等于 b"
fi
if [ $a != $b ]
then
    echo "a 不等于 b"
fi
if [ $a -eq $b ]
then
    echo  "$a -eq $b: a 等于 b"
 else
     echo "$a -eq $b: a 不等于 b"
 fi
 if [ $a -ne $b ]
 then
     echo "$a -ne $b: a 不等于 b"
 else
     echo "$a -ne $b: a 等于 b"
 fi
 if [ $a -gt $b ]
 then
     echo "$a -gt $b: a 大于 ｂ"
 else
     echo "$a -gt $b: a 不大于 b"
 fi
 if [ $a -lt $b ]
 then
     echo "$a -lt $b: a 小于 b"
 else
     echo "$a lt $b:  a 不小于 ｂ"
 fi
 if [ $a -ge $b ]
 then
     echo "$a -ge $b: a 大于或等于 ｂ"
 else
     echo "$a -ge $b: a 小于 b"
 fi
 if [ $a -le $b ]
 then
     echo "$a -le $b: a 小于或等于 ｂ"
 else
     echo "$a -le $b: a 大于 b"
 fi


#布尔运算
if [ $a != $b ]
then
    echo "$a != $b: a 不等于 b"
else
    echo "$a != $b: a 等于 b"
fi
if [ $a -lt 100 -a $b -gt 15 ]
then
    echo "$a 小于　100 且　$b 大于 15: 返回　true"
else
    echo "$a 小于　100　且　$b 大于 15: 返回　flase"
fi
if [ $a -lt 100 -o $b -gt 100 ]
then
    echo "$a 小于　100 或　$b 大于 100: 返回　true"
else
    echo "$a 小于　100　或　$b 大于 100: 返回　flase"
fi
if [ $a -lt 5 -o $b -gt 100 ]
then
    echo "$a 小于 5 或　$b 大于　100: 返回　true"
else
    echo "$a 小于 5　或 $b 大于　100: 返回　flase"
fi

#逻辑运算
if [[ $a -lt 100 && $b -gt 100 ]]
then
    echo "返回 ture"
else
    echo "返回　false"
fi
if [[ $a -lt 100 || $b -gt 100 ]]
then
    echo "返回　true"
else
    echo "返回　flase"
fi

#字符串运算符
a="abc"
b="efg"

if [ $a = $b ]
then
    echo "$a = $b : a 等于　b"
else
    echo "$a = $b : a 不等于 b"
fi
if [ $a != $b ]
then
    echo "$a != $b: a 不等于 b"
else
    echo "$a != $b: a 等于 b"
fi
if [ -z "$a" ]
then
    echo "-z $a: 字符串的长度为　０"
else
    echo "-z $a; 字符串的长度不为　０"
fi
if [ -n "$a" ]
then
    echo "-n $a: 字符串不为空"
else
    echo "-n $a: 字符串为空"
fi
if [ $a ]
then
    echo "$a: 字符串不为空"
else
    echo "$a: 字符串为空"
fi

#文件测试运算符

file="/home/lidecao/184"
if [ -r $file ]
then
    echo "文件可读"
else
    echo "文件不可读"
fi
if [ -w $file ]
then
    echo "文件可写"
else
    echo "文件不可写"
fi
if [ -x $file ]
then
    echo "文件可执行"
else
    echo "文件不可执行"
fi
if [ -f $file ]
then
    echo "文件为普通文件"
else
    echo "文件为特殊文件"
fi
if [ -d $file ]
then
    echo "文件是个目录"
else
    echo "文件不是个目录"
fi
if [ -s $file ]
then
    echo "文件不为空"
else
    echo "文件为空"
fi
if [ -e $file ]
then
    echo "文件存在"
else
    echo "文件不存在"
fi


a=""
echo "a 的长度为${#a}"
if [ -n $a ]
then
    echo "-n $a :字符长度不为　０"
else
    echo "-n $a :字符长度为　０"
fi











