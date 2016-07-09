# DataBaseManager
Simple Database system for sql

#开发环境

Microsoft Windows 10专业版

Microsoft Visual Studio Professional 2015

#DBMS系统架构

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/001.png?raw=true)

```
	解释：
		DBMS:
			Analysis是词法分析函数
			IsNum用于判断是否为数字
			ShowStrArray用于显示字符串数组
			SelectFromWhere递归函数，用于解释执行Select-From-Where语句
			And用于Where返回的集合进行交运算
			Where递归函数，用于返回匹配Where的结果
			main主函数，程序入口
		DBClass:
			DBName数据库名字
			Tables数据库包含的表
			DBClass构造函数
			AddTable添加表到数据库
			DelTable删除表
			FindTable查找表
			Load从文件中载入数据库
			Save将数据库保存到文件
		TableClass:
			TableName表名
			TypeArray表中包含的属性
			PrimaryKey表中指定的关键字集合
			ClearPrimaryKey清楚表中的关键字
			CalTypeArrayLength计算属性所占用的一行的内存空间
			Insert往表中插入数据
			Save将表数据存入数据流中
			Where解释Where 值相等语句，返回搜索到的数据的内存地址集合
			Where解释Where In语句，返回搜索到的数据的内存地址集合
Select解释Select语句，将内存地址集合中符合显示要求的内容返回到一个字符串集合中
		TypeClass:
			Name属性名称
			TypeName属性类型
			TypeSize属性个数
			TypeLength属性所占内存长度
			TypeClass构造函数
			IsSame判断两个TypeClass是否相等
			operator ==重载==操作符，判断两个TypeClass是否相等
			Save将属性保存到数据流中
		FileOperate:
			GetString从文件数据流中获取字符串
			IsInStr判断字符串是否在字符串集合中
			IsInFlo判断单精度浮点数是否在集合中
			IsInInt判断整数是否在集合中
```

#DBMS主要功能模块

##SQL语言的词法分析

###功能介绍

将传入的SQL语言写成的纯文本数据流拆分成一个个单词组成的字符串集合

###相关理论

```
词法分析分类：
			标志符只由字母、数字和下划线组成
			字符串由单引号或者双引号括起来
			符号包括：逗号、回车、左右括号、等于号
```

###算法描述

通过对字符串的检索进行分类

###程序流程图

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/002.png?raw=true)

###测试用例与实验结果

测试用例：

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/003.png?raw=true)

实验结果：

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/004.png?raw=true)

##数据库存储设计

###功能介绍

数据库的保存与读取

###相关理论

这款数据库管理系统，把每个数据库数据保存到一个二进制文件中。

###数据结构设计

数据库二进制文件结构：

<table>
	<tr>
		<td>数据名称</td><td>数据类型</td><td>数据长度</td><td>辅助说明</td>
	</tr>
	<tr>
		<td>DBName</td><td>char</td><td>不定长，以0结束</td><td> </td>
	</tr>
	<tr>
		<td>Tables.size</td><td>int</td><td>4字节</td><td> </td>
	</tr>
	<tr>
		<td>Tables</td><td>TableClass</td><td>共Tables.size个</td><td>具体数据结构由Table二进制结构表说明</td>
	</tr>
</table>


Table二进制结构表

<table>
	<tr>
		<td>数据名称</td><td>数据类型</td><td>数据长度</td><td>辅助说明</td>
	</tr>
	<tr>
		<td>TableName</td><td>char</td><td>不定长，以0结束</td><td> </td>
	</tr>
	<tr>
		<td>TypeArray.size</td><td>Int</td><td>4字节</td><td> </td>
	</tr>
	<tr>
		<td>TypeArray</td><td>TypeClass</td><td>共TypeArray.size个</td><td>具体数据结构由Type二进制结构表说明</td>
	</tr>
	<tr>
		<td>TypeArrayLength</td><td>int</td><td>4字节</td><td> </td>
	</tr>
	<tr>
		<td>Data</td><td>链表</td><td>不定长，当链表指针为nullptr时为结束</td><td>该链表的节点长度由TypeArrayLength决定，其后4个字节为指向下一节点的指针</td>
	</tr>
</table>

Type二进制结构表

<table>
	<tr>
		<td>数据名称</td><td>数据类型</td><td>数据长度</td><td>辅助说明</td>
	</tr>
	<tr>
		<td>Name</td><td>char</td><td>不定长，以0结束</td><td> </td>
	</tr>
	<tr>
		<td>TypeName</td><td>char</td><td>不定长，以0结束</td><td> </td>
	</tr>
	<tr>
		<td>TypeSize</td><td>int</td><td>4字节</td><td> </td>
	</tr>
</table>

###ER图

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/005.png?raw=true)

###测试用例与实验结果

测试用例:

