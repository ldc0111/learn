#*************************************************************************
#	> File Name: sh06.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年08月25日 星期六 19时28分05秒
#*************************************************************************

#!/bin/bash

read -p "please input (Y/N):" yn
[ "$yn" == "Y" -o "$yn" == "y" ] && echo "ok, continue" && exit 0
[ "$yn" == "N" -o "$yn" == "n" ] && echo "oh,interrput!" && exit 0
echo "I don't konw what your choice is" && exit 0
