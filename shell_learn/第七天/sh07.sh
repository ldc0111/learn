#*************************************************************************
#	> File Name: sh07.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年08月25日 星期六 19时32分39秒
#*************************************************************************

#!/bin/bash

echo "the script name is        ==> $0"
echo "total parameter number is ==> $#"

[ $# -lt 2 ] && echo "the number of parameter is less than 2. stop here."\
    && exit 0
echo "your whole parameter is   ==>'$@'"

echo "the 1st parameter is      ==> $1"

echo "the 2nd parameter         ==> $2"
