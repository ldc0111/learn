#!/bin/bash

#echo "菜鸟教程：www.runoom.com" >> users
#cat users | wc -l
wc -l < users


wc -l << EOF
          欢迎来到
          菜鸟教程
          www.runoom.com
EOF

