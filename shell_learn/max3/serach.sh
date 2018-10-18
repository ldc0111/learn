#*************************************************************************
#	> File Name: serach.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年10月14日 星期日 20时11分17秒
#*************************************************************************

#!/bin/bash


max1=(0 0 '' '')
max2=(0 0 '' '')
max3=(0 0 '' '')
fl=(0 0 '' '')
words=''
dirn=$1
path='.'

#寻找文件内最长的三个字符串
count_char(){
    #echo $1
    words=`cat $1 2>> /dev/null`
    for i in $words ; do
        i=`echo $i|grep ^[a-zA-Z]`
        temp=${#i}
        if [[ $i == ${max1[3]} ]]; then
            continue
        fi
        if [[ $i == ${max2[3]} ]]; then
            continue
        fi
        if [[ $i == ${max3[3]} ]]; then
            continue
        fi
        if [[ $temp -gt ${max1[0]} ]]; then
            fl[0]=$temp
            fl[1]=`grep -son $i $1|cut -d":" -f1|head -1 `
            fl[2]=$1
            fl[3]=$i
            max1=(${fl[*]})
            #echo ${max1[*]}

            if [[ ${max1[0]} -gt ${max2[0]} ]]; then
                fl=(${max2[*]})
                max2=(${max1[*]})
                max1=(${fl[*]})
                if [[ ${max2[0]} -gt ${max3[0]} ]]; then
                     fl=(${max3[*]})
                     max3=(${max2[*]})
                     max2=(${fl[*]})
                fi
            fi
        fi
    done
}


filter() {
    file $1|grep "executable" > /dev/null
    if [[ $? -eq 0 ]]; then
        #echo $1
        return 0
    fi
    temp=''
    a=(yml rmvb png img md gif avi zip tar gz 7z jpg)
    suffix=`echo $1|awk -F . '{print $NF}'`
    echo ${a[*]} |grep "$suffix" >> /dev/null 
    if [[ $? -eq 0 ]]; then
        return 0
    fi
    return 1;
}

#递归文件夹　搜索文件
dir() {
    if [[ -f $1 ]]; then
        filter $1
        if [[ $? -eq 1 ]]; then
            count_char $1
        fi
    elif [[ -d $1 ]]; then
        for arr in `ls -a $1` ; do
            if [[ $arr == '.' || $arr == '..' ]]; then 
                continue
            fi
            tempway=$1/$arr
            dir $tempway
        done
    fi
}
dir $path 





#count_char 
echo ${max1[*]}
echo ${max2[*]}
echo ${max3[*]}

