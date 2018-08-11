#!/bin/bash


A=1
my_array=($A a,b "c" d)
echo "第一个元素为：${my_array[0]}"
echo "第二个元素为：${my_array[1]}"
echo "数组的元素为：${my_array[*]}"
echo "数组的元素为：${my_array[@]}"
echo "数组的长度为: ${#my_array[*]}"
echo "数组的长度为: ${#my_array[@]}"

echo "第Ａ个元素为：${my_array[A]}"

echo "－－－－－－－for循环遍历输出－－－－－"
for i in ${my_array[@]}; do
    echo $i
done


echo "-----while 循环输出使用let i++ 自增：：-----："
j=0
while [ $j -lt ${#my_array[@]} ]
do
    echo ${my_array[$j]}
    let j++
done

echo "----::while 循环输出　使用a=\$[\$a+1] 自增，个人感觉这种写法比较明显----"
a=0
while [ $a -lt ${#my_array[@]} ]
do
    echo ${my_array[$a]}
    a=$[$a+1]
done


echo "----::while 循环输出　使用let "n++" 自增，个人感觉这种写法比较明显----"
n=0
while [ $n -lt ${#my_array[@]} ]
do
    echo ${my_array[$n]}
    let "n++"
done


echo "----::while 循环输出　使用let m+=1 自增，个人感觉这种写法比较明显----"
m=0
while [ $m -lt ${#my_array[@]} ]
do
    echo ${my_array[$m]}
    let m+=1
done
