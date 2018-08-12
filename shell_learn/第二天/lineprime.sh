#!/bin/bash

maxn=10
for ((i = 0; i <= maxn; i++)); do
    isprime[i]=0
done


for ((i = 2; i < maxn; i++)); do
    if [[ ${isprime[i]} -eq  0 ]]
    then
        prime[0]=$[ ${prime[0]} + 1 ]
        prime[prime[0]]=$i
    fi

    for ((j=1; j <= prime[0]; j++)); do
        if [[ `expr $i \* ${prime[j]}` -ge $maxn ]];then  break; fi
        #echo $i ${prime[j]}
        isprime[i * prime[j]]=1
        #echo
        if [[ `expr $i % ${prime[j]}` -eq 0 ]];then break; fi
    done 
done


echo 'd'
for (( i = 0; i < 10; i++ )); do 
     echo ${isprime[i]} ${prime[i]}
done 
