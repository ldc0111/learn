#!/bin/bash


demoFun(){
    echo "这是我的第一个shell 函数,谢谢大家的鼓励"
}

echo "----函数开始执行----"
demoFun
echo "----函数执行完毕----"

fumWithReturn(){
    echo "这个函数会对输入的两个数字进行相加运算。。"
    echo "输入第一个数字"
    read aNUM
    echo "数输入第二个数字"
    read anothenNUM
    echo "两个数字分别为 $aNUM 和 $anothenNUM !"
    return $(($aNUM+$anothenNUM))
}

fumWithReturn
echo "出入的两个数字之和为$? !"

fumWithReturn(){
    echo "第一个参数为　$1"
    echo "第二个参数为　$2"
    echo "第三个参数为　$3"
    echo "第四个参数为　$4"
    echo "第五个参数为　$5"
    echo "第六个参数为　$6"
}
fumWithReturn 1 2 3 4 5 6

#注意，$10 不能获取第十个参数，获取第十个参数需要${10}。当n>=10时，需要使用${n}来获取参数。

