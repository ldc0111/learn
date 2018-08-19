#!/bin/bash

id="192.168.1."
i=1
while (( i < 255 )); do
    ping -c1 -w1 ${id}${i} 2>> /dev/null 1>>/dev/null
    if [[ $? == 0 ]]; then
        echo ${id}${i}
    fi
    (( i++ ))
done
