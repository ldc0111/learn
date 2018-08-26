#*************************************************************************
#	> File Name: sh04.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年08月25日 星期六 19时09分33秒
#*************************************************************************

#!/bin/bash

echo "You should input 2 nambers, i will cross them! \n"
read -p "first number:" first
read -p "second nambers:" secnu
total=$(( $first*$secnu ))
echo "\nthe result of $first * $secnu is ==> $total"
