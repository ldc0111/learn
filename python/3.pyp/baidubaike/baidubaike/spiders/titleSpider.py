# -*- coding: utf-8 -*-
import scrapy
from scrapy import Request
from fake_useragent import UserAgent

class TitlespiderSpider(scrapy.Spider):
    name = 'titleSpider'
    allowed_domains = ['baidu.com']
    base_url = "https://baike.baidu.com"
    start_url = 'https://baike.baidu.com/item/%E6%96%90%E6%B3%A2%E9%82%A3%E5%A5%91%E6%95%B0%E5%88%97/99145?fr=aladdin'
    filename = "output"

    def __init__(self):
        self.agent = UserAgent()
        self.fout = open(self.filename, "w")

    def start_requests(self):
        yield Request(url = self.start_url, meta = {"level" : 1, "raw_title" : ""}, callback = self.parse)

    def parse(self, response):
        h1_list = response.xpath("//h1/text()")
        data = response.meta["raw_title"] + h1_list[0].extract()
        self.fout.write(data.encode("UTF8"))
        self.fout.write("\n")
        data += ' -> '
        if response.meta["level"] < 5:
            ahref_list = response.xpath("//div[@class='lemma-summary']/div[@class='para']/a/@href")
            for link in ahref_list:
                url = self.base_url + link.extract()
                yield Request(url = url, meta = {"level" : response.meta["level"] + 1, "raw_title" : data}, callback = self.parse)

