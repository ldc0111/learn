```sql
select sname from StudentInof
where sId>5

--取出编号从３到８的学生
select *from StucentInfo
where sId between 3 and 8
--取考试成绩在６０到８０的成绩
select * from ScoreInfo
where scoreValue between 60 and 80

--取班级编号为１到３的学生信息
select * from StudentInfo
where cid between 1 and 3

select * from StudentInfo
>where cid >=1 and cid <= 3

--去班级编号为１或者３的学生信息
select * from StudentInfo
where cid in (1,3)

select * from StudentInfo
where cid = 1 or cid = 3

--取学生编号为３－８的在１班的学生
select * from StudentInfo
where sId between 3 and 8 and cid = 1

--学生编号在[3,8]，在１班，学生信息
select * from StudentInfo
where (sId between 3 and 8) and (cid = 1)


--对性别ｂｉｔ类型查询
select * from StudentInfo
where sGender=1
```

模糊查询:用于处理字符串的值，运算符：like % _ [] ^



%０到任意多个字符

_一个字符

[]范围内的字符

^用在[]之前表示不适用内部的字符

```sql
--模糊查询
--名字中包含三的学生信息
select * from StudentInfo
where sName like '%三%'
--姓张的学生
select * from StudentInfo
where sName Like '%张'
--姓名为２个字的姓黄的学生
select * from StuedntInfo
where sName like '黄_'
--查询使用电话为１３段的学生信息
select * from StudentInfo
where sPhone like '13%'

select * from StudentInfo
where sPhone like '1[5-9]%'
--15xxxxx -19xxxx

select * from StudentInfo
where sPhone like '1[^5-9]%'



--取使用ｑｑ邮箱的学生
select sEMail like '%@qq%'
--讲编号为５和６的设置为空
update studentInof set sPthone =null
where sId in(5,6)

--电话为nul的学生信息
select * from StudentInfo
where sPhone is not null

```

链接查询：当需要的结果从多张表中取时



````sql
--查询学生姓名级所在的班级名称
--关键问题：那些表。关系
--StudentInfo
--ClassInfo
--关系：StudentInof.cid => ClassInfo.cid
--内链接：两个表中完全匹配的数据
select si.sName,ci,CTitle
from StudentInfo as si
inner join ClassInfo as ci on si.cid = ci.cid

--左链接：两个表中完全匹配的数据　左表中特有的数据
select si.sName,ci,CTitle
from StudentInfo as si
left join ClassInfo as ci on si.cid = ci.cid

--右链接两：个表中完全匹配的数据　右表中特有的数据
select si.sName,ci,CTitle
from StudentInfo as si
right join ClassInfo as ci on si.cid = ci.cid
　
--完全链接：两个表中完全匹配的数据　左表中特有的数据　右表中特有的数据
select si.sName,ci,CTitle
from StudentInfo as si
full join ClassInfo as ci on si.cid = ci.cid


--学生姓名，科目名称，分数
--studentInfo,SubjictInfo,ScoreInfo
--sid=stuid,sid=subid
select * 
from ScoreInfo as score
inner join StudentInfo as stu on score,stuId=stu.sid
inner join SubjectInfo as sub on score.subId

select * 
from ScoreInfo as score
inner join StudentInfo as stu on score,stuId=stu.sid
inner join SubjectInfo as sub on score.subId
inner join ClassInfo as class on stu,cid=class.cId

````

聚合函数

sum, avg, count, max, min

```sql
--聚合函数

select * from studentInof where cid=1
select COUNT(*) as count1 from StudentInfo

select COUNT(*) as count1 from StudentInfo
where cid=1
--单元格为null不计数
select * from ScoreInfo

select MAX(scourevalue) from ScoreInfo

--求学生编号为１的最低分
select min(scorevalue) from ScoreInfo
where stuId=1

select * from ScoreInfo

--求语文科目的平均分
--subjictInfo,ScoreInfo avg
select AVG(scoreValue) from SubrectInfo
inner join ScoreInfo on subId=SubjectInfo.sid
where sTitle= '语文'


```

over函数

```sql
--将统计信息分布到行中
select ScoreInfo.*,avg(scorevalue) over()
from ScoreInfo
where subId=1
```

group by 

