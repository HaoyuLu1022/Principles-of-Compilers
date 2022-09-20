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
