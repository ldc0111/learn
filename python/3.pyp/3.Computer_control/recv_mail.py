#!/usr/bin/env python
# coding=utf-8


import poplib
import email
import time
def get_userinfo():
    import json
    with open("userinfo.json", "r") as fin:
        return json.loads(fin.read())


def read_mail(new_stats):
    msg = mail.retr(new_stats[0])
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
    print (title)
    #if len(title[0]) == 2:
    #    title = title[0][0].decode("utf-8")
    #else :
    #    title = title[0][0].decode()
    print(title[0][0])




mail = poplib.POP3("pop.163.com")
userinfo = get_userinfo()

mail.user(userinfo["username"])
mail.pass_(userinfo["password"])


stats = mail.stat()
i = 0

while 1:
    mail = poplib.POP3("pop.163.com")
    userinfo = get_userinfo()

    mail.user(userinfo["username"])
    mail.pass_(userinfo["password"])
    
    new_stats = mail.stat()
    #元祖　邮件数　和邮件占用的内存大小
    print(i, new_stats)
    #元组
    if new_stats[0] != stats[0]:
        read_mail(new_stats)
    i += 1
    stats = new_stats
    mail.close()
    time.sleep(1)

