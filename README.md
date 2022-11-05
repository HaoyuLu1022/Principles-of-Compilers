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

## 实验2 语法分析

实验说明：[实验指导2 语法分析 · 语雀 (yuque.com)](https://www.yuque.com/huolihang/byyl22/lnu277#85d436d7)

### Quick Start

依赖包安装

```shell
sudo apt-get install bison
sudo apt-get install libbison-dev %% 如果gcc编译-ly报错，可以尝试这个
```

逻辑上的工作顺序应该是flex先按词法识别token，再由bison构建语法树

```sh
flex yf.l
bison -d syntax.y
gcc syntax.tab.c SyntaxTree.c -lfl -ly -o parser
```

需要注意的是

1.   flex对应的.l文件不需要加入头文件"SyntaxTree.h"，因为它并不负责、也不需要语法树的构建，加了还会导致头文件的重复引用
2.   bison对应的.y文件在定义部分需要引入头文件"SyntaxTree.h"，因为在规则部分，对于符合正确产生式的语句，我们需要构建语法树；在用户函数部分的main函数中，我们需要引入"lex.yy.c"文件，以将flex识别到的token同语法结合
3.   需要将yyerror()函数重载以使其失效（详见"syntax.y"代码），再构造myerror()函数以实现自定义报错输出

>   虽然没有仔细对比，但是实际运行时，调换flex和bison的执行顺序应该是等效的。推测是因为它们只是为对应代码创建静态链接，动态链接的加载还是交给gcc来做的
>
>   有时间可以再测试一下

测试样例

```sh
%% 基本要求
./parser test1.cmm
./parser test2.cmm
%% 附加要求
./parser test3.cmm
./parser test4.cmm
```

## 实验3 语义分析

实验说明：[实验指导3 语义分析 (yuque.com)](https://www.yuque.com/huolihang/byyl22/vq9hen#e44cad04)

### Quick Start

参考然然辛勤耕耘的RBTtest.c接口文档，添加下面列出的19种语义错误叭<(￣︶￣)↗[GO!]

#### 如何维护作用域

我将RBTtest.c文件的引用从syntax.y文件挪至yf.l文件中，为了更便捷地实现作用域的维护，以及其他各种类型的flag维护

简单来说，目前的解决方案是：

当**词法分析**识别到**左大括号LC**这个token时，RBT栈this_scope被push_back一个新的RBT；当**语法分析**完全匹配一个**含Compst (LC Mid RC)的产生式**时，RBT栈this_scope被pop_back掉一个RBT。

这样做的原因是：

-   syntax每个产生式后的代码仅会在产生式匹配完成后执行。如果push操作放在含Compst (LC Mid RC)的产生式匹配后执行的代码中，那么函数就只能被插入到新的局部作用域中，而不能被插入前一个范围更广的作用域
-   如果pop操作放在词法分析识别到右大括号RC这个token后，那么在向局部作用域插入函数声明的结点前，局部作用域就被删除了
-   为了能够既在函数自己的局部作用域中插入函数的结点，又在范围更广的前面的作用域中插入函数结点，故选择这种方案

### Task List

-   [x] 变量未定义
-   [x] 函数未定义
-   [x] 变量重定义
-   [x] 函数重定义
-   [ ] 赋值号两侧类型不匹配
-   [ ] 赋值号左侧出现右值表达式
-   [ ] 操作数类型不匹配
-   [ ] Return类型不匹配
-   [ ] 函数实参形参不匹配
-   [ ] 对非数组变量进行数组访问
-   [ ] 对普通变量调用函数
-   [ ] 数组访问符中出现非整数
-   [ ] 对非结构体变量使用"."
-   [ ] 访问结构体中未定义域
-   [ ] 结构体域名重复
-   [x] 结构体名字重复
-   [x] 使用未定义结构体定义变量
-   [ ] *函数声明但未定义
-   [ ] *函数声明冲突

注：*代表附加要求
