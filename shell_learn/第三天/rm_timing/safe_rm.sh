#!/bin/bash


dir=`date +"%y_%m_%d"`
#echo $dir
dir="/home/lidecao/trash/$dir"
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

