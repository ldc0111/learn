#*************************************************************************
#	> File Name: sh05.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年08月25日 星期六 19时14分38秒
#*************************************************************************

#!/bin/bash

echo "please input a filename,i will check the filename's type and\
    permission.\n\n"

#判断是不是真的有字符串
read -p "input a filename:" filename
test -z $filename && echo "you must input a filename." && exit 0

#　判断文件是不是存在
test ! -e $filename && echo "the filename '$filename' Do Not exist" && exit 0
test -f $filename && filetype="regulare file"
test -d $filename && filetype="directory"
test -r $filename && perm="readable"

test -w $filename && perm="$perm writable"

test -x $filename && perm="$perm executable"

echo "the filename: $filename is a $filetype"

echo "and the permission are: $perm"

