#!/bin/bash

echo "#writeing rizhi.txt">> /home/Tesla/.bashrc
cat>>/home/Tesla/.bashrc<<eof
echo \`who am i\` "login" >>rizhi.txt
ss=\`date +%s\`
eof

echo "#writeing rizhi.txt">>/home/Tesla/.bash_logout
cat>>/home/Tesla/.bash_logout<< eof
sss-\`date +%s\`
echo \`who am i\` \$[(\$sss-\$ss)/60] "logout" >> rizhi.txt
eof
