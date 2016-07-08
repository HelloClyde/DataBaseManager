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

