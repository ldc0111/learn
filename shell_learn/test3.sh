#!/bin/bash
echo "shell　传递参数实例！";
echo "执行的文件名：$0";
echo "第一个参数为：$1";
echo "第二个参数为: $2";
echo "第三个参数为：$3";

echo "shell 传递参数的实例"
echo "第一个参数为：$1";
echo "参数个数为：$#";
echo "传递的三叔作为一个字符串显示：$*"


echo "--\$* 演示---"
for i in "$*";do
    echo $i
done
echo "--\$@ 演示---"
for i in "$@"; do
    echo $i
done

