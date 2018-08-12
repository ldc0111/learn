#!/bin/bash 

echo 'hello haize'
for shi in 1 2 3 4 5 6
do
    echo "这是第 $shi 个数 "
 done
a=10
b=20
if test $[a] -eq $[b]
then
    echo '两个数相等'
else 
    echo '两个数不相等'
fi

echo "$0"
echo "$1$2"
echo "$*"
echo "$#"
echo "$@"

for i in "$*"; do
    echo $i
done

for i in "$@"; do
    echo $i
done


a=3
b=2
c="$a+$b"
echo $c
