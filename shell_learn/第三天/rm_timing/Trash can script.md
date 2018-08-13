### 1,编写垃圾桶文件

借鉴网址https://blog.csdn.net/newbietao/article/details/79833655

创建一个垃圾桶目录设置垃圾桶权限

`chmod 755 trash`



````shell
#!/bin/bash


dir=`date +"%y_%m_%d"`
#echo $dir
dir="trash/$dir"
#echo $dir

if [[ ! -d $dir ]]; then
    mkdir $dir
fi

temprf=false
args=''

#deleting function
function remove(){
    for i in $args ; do
        #echo "$i 1"
        if [ -d $i -o -f $i ] ; then
            name=`basename $i`
           # echo "$name 2"
            if [ -d "$dir/$name" -o -f "$dir/$name" ]; then # already exist
                new_name="$dir/${name}_$(date +"%T")"
                mv $i $new_name && echo "$i deleted, you can see in $new_name"
            else
                mv $i $dir && echo "$i deleted, you can see in $dir"
            fi
        else
            echo "unknown error "
            echo "Please check if the file exists."
        fi
    done
}

#echo $1
#Read commands and parameters
while [[ $1 ]]; do
    case "$1" in
        -fr|-rf)
            temprf=true
            shift
            ;;
        -i)
            temprf=false
            shift
            ;;
        *)
            args="$1 $args"
            shift
            ;;
    esac
done
#echo $temprf

#判断命令 Judgment command
if [[ $temprf = true ]]; then
    remove
else
    read -p "Remove $args?[y/n] " temp
    if [[ $temp = y ]]; then
        echo "$args"
       remove
    elif [[ $temp = n ]];then
        exit
    else
        echo "Input error, please reinput."
        exit
    fi
fi


````



###2,设置变量别名

将脚本放到指定目录下

在bashrc文件下添加一行

`alias rms=/home/lidecao/scriptTask/rm_timing/safe_rm.sh`

设置完成之后更新bashrc文件

`source ~/.bashrc`或者`./.bashrc`

*注意：bashrc是一个隐藏文件*

###３编写定时文件

````shell
#!/bin/bash
#find 对应目录 -mtime +天数 -name "文件名" -exec rm -rf {} \;
find /home/lidecao/trash -mtime +7 -name "*" -exec rm -f {} \;

````



###４设置定时任务



在中断输入`crontab -e`

第一次使用会让你选择编译器　我选择的是vim

然后加入下面一行

````shell
#分　时　日　月　周　命令
0 10 * * 6 /home/lidecao/scriptTask/rm_timing/time_rm.sh

````



权限解释网址https://blog.csdn.net/slpond/article/details/53282167

date解释网址https://blog.csdn.net/hao_hl1314/article/details/61913288

crontab 解释网址https://www.cnblogs.com/intval/p/5763929.html