****

**正在维护当中。。。。。。**

****



## 爬虫项目

### 项目需求

**统计某个在 OJ 上写了多少行代码**



### 前期准备

通常不使用浏览器进行爬虫

1. pyenv
   * python 各版本不兼容，需要 pyenv 管理 python 环境，在各版本中切换
   * pyenv install 3.7.1
   * [安装pyenv](https://www.cnblogs.com/olajennings/p/8832481.html)
2. pycharm
   * python 的 IDE
   * 推荐上官网下载 [安装pycharm](https://blog.csdn.net/qq_38683692/article/details/79868391)
   * pycharm 新建的项目放在`PycharmProjects`文件夹中
   * 打开 pycharm 中的 Terminal: `View -> ToolWindows -> Terminal`
3. anaconda
   * [官网下载](https://www.anaconda.com/distribution/)
   * [安装anaconda](https://www.jianshu.com/p/3e53407f8bd4)
   * [anaconda换源](https://blog.csdn.net/dream_allday/article/details/80344511)
   * 切换环境等常用命令
     * `conda activate 环境名`  进入某环境
     * `conda deactivate` 退出环境
     * `conda env list` 列举当前所有环境
     * `conda create -n your_env_name python=3.5` 创建指定python版本的环境
     * `conda remove -n your_env_name --all` 删除环境（不要乱）
     * `activate your_env_name` 进入（激活）指定名字的环境
     * `conda install lib_name` 安装指定库名
     * `conda uninstall lib_name` 卸载指定库名
4. scrapy
   * [安装scrapy](https://blog.csdn.net/a6864657/article/details/82634187)
5. xpath
   * [scrapy框架xpath和css选择器语法](https://blog.csdn.net/mouday/article/details/80455560)



### 开发环境

* scrapy
* python2.7.10



## 软件说明 

### Scrapy 的使用

说明：爬虫框架

1. 下载器（Download）
2. 分析器（Parse）
3. 存储器（Store, Save, Date, Item(一项、条目)）



#### 1.新建爬虫项目

```
scrapy startproject [爬虫项目的名字]
```



#### 2.新建爬虫

```
cd 
scrapy genspider [爬虫的名字] [爬虫的域名]
```

使用 fake-useragent 模块随机生成 User-Agent

[Scrapy 设置随机 User-Agent](https://www.cnblogs.com/yuqiangli0616/p/9277263.html)



```python
url = 开始的网址
callback = 分析的方法
```



#### 3.middlewares

```
from fake_useragent import UserAgent

class RandomUserAgentMiddleware(object):

    def __init__(self):
        self.agent = UserAgent()

    @classmethod
    def from_crawler(cls, crawler):
        return cls()

    def process_request(self, request, spider):
        request.headers.setdefault('User-Agent', self.agent.random)
```



#### 4.settings

**24 行左右**

```python
ROBOTSTXT_OBEY = False
```



#### 5.执行爬虫

```
scrapy crawl [爬虫名字](不加.py后缀)
```



#### 6.错误信息

>from fake_useragent import UserAgent
>ImportError: No module named fake_useragent

**解决方法**

```
sudo -H pip install fake-useragent
```



## 爬取计蒜客代码

* **爬虫代码中`./`以我们爬虫项目的路径为当前路径**
* 爬取的文件放到与该爬虫项目统计目录 data 中



### 1. 获取网页cookies数据（解决登录问题） 

<F12> -> `Application` -> `Cookies` -> **全选(鼠标拉动全选)** -> **复制** -> **粘贴到表格当中** -> **删除后三列** -> **在粘到爬虫项目目录下 cooke_file 文件中**



#### cookie表格

| 第一列     | 第二列   | 第三列 |
| ---------- | -------- | ------ |
| cookie名字 | cookie值 | domain |



#### 运行时报错

> Traceback (most recent call last):
>   File "test.py", line 11, in <module>
> ​    name, value, domain = line.strip().split("\t")
> ValueError: need more than 1 value to unpack

原来cookie_file是多了一个空行，把最后一行（空行）删除。



### 2. selenium

* 解释
  * selenium主要是用来做自动化测试，支持多种浏览器，爬虫中主要用来解决JavaScript渲染问题。
  * 模拟浏览器进行网页加载，当requests,urllib无法正常获取网页内容的时候
* `pip install selenium `  安装 
* [用法](https://www.cnblogs.com/themost/p/6900852.html)



### 3. chromedriver

**根据对应版本下载对应驱动**

* [版本对应网址](https://blog.csdn.net/huilan_same/article/details/51896672)

* [下载驱动官网](https://www.cnblogs.com/x54256/p/8403864.html)



#### 安装ChromeDriver

**1、安装xvfb以便我们可以无头奔跑地运行Chrome**

```bash
sudo apt-get install xvfb
```

**2、安装依赖**

```bash
sudo apt-get install unzip
```

**3、下载安装包（推荐通过官网下载符合自己版本的包）**

通过官网下载<https://chromedriver.storage.googleapis.com/index.html?path=73.0.3683.68/>

```bash
wget -N http://chromedriver.storage.googleapis.com/2.26/chromedriver_linux64.zip
```

**4、解压缩+添加执行权限**

```bash
unzip chromedriver_linux64.zip
```

**5、移动**

```bash
sudo mv -f chromedriver /usr/local/share/chromedriver
```

**6、建立软连接**

```bash
sudo ln -s /usr/local/share/chromedriver /usr/local/bin/chromedriver
sudo ln -s /usr/local/share/chromedriver /usr/bin/chromedriver
```



### 4.JavaScript

#### 单击事件

**1、middlewares.py**

```python
    def process_request(self, request, spider):
        # Called for each request that goes through the downloader
        # middleware.

        # Must either:
        # - return None: continue processing this request
        # - or return a Response object
        # - or return a Request object
        # - or raise IgnoreRequest: process_exception() methods of
        #   installed downloader middleware will be called
        from scrapy.http import HtmlResponse
        import time
        print hasattr(spider, "driver")
        if hasattr(spider, "driver") :
            print "my driver get html"
            spider.driver.get(request.url)
            js = '''
                if (document.getElementById('submit-history-trigger')) {
                    document.getElementById('submit-history-trigger').click();
                }
            '''
            spider.driver.execute_script(js)
            time.sleep(0.5)
            return HtmlResponse(
                spider.driver.current_url,
                body = spider.driver.page_source,
                encoding = "utf-8",
                request = request
            )
        return None
```

**2、settings.py**

```python
# 将下一行代码取消注释
DOWNLOADER_MIDDLEWARES = {
    'jisuanke.middlewares.JisuankeDownloaderMiddleware': 543,
}
```



### 5. 运行命令

```bash
python spider_run.py
```



#### spider_run.py

```python
#!/usr/bin/env python
# coding=utf-8

import os

# 运行爬取OJ上代码的爬虫
os.system("scrapy crawl codeSpider")

# 运行统计代码行数的脚本
os.system("bash code_line.sh")
```


