#!/usr/bin/env python
# coding=utf-8

import poplib
import email
import time
import os
import smtplib

def get_userinfo():
    import json
    with open("userinfo.json", "r") as fin:
        return json.loads(fin.read())

def sign_in_mail_pop3(userinfo):
    mail = poplib.POP3("pop.163.com")
    mail.user(userinfo["username"])
    mail.pass_(userinfo["password"])
    return mail
def sign_in_mail_smtp(userinfo):
    mail = smtplib.SMTP("smtp.163.com")
    mail.login(userinfo["username"],userinfo["password"])
    return mail


def init_mail(userinfo, com):
    #创建实例
    from email.header import Header
    from email.mime.multipart import MIMEMultipart
    content = MIMEMultipart()
    content["from"] = Header(userinfo["username"],'utf-8')
    content["to"] = Header(userinfo["username"],'utf-8')
    content["subject"] = Header(com,'utf-8')
    return content
def init_Enclosure():
    from email.mime.text import MIMEText
    att1 = MIMEText(open('1.png', 'rb').read(), 'base64', 'utf-8')
    att1["Content-Type"] = 'application/octet-stream'
    # 这里的filename可以任意写，写什么名字，邮件中显示什么名字
    att1["Content-Disposition"] = 'attachment; filename="1.png"'
    return att1

def Screenshots(title, userinfo):
    os.system("scrot ./1.png")
    mail1 = sign_in_mail_smtp(userinfo)
    #创建实例
    content = init_mail(userinfo,"Screenshots")

    #构造附件
    att1 = init_Enclosure() 
    content.attach(att1)
    mail1.sendmail(userinfo["username"],"15736818863@163.com",content.as_string())




def read_mail(mail, new_stats, userinfo):
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
    print (len(title[0]))
    if len(title[0]) == 2:
        title = title[0][0].decode("utf-8")
    print(title)
    if(title == '1'):
        Screenshots(title,userinfo)






def main():
    userinfo = get_userinfo()
    mail = sign_in_mail_pop3(userinfo)
    stats = mail.stat()
    while 1:
        mail = sign_in_mail_pop3(userinfo)
        new_stats = mail.stat()
        #邮件数对比
        if new_stats[0] != stats[0]:
            read_mail(mail, new_stats,userinfo)
        stats = new_stats
        mail.close()
        time.sleep(1)
    

if __name__ == '__main__':
    main()
