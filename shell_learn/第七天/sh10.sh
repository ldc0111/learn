#*************************************************************************
#	> File Name: sh10.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年08月25日 星期六 21时19分48秒
#*************************************************************************

#!/bin/bash

while [[ $1 ]] ; do
##echo "`[[ $1 ]]`"
##echo "`(( $1 ))`"
case $1 in
    "shabi"|"sb")
        echo "脏话不对"
        shift
        ;;
    "nihao"|"sorry")
        echo "nihao"
        shift
        ;;
    "*")
        echo "nishaoyisi"
        shift
        ;;
esac
done 