```
drop table employee
go
create table employee(name char(10) not null, ssn char(18) not null, bdate char(10) not null, address char(30) not null, sex char(2) not null, salary float not null, superssn char(18) not null, dno char(3) not null, primary key(ssn))
go

insert into employee values('张三','230101198009081234','1980-09-08', '哈尔滨道里区十二道街', '男', 3125, '23010119751201312X', 'd1')
insert into employee values('李四','230101198107023736','1981-07-02', '哈尔滨道外区三道街', '男', 2980, '23010119751201312X', 'd1')
insert into employee values('张红', '23010119751201312X','1975-12-01', '哈尔滨南岗区三十道街', '男', 4260, '23010119751201312X', 'd1')
insert into employee values('王二','230101198204078121','1982-04-07', '哈尔滨动力区六十道街', '男', 2890, '23010119751201312X', 'd1')
insert into employee values('灰太狼','23010119950101XXXX','1995-01-01', '青青草原狼堡', '男', 1200, '23010119960101XXXX', 'd2')
insert into employee values('红太狼','23010119960101XXXX','1996-01-01', '青青草原狼堡', '女', 3600, '23010119960101XXXX', 'd2')
insert into employee values('喜羊羊','23010120050101XXXX','2005-01-01', '青青草原大肥羊学校', '男', 1000, '23010120050101XXXX', 'd3')
insert into employee values('超人','XXXXXXXXXXXXXXXXXX','3000-01-01', '外星', '男', 1000000, '23010120050101XXXX', 'd4')
go
```

实验结果:

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/007.png?raw=true)

##查询功能

###功能介绍

对SQL语言中的Select-From-Where语句进行解释执行。

###相关理论

```
		Select是∏(想显示的属性)
		From是操作的表，如果是多张则进行笛卡尔积运算。（该DBMS只支持单张表，如果要进行多表查询，需要对SQL语句进行转换，转换成嵌套的方式）
		Where是σ(逻辑条件)

```

###算法描述

```
		Select操作与Where操作都被封装在TableClass类中。Select需要两个参数，一个是需要显示的属性名称，第二个是计算后的表内容行的地址集合。
		Where操作分为Where和WhereIn。Where用于判断单条件是否相等。WhereIn判断单条件属性是否在一个集合内。这两个Where函数都返回Select需要的集合。
		在main.cpp中还有两个函数，是SelectFromWhere和Where，SelectFromWhere用于解释执行Select-From-Where语句，遇到Where语句调用Where函数，遇到Select-From-Where语句的嵌套会递归调用自身。
		Where用于解释执行Select-From-Where中的Where语句，遇到多条件递归调用自身。

		所以，本数据库管理系统可以实现多表多条件的查询。
```

###程序流程图

主函数

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/008.png?raw=true)

SelectFromWhere函数

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/009.png?raw=true)

Where函数

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/010.png?raw=true)

###测试用例与实验结果

测试用例：

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/011.png?raw=true)

实验结果：

where pno=’p2’结果：

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/012.png?raw=true)

select essn from works_on where pno=’p2’结果：

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/013.png?raw=true)

where essn in (select essn from works_on where pno=’p2’)结果：

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/014.png?raw=true)

where pno=’p1’ and essn in (select essn from works_on where pno=’p2’)结果：

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/015.png?raw=true)

select essn from works_on where pno=’p1’ and essn in (select essn from works_on where pno=’p2’)结果：

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/016.png?raw=true)

##查询优化

###功能介绍

对查询、插入进行优化，加快计算速度。

###相关理论

链表可以存储不定长的数据。

申请一段动态的内存空间就可以使节点也成为变长。

###算法描述

通过记录上一次insert的位置，这样在插入数据的时候就不用遍历链表。

需要搜索数据的时候，先计算该数据在每一行的位置，然后只要计算每行头地址+位置就可以取得需要的内容。

###程序流程图

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/017.png?raw=true)

###测试用例与实验结果

测试用例：

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/018.png?raw=true)

实验结果：

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/019.png?raw=true)

##数据库使用说明

本数据库的功能就是执行SQL语句，从控制台读入需要执行的SQL代码文件路径，然后对SQL代码进行解释执行，数据库保存在应用程序同目录下的DefaultDataBase文件中。结果显示在控制台窗口上。如果SQL语句有误，数据库会直接退出。

举例运行一下：

1.打开CMD。

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/020.png?raw=true)

2.将目录切换到程序目录。

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/021.png?raw=true)

3.直接运行程序会出现提示信息，加上SQL代码文件路径后就能正确执行了。

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/022.png?raw=true)

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/023.png?raw=true)

4.结果直接在控制台显示。

![](https://github.com/FieldSoft-HelloClyde/DataBaseManager/blob/master/snap/024.png?raw=true)

#总结

我理论知识学的不好，导致这个管理系统架构有问题，索引什么的都没有加，执行的SQL语句也有限制，更加不用说大数据，并发操作，信号量什么的了。

下面我列一下该数据库管理系统的缺陷：

1.	不支持错误处理。
2.	不安全
3.	不支持多用户共同操作，多用户操作会产生错误的结果
4.	不支持真正的多表，现在的多表是对select语句的转换得到的
5.	其他程序调用该系统不能获取结果，除非截取控制台标准输出
6.	多条件会有问题，in语句只能放在最后
7.	条件判断只支持=，不支持>、<等

#参考文献

数据库系统原理/李建中，王珊编著.	—2版.	—北京：电子工业出版社,2004.9
