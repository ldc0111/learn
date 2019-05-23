#*************************************************************************
#	> File Name: sh11.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年08月25日 星期六 21时28分25秒
#*************************************************************************

#!/bin/bash

function printit(){
    echo -n "your choice is "
}

#echo "this program will print your selection"
#echo $1
case $1 in
    "one")
         printit
         echo $1| tr "a-z" "A-Z"
         ;;
     "two")
         printit
         echo $1|tr "a-z" "A-Z"
         ;;
     "three")
         printit
         echo $1|tr "a-z" "A-Z"
         ;;
     *)
         echo "usage $0 {one|two|three}"
         ;;
 esac

