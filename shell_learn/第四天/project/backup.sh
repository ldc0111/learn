#!/bin/bash 

source /home/tesla/jiaoben/project/.backup.rc 
#source .backup.rc
#back_path=/home/tesla/184:/home/tesla/1844 
#last_path=/home/tesla/18444
#dayf=/home/tesla/18444/tayff.txt


days=`date +"%y_%m_%d_%H_%M"`
i=0
echo $back_path
if [[ ! -d $last_path ]]; then
    echo -e "\033[31m[error]$last_path is not a dir\033[0m">> $dayf
fi

for arr in `echo $back_path| tr ':' ' '`;do 
    echo -e "\033[32m $arr strated\033[0m"
    base=`basename $arr`
    new_name="$last_path/${base}_$days.tar.gz"
    #echo  $new_name
    if [[ -d $new_name ]];then
        new_name="$last_path_$days_$(date +"%T")_$base.tar.gz"
        tar czPf ${new_name} $arr
        echo -e "\033[32m the new_name is $new_name\033[0m"
    else
        tar czPf  ${new_name} $arr
        echo -e "\033[32m the new_name is $new_name\033[0m"
    fi
    size=`du -h $new_name|cut -f 1`
    echo -e "\033[36m $days 压缩  $new_name $size\033[0m" >> $dayf
done

#find /home/tesla/18444 -name "*.tar.gz" -cmin +3


del_list=`find $last_path -name "*.tar.gz" -cmin +2`

for i in $del_list; do
    echo -e "\033[33m $del_list is delete!!!\033[0m">> $dayf
    rm -f $del_list
done
