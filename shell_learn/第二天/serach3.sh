#!/bin/bash

maxsize=1048576
max1=(0 0 '' '')

max2=(0 0 '' '')

max3=(0 0 '' '')
fl=(0 0 '' '')

words=''

#file a.out |grep "executable"

#计算文件字符串长度，并统计最长字符串
count_char(){
    echo $1
    words=`cat $1`
    for i in $words ; do
        temp=${#i}
        #echo $temp
        if [[ $temp -gt ${max1[0]} ]]; then
            fl[0]=$temp
            fl[1]=`grep -n $i $1|cut -d":" -f1`
            fl[2]=$1
            fl[3]=$i
            max1=(${fl[*]})

            if [[ ${max1[0]} -gt ${max2[0]} ]]; then
                fl=(${max2[*]});
                max2=(${max1[*]});
                max1=(${fl[*]});
               if [[ ${max2[0]} -gt ${max3[0]} ]] ;then
                    fl=(${max3[*]});
                    max3=(${max2[*]});
                    max2=(${fl[*]});
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


echo ${max1[1]}
echo ${max1[*]}
echo ${max2[*]}
echo ${max3[*]}
