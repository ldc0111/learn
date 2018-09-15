#!/usr/bin/env python
# coding=utf-8
import re
users = re.findall(r'<li><span class="name">([\w]+)</span>([\w]+@[\w\.-]+)</li>','<ul><li><span class="name">Bob</span>bob@jisuanke.com</li><li><span class="name">ALice</span>alice@gmail.com</li><li><span class="name">Cane</span>cane.tec@bob.com</li></ul>')
for user in users:
    print user 
