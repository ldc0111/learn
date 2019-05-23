#*************************************************************************
#	> File Name: sh08.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年08月25日 星期六 19时40分49秒
#*************************************************************************

#!/bin/bash

if [ "$1" == "hello" ]; then
    echo "hello,how are you ?"
elif [ "$1" == "" ]; then
    echo "you must input parameters,ex> {$0 someword}"
else
    echo "the onle parameters is 'hello',ex>($0 hello)"
fi
