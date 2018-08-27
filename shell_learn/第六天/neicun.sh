#!/bin/bash

free|awk 'BEGIN{remainder="" ; occupancy="" ; dynanic=""} NR == 2{remainder=$2 - $3 ; occupancy=remainder * 100/$2; dynanic = 0.3*la + 0.7*occupancy ; printf "%s\t%sM\t%sM\t%.1f%%\t%.1f%%\n",dates,$2,$3,occupancy,dynanic}' dates=`date +"%Y_%m_%d_%H:%M:%S"` la=$1
