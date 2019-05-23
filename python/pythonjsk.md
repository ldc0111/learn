###　入门

* 解释型语言（一边理解一边执行）
* 变量，参数，函数声明时无需说明类型

````py
a = 3
a = 'dsf'
from __future__ import division
print

len(a)
str()
````







###　简单程序

python缩进代表了逻辑层次

```py
def name(list):
  
```

命名规范 下划线命名法

````py
a,b,c = (int(x) for x in raw_input().split(' '))
printf a + b + c
````



###　字符串使用

一个单引号字符中可以使用双引号

一个双引号字符中可以使用单引号

字符串可以分成多行来写，但是我们需要在末尾加上一个斜杠``

````shell
a.lower()转化为小写
a.upper()转化位大写

s.isalpha()判断是不是全字符
s.isdigit()判断是不是全数字
s.startswith('xx')判断开头字符
s.endswith('xx')判断结尾字符
````



索引字符

h 　　　   e             l                l           o

０　　　１　　　２　　　３　　　４

－５　　－４　　－３　　－２　　－１

####　判断语句

````py
if a > ０:
   c = a
elif a == 0:
   c = -1
else
   c = -a
````

####　其他



````py
or
and
````



````
s.find(' ')查找函数
s.replace(' ', ' ')替换
````



````
print name + ' is a ' + str(age) + '-year-old woman with height ' + str(height)
print '%s is a %d-year-old woman with height %g' % (name,age,height)
````



````
print raw_input().replace(' ','%20')
````



###　简单结构

####　列表

　用于存储１系列的数据

　字符串是特殊等待列表

　　可以简单的将一列长度为１的子字符串看成组成的特殊列表的

````py
arr.append(' ')
arr.extend(arr1)
arr.insert(0,'xxx')
arr.index('xx')

arr.remove(' ')
arr.pop(number)

````



`````
manager = 'tuotatianwang,taibaijinxing,juanliandajiang'
manager_list = manager.split(',')
print manager_list
new_manager = ' '.join(manager_list)
print new_manager
`````



````py
sum(arr)
for i in list:
   
````



````
rang(100)
rang(1, 10)
rang(1,10, 2)

````







###　排序与元组

````
arr.sort()
sorted(arr)#有返回值
sorted(numbers, reverse=True)
````

ver





###　字典与文件

键值对

键名：键值

`````py
bat = {'a': 'alibaba', 'b': 'baidu', 't': 'tencent'}

print bat.keys()#键名
print bat.values()#键值
print bat.items()＃所有对

for k,v in bat.items():
    print k,'>',v
    
    
    
boss = {} 
boss['name'] = 'robin' 
boss['age'] = 45
boss['height'] = 1.78
print 'The boss named %(name)s is %(age)d-year-old and %(height)g tall.' %　boss
`````



````
fd = open('filename', 'r')
fd.close
fd = open('filename', 'rw')


f = open('filename', 'rU')
for line in f :
    print line
打印每一行（读取一行）

fd.readline()
将每一行转化成一个字符串
fd.read()
将整个文件转化成一个字符串

fd.write(字符串)
print >> 文件操作符，字符串

inport codes
fd = condese.open('foo.txt','rU','utf-8')

````





###　正则表达式



````py
re.findall(r'([\w\.-]+)@([\w\.-]+)',str)
````

