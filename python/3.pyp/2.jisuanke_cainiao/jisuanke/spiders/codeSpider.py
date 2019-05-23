# -*- coding: utf-8 -*-
import scrapy
import os
from scrapy import Request
from selenium import webdriver
#一个类
class CodespiderSpider(scrapy.Spider):
    #类成员
    name = 'codeSpider'
    allowed_domains = ['jisuanke.com']
    start_url = 'https://www.jisuanke.com/course/%s?view=study'
    les_num = ["790","799","791","792","787","786","788","789"]
    #les_num = ["790"]
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
        for i in self.les_num:
            les_path = self.path + i + "/"
            os.mkdir(les_path)
            yield Request(url = self.start_url % i, callback = lambda response, cur_path = les_path: self.parse(response, cur_path))

    #方法１　类体＋爬取的文本
    def parse(self, response, cur_path):
        #获取每个模块的id
        m_list = response.xpath("//@data-chapter-id").extract()
        #遍历每个模块
        for m_item in m_list:
            #获取模块名字　并申请文件夹
            dir_m_name = "//li[@data-chapter-id='" + str(m_item) + "']/div[@class='chapter-section']/div[@class='chapter-title']/h2/text()"
            dir_name = cur_path + response.xpath(dir_m_name)[0].extract().encode("utf8")
            os.mkdir(dir_name)

            href_list = []
            a_list = response.xpath("//li[@data-chapter-id='" + str(m_item) + "']/ul[@class='jsk-list jsk-list-striped lessons']/li/a")
            file_name = []
            for a_item in a_list:
                title = a_item.xpath("./span[@class='lesson-icon-challenge']")
                if len(title) == 0:
                    continue
                href_list.append(a_item.xpath("./@href")[0].extract())
                file_name_temp = a_item.xpath("./span[@class='lesson-title jsk-text-truncate']/text()")[0].extract()
                file_name.append(dir_name + "/" + file_name_temp.encode("utf8") + ".cpp")
            ind = 0;
            for url in href_list:
                yield Request(url = "https:" + url, meta = {"file_name" : file_name[ind]}, callback = self.parse2) 
                ind += 1;
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
        file_name = response.meta["file_name"]
        print ("\n\n")
        print (file_name)
        print ("\n\n")
        #文本格式
        code = response.xpath("//pre/text()")[0].extract()
        with open(file_name, "w") as fout:
            fout.write(code.encode("utf8"))


