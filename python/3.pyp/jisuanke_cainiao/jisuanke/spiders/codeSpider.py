#!/usr/bin/env python
# coding=utf-8
# -*- coding: utf-8 -*-
import scrapy
from scrapy import Request
from selenium import webdriver
#一个类
class CodespiderSpider(scrapy.Spider):
    #类成员
    name = 'codeSpider'
    allowed_domains = ['jisuanke.com']
    start_url = 'https://www.jisuanke.com/course/786?view=study'
    cookie_file = "./cookie_file"
    path = "./data/"
    
    #类的初始化函数　ｓｅｌｆ指的是类自己
    def __init__(self):
        driver = webdriver.Chrome()
        driver.set_page_load_timeout(10)
        driver.get("https://www.baidu.com")
        with open(self.cookie_file, "r") as fin:
            for line in fin:
                name, value, domain = line.strip().split("\t")
                cookie = {"name" : name, "value" : value, "domain" : domain}
                driver.add_cookie(cookie)
        self.driver = driver

    def start_requests(self):
        yield Request(url = self.start_url, callback = self.parse)

    #方法１　类体＋爬取的文本
    def parse(self, response):
        #// a 从匹配选择的当前节点选择文档中的节点，而不考虑它们的位置。
        a_list = response.xpath("//a")
        #会得到所有可以点击的链接存储在列表里面
        href_list = []
        #遍历列表
        for a_item in a_list:
            #.选取当前节点。/从根节点选取。选取包含span[]　@匹配class属性的节点，这个属性是已完成的标志
            title = a_item.xpath("./span[@class='lesson-icon-challenge']")
            #筛选失败的
            if len(title) == 0:
                continue
            #成功的将路径保存
            href_list.append(a_item.xpath("./@href")[0].extract())

        ind = 1
        #遍历每个路径，调用方法二，传入参数ind
        for url in href_list:
            yield Request(url = "https:" + url, meta = {"index" : ind}, callback = self.parse2)
            ind += 1
    #方法二
    def parse2(self, response):
        #筛选历史标题里每一个提交记录
        tr_list = response.xpath("//div[@class='jsk-modal-bd']/table/tbody/tr")
        for tr in tr_list:
            #筛选成功的标题
            tds = tr.xpath("./td[@class='jsk-text-success']")
            if len(tds) == 0:
                continue
            #执行点击里面每一个ｃ代码 参数是下标，调用下载函数
            yield Request(url = tr.xpath(".//a/@href")[0].extract(), meta = response.meta, callback = self.save_code)
            #跳出代码网页
            break

    #保存代码
    def save_code(self, response):
        #文件名
        file_name = self.path + str(response.meta["index"]) + ".cpp"
        #文本格式
        code = response.xpath("//pre/text()")[0].extract()
        with open(file_name, "w") as fout:
            fout.write(code.encode("utf8"))

