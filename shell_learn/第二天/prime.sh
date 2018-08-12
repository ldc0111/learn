#!/bin/bash


while read i
do
#for (( i = 2 ; i <= 10000; i++ )); do
    j=2
    for (( ; j*j <= i; j++ )); do
       # echo "$j"
        if [[ `expr $i % $j` == 0 ]]
        then
            break;
        fi
    done
    #echo $j $i
    if [[ $j*$j -gt $i  ]]
    then
        echo "$i 他是素数！！"
    else
        echo "他不是素数！！"
    fi
done


