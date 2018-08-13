#!/bin/bash

#find 对应目录 -mtime +天数 -name "文件名" -exec rm -rf {} \;
find /home/lidecao/trash -mtime +7 -name "*" -exec rm -f {} \;
