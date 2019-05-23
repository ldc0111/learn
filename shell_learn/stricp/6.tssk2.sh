#*************************************************************************
#	> File Name: tssk.sh
#	> Author: ldc
#	> Mail: 
#	> Created Time: 2018年08月26日 星期日 20时52分00秒
#*************************************************************************

#!/bin/bash
df -m|grep '^/dev'|awk 'BEGIN{total="" ; used=""; p="" } { total= total +$2 ; used = used + $3 ; printf "%s\t1\t%20s\t%s\t%s\t%s\n",dates,$6,$2,$3,$5} END{p=used *100 /total ; printf "%s\t0\t%20s\t%s\t%s\t%.0d%%\t\n",dates,"disk",total,used,p}' dates=`date +%Y-%m-%s__%H:%M:%S`
