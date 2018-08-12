#!/bin/bash

your_name="qinjx"
#echo $your_name
#echo ${your_name}
#for file in $(ls /etc)
#for file in 'ls /etc'
#for file in $(ls /etc)
#｛｝大括号演示
for skill in Ada Coffe Action Java; do
    echo "I am good at ${skill}Script"
done


#只读变量演示
myUrl="http:www.baidu.com"
readonly myUrl
#myUrl="http"

#删除演示
myUrlj="http:www.baidu.com"
unset myUrlj
echo $myUrlj

#单引号　双引号的使用
str='stis is a string'
your_name='runoob'
str="hello, I know you are\"$your_name\"! \n"
echo $str


#拼接字符串
#使用双引号拼接
greeting="hello, "$your_name" !"
greeting_1="hello, ${your_name} !"
echo $greeting $greeting_1
#使用单引号拼接
greeting_2='hello,'$your_name' !'
greeting_3='hello,${your_name} !'
echo $greeting_2 $greeting_3


#获取字符串长度
string1="abcd"
echo ${#string1}

#提取子串长度
string2="runoob is a great site"
echo ${string2:1:4}

#查找子字符串
string3="runoob is a great site"
echo `expr index "$string3" io`

#定义数组
#1
#array_name=(value0,value1,value2,value3,value4)
#2
array_name=(
 value0
 value1
 value2
 value3
 value4
)
#3
#array_name[0]=value0
#array_name[1]=value1
#array_name[2]=value2

#读取数组
valuen=${array_name[0]}
echo $valuen
#读取所有元素
echo ${array_name[@]};

#读取数组长度
#1
length=${#array_name[@]}
echo $length
#2
#length=${#array_name[*]}
#3
#length=${array_name[n]}



#-----------------------
#这是一个注释
#学习的不是技术还是梦想
############用户配置开始##############
#
############用户配置结束#############
#-------------------------
#多行注释
:<<EOF
注释内容
哈哈
聪明吧
EOF

:<<!
注释内容...
注释内容...
注释内容...
!



