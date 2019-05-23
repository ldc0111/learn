#*************************************************************************
#	> File Name: sh03.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年08月25日 星期六 12时05分50秒
#*************************************************************************

#!/bin/bash

echo "T will use 'touch'  command to create to create 3 files."
read -p "Please input your filename:" fileuser
filename=${fileuser:-"filename"}
#echo $filename
date1=$( date --date='2 days ago' +%Y%m%d )
date2=$( date --date='1 days ago' +%Y%m%d )
date3=$( date +%Y%m%d )
file1=${filename}${date1}
file2=${filename}${date2}
file3=${filename}${date3}

echo $file1  $file2 $file3
