#!/bin/bash

a=10
b=20
#if 的使用
if [ $a == $b ]
then
    echo "a 等于ｂ"
elif [ $a -gt $b ]
then
    echo "a 大于　ｂ"
elif
    echo "a 小于　ｂ"
then
    echo "a 小于　ｂ"
else
    echo "没有符合的条件"
fi

num1=$[2*3]
num2=$[1+5]
if test $[num1] -eq $[num2]
then
    echo '两个数字相等！'
else
    echo '两个数字不相等'
fi

#for循环

for loop in 1 2 3 4 5
do
    echo "The value is:$loop"
done

for str in 'This is a strring'
do
    echo $str
done

for((i=1; i <= 5; i++ )); do
    echo "这是第　$i  次调用"
done


#while 循环
int=1
while(( $int<=5 ))
do
    echo $int
    let "int++"
done

#echo '按下　<CTRL-D>退出'
#echo -n '输入你最喜欢的网站名'
#while read FILM
#do
 #   echo "是的！　$FILM 是一个好网站"
#done
#无限循环
#1
#while :
#do
#    xxxx
#done
#2
#while true
#do
#    xxxx
#done
#3
#for (( ; ;  ))

#until循环
a=0
until [ ! $a -lt 10 ]
do
    echo $a
    a=`expr $a + 1`
done


echo '输入１　到４之间的数字：'
echo '你输入的数字为：'
read aNUM
case $aNUM in
    1)  echo '你选择了１'
    ;;
    2)  echo '你选择了２'
    ;;
    3)  echo '你选择了３'
    ;;
    4)  echo '你选择了４'
    ;;
    5)  echo '你选择了５'
    ;;
    *)  echo '你没有输入１到５之间的数字'
    ;;
esac

#跳出循环
while :
do
    echo -n '输入１到５之间的数字'
    read aNUM
    case $aNUM in
         1|2|3|4|5) echo "你输入的数字为　$aNUM"
         ;;
         *) echo "你输入的数字不是１到５之间的！　游戏结束"
             break
         ;;
    esac
done


while :
do
    echo -n "输入１　到　５之间的数字"
    read aNUM
    case $aNUM in
        1|2|3|4|5) echo "你输入的数字为　$aNUM"
        ;;
        *) echo "你输入的数字不是　１ 到　５　之间的！"
             continue
             echo "Game over!"
        ;;
    esac
done

