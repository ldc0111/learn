#!/bin/bash


num1=100
num2=100
if test $[num1] -eq $[num2]
then
    echo "两个数相等"
else
    echo "两个数不相等"
fi
a=5
b=6
result=$[a+b]
echo "result 为：$result"
        

num1="ru1noob"
num2="runoob"
if test $num1 = $num2
then
    echo '两个字符串相等'
else
    echo '两个字符串不相等'
fi


cd /bin
if test -e ./bash
then
    echo '文件已近存在'
else
    echo '文件不存在'
fi

#cd /bin
if test -e ./notFile -o -e ./bash
then
    echo '至少有一个文件存在'
else
    echo '两个文件都不存在'
fi
