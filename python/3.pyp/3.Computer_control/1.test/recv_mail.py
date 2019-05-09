#!/usr/bin/env python
# coding=utf-8


import poplib
import email

def get_userinfo():
    import json
    with open("userinfo.json", "r") as fin:
        return json.loads(fin.read())


mail = poplib.POP3("pop.163.com")
userinfo = get_userinfo()

mail.user(userinfo["username"])
mail.pass_(userinfo["password"])

stats = mail.stat()
#邮件数　和邮件占用的内存大小
#print(stats)
#元组
msg = mail.retr(stats[0])
#一个元组三个数据 其中第二个数据是一个列表
#print(msg)
str = "\n".join(map(lambda i: i.decode(),msg[1]))
#如果以"\n"结尾会是一个html格式的字符串
#print(str)
newmsg = email.message_from_string(str)
#解析成html格式
#print(newmsg)

#解析html
from email.header import decode_header
#获取subject
title = decode_header(newmsg["subject"])
if len(title[0]) == 2:
    title = title[0][0].decode(title[0][1])
else :
    title = title[0][0].decode()
print(title)

mail.close()
