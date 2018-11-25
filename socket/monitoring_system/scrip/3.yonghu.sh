#!/bin/bash
# dates j fei jin your dang
dates=`date +"%Y_%m_%d_%H:%M:%S"`
j=`cat /etc/passwd|grep  "bash"|cut -d ":" -f1|wc -w`
jin=`last|grep -v "^S\|wtmp"|cut -d " " -f1|sort|uniq -c|sort -nr|head -n3|tr -s " " " "|cut -d " " -f3|xargs|tr " " ","`
your=`cat /etc/group|grep "sudo"|tr "," ":"|tr ":" "\n"|tail -n +4|xargs|tr " " ","`
dang=`who|awk '{print  $1 $5 $2}'|tr "(\|)" "_"|xargs|tr " " ","`
echo "$dates $j [$jin] [$your] [$dang]"

