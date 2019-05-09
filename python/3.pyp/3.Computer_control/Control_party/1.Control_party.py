#!/usr/bin/env python
# coding=utf-8

import smtplib
#from email.mime.text import MIMEText
from email.header import Header
from email.mime.multipart import MIMEMultipart

def tishi():
    print("Please enter parameter 1-N")
    print("1 = Screenshots")

def get_userinfo():
    with open("userinfo.json", "r") as fin:
        import json
        return json.loads(fin.read())

def sign_in_main(userinfo):
    mail = smtplib.SMTP("smtp.163.com")
    mail.login(userinfo["username"],userinfo["password"])
    return mail


def init_mail(userinfo, com):
    #创建实例
    content = MIMEMultipart()
    content["from"] = Header(userinfo["username"],'utf-8')
    content["to"] = Header(userinfo["username"],'utf-8')
    content["subject"] = Header(com,'utf-8')
    return content


def main():
    tishi()
    com = input("input:")
    userinfo = get_userinfo()
    mail = sign_in_main(userinfo)
    content = init_mail(userinfo,com)
    mail.sendmail(userinfo["username"],"15736818863@163.com",content.as_string())
    mail.close()





if __name__ == '__main__':
    main()
