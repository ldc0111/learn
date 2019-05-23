#*************************************************************************
#	> File Name: 3.serach.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年10月15日 星期一 12时11分59秒
#*************************************************************************

#!/bin/bash
pi_cmd="
grep -EIHron '[a-zA-Z]+' './' 2> /dev/null |awk -F ':' -v hname=\$(hostname) 'BEGIN{
    len1=0;
    len2=0;
    len3=0;
    lentemp=0;
    str1=\$0;
    str2=\$0;
    str3=\$0;
    temp=\$0;
}
{
    if (length(\$3) > len1) {
        str1=\$0;
        len1=length(\$3);
    }
    if (len1 > len2) {
        temp=str2;
        str2=str1;
        str1=temp;
        lentemp=len2;
        len2=len1;
        len1=lentemp;
    }
    if (len2 > len3) {
        temp=str3;
        str3=str2;
        str2=temp;
        lentemp=len3;
        len3=len2;
        len2=lentemp;
    }
}
END{
printf(\"%d:%s:%s\\n%d:%s:%s\\n%d:%s:%s\\n\",len1,hname,str1,len2,hname,str2,len3,hname,str3);
}
'
"
for i in `seq 1 10` ; do 
    ssh  Tesla@pi${i} ${pi_cmd} >> ./piout/pidata
done

#cat -n ./piout/pidata|awk '{print $1 ":" $2 $3}'|sort -n -r -t ":" -k2|head -3 > ./piout/pi 
cat ./piout/pidata |sort -n -r -t ":" -k1|head -3
rm -f ./piout/pidata 
#cat ./piout/pi|cat -d":" -f1
#cat ./piout/pi |cut -d " " -f-6
