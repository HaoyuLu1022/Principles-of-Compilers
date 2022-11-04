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

基本同上

因为考虑采用红黑树RB Tree装各个作用域的符号表，然后维护一个符号表栈以区分作用域；然后我嫌手写很麻烦，想直接用C++的vector和map，所以这次也有gcc和g++编译的两个版本

但是 〒▽〒

但是 /(ㄒoㄒ)/~~

但是 (┬┬﹏┬┬)

一周了都没改好( ′ 3`) sigh~还不如手写RBT来得方便

所以大家参考然然辛勤耕耘的RBT文档，添加19种语义错误叭<(￣︶￣)↗[GO!]

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
