#!/bin/bash


device='/dev'
for i in `w -h`|awk '{print $w}';do
    device="$device/$i"
    echo `who am i` "$1">> $device
done