```sql
--统计男女生人数
select COUNT(*)
from StudentInfo
group by sGender

select sGender,COUNT(*)
from StudentInfo
group by sGender

--科目一的平均分
select AVG(scoreValue) from ScoreInfo
where subId = 1
--每个科目的平均分
select subId,AVG(scorevalue) from ScoreInfo
group by subId

--
select subId,AVG(scorevalue) from ScoreInfo
group by subId,stuId
--求每个班的男女生人数
--结果集　中，分组依据值相同的实例在一组，在结果列中中能出息分组的依据列和聚列
select sGender,cid,COUNT(*)
from Studentfo
group by sGender，cid

--统计学生编号大于２的各个班级各个性别的学生人数
select cid,sGender,COUNT(*)
from StudentInfo
where sid>2
group by cid,sGender
--统计学生编号大于２的编号为３的班级的各性别的学生人数
select cid,sGender,COUNT(*)
from StudentInfo
where sid>2 and cid = 3
group by sGender

--统计学生编号大于２的各个班级各个性别的学生人数大于３的信息
select cid,sGender,COUNT(*)
from StudentInfo
where sId>2
group by cid,sGender having COUNT(*)>3

```

联合查询

union, union all,except,in

合集，，，，，，交，，，差

结果集的列数要一致，

对应结果列的类型一致

```sql
select cid from ClassInfo
--union
--union
--except-差集合
intersect--交集合
select cid from ClassInfo
```

快速备份

向未有备份的：select 列名　into　备份表名　from 源表名

说明：备份表可以不存在，会新建表，表的结构完全一致，但是不包含约束，外键

如果想只包含结构不包含数据，可以价格ｔｏｐ０

向已有表备份:insert into 备份表名 select 列名　from 源表名

```sql
--向一个存在的表中插入数据
insert into test2(cTitle)
select cTitle from ClassInfo

```

函数

```sql
--函数
--类型转换
--cast 
select CAST(98.00000 as decimal(4,1))
select CONVERT(decimal(4,1),89.00000,)

--11
select 1 + '1'
--2
select cast(1 as CHAR(1)) + '1'
--字符串函数
ascii（求字符ascii值）
left,right,substring：字符串截取
len:返回字符串长度
lower,upper,大小写转换
ltrim,rtrim:去空格

--日期函数:getDate(获取当前时间)
dateAdd(日期加)
dateDiff(日期差)
datePart（去日期的某部分），year,month,day
注意：dateAdd,dateDiff,datePart的第一个参数使用双引号

select datepaet("dayofyear",GETDATE())
select * from StudentInfo

```

视图

```sql
--创建视图
create view Student_Class
as
select StudentInfo.*,ClassInfo.cTile from StudentInfo inner join ClassInfo on StudentInfo.cid=ClassInfo.cid
--视图中存储的是select语句，而不是结果集
select * from Student_Class
where IsDelete=0 and cTitle = '白虎'
--尽量不用用视图去进行操作

```



子查询

```sql
--子查询
select * from StudentInfo
select * from ScoreInfo
--查询参与了考试的学生信息
select * from StudentInfo  --后
where sId in (select distinct stuid from ScoreInfo)
--先
--in　的效率底下

--exists 效率要高一些　
select * from StudertInfo
where exists (select * from Scoreinfo  where Scoreinfo.stuId = StudertInfo.sid)

--分页　已知：页大小（一页显示多少条数据），页索引
--１，３,１，３
--２，３
select *,ROW_NUMBER() over(order by sid desc) from StudentInfo
where sGender=1


--查询学生姓名，科目名称，成绩
select * from StudenrInof stu
inner join SubjectInfo sub on sub.sId=score.subId
inner join StudentInfo stu on stu.sId=score.stuId
１
--姓名　语文，　　数学　　英语
--小笼包　１００　８９　９２．５
select *,sName 姓名,
... 语文,--如果当前的值是STiTle的值是语文，则输出ScoreValue
... 数学,--如果当前的值是STiTle的值是数学，则输出ScoreValue
... 英语,--如果当前的值是STiTle的值是英语，则输出ScoreValue
from Student_Score
２

--姓名　语文，　　数学　　英语
--小笼包　１００　８９　９２．５
select *,sName 姓名,
case STitle when '语文' then ScoreValue end 语文,
case STitle when '数学' then ScoreValue end 数学,
case STitle when '英语' then ScoreValue end 英语
from Student_Score

３
--姓名　语文，　　数学　　英语
--小笼包　１００　８９　９２．５
select *,sName 姓名,
max(case STitle when '语文' then ScoreValue end) 语文,
max(case STitle when '数学' then ScoreValue end) 数学,
max(case STitle when '英语' then ScoreValue end) 英语
from Student_Score
group by sName
--使用聚合函数，以防多个值处理失败
```



聚类索引：主键

非聚类索引：

有条件的去查，没条件做索引没有变化，而且是大数据量的

做索引的目的给where后面的做索引

一开始可以不用去做，后期在需要去做，

原来是聚类索引，就是一条一条对比

非聚类索引，就是重新就是重新建立一个表，指向数据，在原来数据，不是逐条去检索，是按新建的索引表去索引









