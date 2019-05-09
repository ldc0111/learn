#!/usr/bin/env python
# coding=utf-8
from selenium import webdriver 
from time import sleep
driver = webdriver.Ie()
driver.get('http://www.baidu.com')
driver.find_element_by_id('kw').send_keys('Selenium')
driver.find_element_by_id('su').click()
sleep(2)
driver.get_screenshot_as_file("/home/tesla/github/learn/python/3.pyp/3.Computer_control/1.test/1.png") #截图存放路径，使用jpg报错png格式可以
sleep(3)
driver.quit()

