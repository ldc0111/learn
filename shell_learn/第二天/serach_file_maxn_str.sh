#!/bin/bash

maxsize=1048576
maxnlength=0
maxway=''
maxchar=''

tempway=''
tempchar=''
words=''

#计算文件字符串长度，并统计最长字符串
count_char(){
    #echo $1
    words=`cat $1`
    for i in $words ; do
        temp=${#i}
        #echo $temp
        if [[ $temp -gt $maxnlength ]]; then
            maxnlength=$temp
            maxway=$1
            maxchar=$i
        fi
    done
}



#是文件夹进去
files(){
for arr in `ls $1`
do  
    tempway=$1/$arr
    #echo $tempway
    if  [[ -d $tempway ]]
    then
        #echo $arr
        files $tempway
    elif [[ -f $tempway ]]
    then
        filesize=`ls -l $tempway | awk '{ print $5 }'`   #大于１m的跳过
        if [[ $filesize -lt $maxsize ]];then
        count_char $tempway 
        fi
    fi
done
}

 
#主函数
cd #返回家目录 
for arr in $@ #遍历参数列表
do 
    if test -d $arr #判断是不是文件夹
    then
    tempway=$arr
    files $arr 
    elif [[ -f $arr ]]
    then
        count_char $arr
    fi
done

echo "最长字符串的文件路径为 $maxway"
echo "最长字符串的文件长度为 $maxnlength"
echo "最长字符串为： $maxchar"
