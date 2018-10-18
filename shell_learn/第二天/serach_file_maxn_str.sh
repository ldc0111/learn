#!/bin/bash

maxsize=1048576
maxnlength=0
max2length=0
max3length=0
maxway=''
max2way=''
max3way=''
maxchar=''
max2char=''
max3char=''
max1=(0 '' '')

max2=(0 '' '')

max3=(0 '' '')
tempway=''
tempchar=''
templength=0
words=''

#file a.out |grep "executable"

#计算文件字符串长度，并统计最长字符串
count_char(){
    words=`cat $1`
    for i in $words ; do
        temp=${#i}
        #echo $temp
        if [[ $temp -gt $maxnlength ]]; then
            maxnlength=$temp
            maxway=$1
            maxchar=$i
            if [[ $maxnlength -gt $max2length ]] ;then
                #templength=max
                max2length=$maxnlength;
                max2way=$maxway
                max2char=$maxchar
                if [[ $max2length -gt $max3length ]] ;then
                    max3length=$max2length
                    max3way=$max2way
                    max3char=$maxchar
                fi
            fi
        fi
    done
}

filter(){
    a=(rmvb png img)
    suffix=`echo $1|awk -F.'print $NF'`
    echo $(a[*])|grep "$"
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
            file $tempway|grep "executable" >/dev/null 
            if [[ $?  == 1 ]];then
            count_char $tempway 
            fi
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
echo "最长字符串的文件路径为 $max2way"
echo "最长字符串的文件路径为 $max2way"
echo "最长字符串的文件长度为 $max2length"
echo "最长字符串为： $max3char"
echo "最长字符串的文件长度为 $max3length"
echo "最长字符串为： $max3char"
