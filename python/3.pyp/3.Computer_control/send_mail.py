#!/usr/bin/env python
# coding=utf-8


import smtplib
from email.mime.text import MIMEText
from email.header import Header
from email.mime.multipart import MIMEMultipart


def get_userinfo():
    with open("userinfo.json", "r") as fin:
        import json
        return json.loads(fin.read())

def get_msg():
    with open("test", "r") as fin:
        return fin.read()

userinfo = get_userinfo()
mail = smtplib.SMTP("smtp.163.com")
mail.login(userinfo["username"],userinfo["password"])


#创建实例
content = MIMEMultipart()
content["from"] = Header(userinfo["username"],'utf-8')
content["to"] = Header(userinfo["username"],'utf-8')
content["subject"] = Header("test title",'utf-8')

#构造邮件
msg = get_msg()
content.attach(MIMEText(msg, "html",'utf-8'))

#构造附件
att1 = MIMEText(open('1.png', 'rb').read(), 'base64', 'utf-8')
att1["Content-Type"] = 'application/octet-stream'
# 这里的filename可以任意写，写什么名字，邮件中显示什么名字
att1["Content-Disposition"] = 'attachment; filename="1.png"'
content.attach(att1)

mail.sendmail(userinfo["username"],"15736818863@163.com",content.as_string())

mail.close()
