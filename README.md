# Principles-of-Compilers

北京师范大学2022秋季计算机科学与技术必修课“编译原理”实验汇总

同时也是第3小组的实验进度同步管理平台

## 实验1 词法分析

实验说明：[实验指导1 词法分析 · 语雀 (yuque.com)](https://www.yuque.com/huolihang/byyl22/vig4x3)

实验原理展示如下

<img src="https://pic002.cnblogs.com/images/2011/274814/2011101021413730.jpg">

概括地讲，就是编写一个合适的词法规则文件cf.l，交给Flex编译出lex.yy.c，再交给gcc编译得到可执行文件scanner，使用scanner对.cmm进行词法分析

### Quick Start

依赖包安装

```shell
sudo apt-get install flex
```

编译词法规则文件，形成可执行文件

```shell
cd 1-cffx
flex cf.l
gcc lex.yy.c -lfl -o scanner
```

词法分析测试

```shell
./scanner test.cmm
./scanner test2.cmm
```

#### 9.9 Update

基本实现了实验要求的各种类型的简单判断，尚未完成的工作包括：

1.   正则匹配的鲁棒性测试与改善
2.   指示出匹配到的语素在一行中的第几个字符(at line xxx, char xxx)
3.   报告撰写

#### 9.20 Update: 

1.   修正了RELOP、单行注释NOTE的匹配
2.   添加了简单的字符计数

尚存问题：

1.   字符计数不能在遇到换行符时重置为1
2.   INT类型匹配还需完善

##### 基本任务测试结果

输入：test.cmm

```shell
TYPE at line 1, char 1: int
ID at line 1, char 5: main
BRACKET at line 1, char 9: (
BRACKET at line 1, char 10: )
BRACKET at line 1, char 11: {
TYPE at line 2, char 5: float
ID at line 2, char 11: f
ASSIGNOP at line 2, char 13: =
FLOAT at line 2, char 15: 2.5
SEMT at line 2, char 18: ;
TYPE at line 3, char 5: int
ID at line 3, char 9: n_num
ASSIGNOP at line 3, char 15: =
INT data at line 3, char 17: 30
SEMT at line 3, char 19: ;
KEYWORD at line 4, char 5: if
BRACKET at line 4, char 7: (
ID at line 4, char 8: n
RELOP at line 4, char 10: >
FLOAT at line 4, char 12: 0.15
BRACKET at line 4, char 16: )
BRACKET at line 4, char 17: {
ID at line 5, char 9: printf
BRACKET at line 5, char 15: (
ERROR Type A at line 5, char 16: Myterious character: '"'
ERROR Type A at line 5, char 17: Myterious character: '"'
BRACKET at line 5, char 18: )
SEMT at line 5, char 19: ;
BRACKET at line 6, char 5: }
KEYWORD at line 6, char 6: else
BRACKET at line 6, char 10: {
ID at line 7, char 9: _f2
ASSIGNOP at line 7, char 13: =
ID at line 7, char 15: _f
START at line 7, char 18: *
FLOAT at line 7, char 20: 0.15
SEMT at line 7, char 24: ;
RELOP at line 8, char 9: <
RELOP at line 8, char 11: >
RELOP at line 8, char 13: ==
ERROR Type A at line 9, char 9: Myterious character: '#'
ERROR Type A at line 9, char 11: Myterious character: '%'
AND at line 9, char 13: &&
DIV at line 10, char 9: /
NOTE at line 10, char 13: //note
BRACKET at line 11, char 5: }
KEYWORD at line 12, char 5: return
INT data at line 12, char 12: 0
SEMT at line 12, char 13: ;
BRACKET at line 13, char 1: }
```

