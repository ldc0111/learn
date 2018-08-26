#*************************************************************************
#	> File Name: sh09.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年08月25日 星期六 21时05分53秒
#*************************************************************************

#!/bin/bash


echo "New,i well detect your linux server's servicer!"
echo  -e "The www,ftp ssh ans Maill will be detect! \n"


testing=$(netstat -tuln|grep ":80")
if [ "$testing" != "" ]; then
    echo "www is runing in your system!"
fi 

testing=$(netstat -tuln|grep ""22)
if [ "$testing" != "" ]; then
    echo "ssh is runing is your system!"
fi

testing=$(netstat -tuln|grep ":21")
if [ "$testing" != "" ]; then
    echo "FTP is runing in your system!"
fi 
##
#
testing=$(netstat -tuln|grep ":25")
if [ "$testing" != "" ]; then
    echo "Mail is runing in your system!"
fi 

