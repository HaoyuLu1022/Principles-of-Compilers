# 一个介绍RBTtest.c文件的Readme

<hr>

## 更新

- 修复了浅拷贝问题，在使用时注意无需分配内存和删除内存，建议使用`MyType tmp = MyType_default`更方便地初始化。
- 修复`print`函数，可以使用打印符号表啦~

在此例举使用新`MyType`的示例：
```c
// ...
| ID LP RP {
        $$ = insNode($1, "FunDec", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        MyType tmp = MyType_default;   // 在此创建局部变量
        // tmp.name = (char*)malloc(sizeof($1->id));   // 无需开内存
        strcpy(tmp.name, $1->id);  // 注意为了防止msg炸了，name、type和return_type都只开了20的大小
        if(search(this_scope, tmp)) {
            char msg[100];
            sprintf(msg, "Error %d at line %d : Redefined function \'%s\'", REDEFINED_FUNCTION, last_row, tmp.name);
            myerror(msg);
        }
        else {
            // printf("insert function \'%s\'\n", tmp.name);
            tmp.def = 1;
            tmp.isfunc = 1;
            this_scope = insert(this_scope, tmp);

            // free(tmp.type);  // 无需释放~
            tmp.def = 0;
            tmp.isfunc = 0;
        }
        // free(tmp.name);   // 无需释放~
    }
```

<hr>

这个文件主要使用Linux内核的rbtree.h和rbtree.c封装完成，下文为本文件的主要函数简介。

一开始的include和define不是咱写的不用管，先看我定义的结构体mytype

```c
typedef struct mytype {
    int def;  // 是否被定义
    char* name;   // 变量名，主键
    // int scope;   // 作用域，这个应该不需要了，用模拟栈的方法搞了
    int isvariable;  // 是否为VARIABLE
    char* type;  // 类型
    int isstruct;  // 是否为STRUCT
    int isfunc;  // 是否为FUNCTION
    int isarr;  // 是否为ARRAY
    int dimension;   // 数组维度
    char* return_type;  // func返回类型
    struct rb_root struct_varilist;
    // struct rb_root* funcvarlist;  // func参数列表，只能放结构体和变量
}MyType, *Mylink;
```

我注释写的太好了，无需多言，但是这些信息是独立的没有放到红黑树上，所以设置一个节点结构体如下：

```c
struct my_node {
    struct rb_node rb_node;    // 红黑树节点
    Type key;                // 键值
    // 自定义的数据
    MyType info;
};
```

最后为了方便直接的对当前作用域操作，对之前所有父级作用域访问，设置一个链表模拟栈存红黑树根节点，当然查询时有必要遍历栈中每一棵红黑树，定义如下。

```c
typedef struct table_stack {
    struct rb_root my_root;  // 当前作用域
    int top;   // 作用域编号，原本是头指针，现在debug用
    struct table_stack *last;  // link上一个作用域
}VariTables, *VariLink;
```

在此描述这样设计的目的，虽然假设使作用域的问题大大简化，但是我们仍然设计一个栈来表示、记录作用域。这是很直观的，我们根据以下规则设计：

1. 在一个作用域开始处压栈新建一棵红黑树记录其中变量，在该作用域结尾处出栈，抛弃整个作用域。所以很显然，该栈在语义分析开始和结束时为空；
2. 这个栈是特殊的栈，它只允许修改（插入节点）当前作用域，这与普通栈的性质相同；它可以顺序访问栈中保存的所有数据，这是因为当前作用域的变量可能来自祖先作用域的声明。

```c
int i;
int func(int a){
	int b;
    i = 0;
}
int main(){
	int j = i;
}
```

例如，上述程序的作用域栈转移应该如下：

```
栈顶      {a, b}     {j}
栈底 {i} -> {i}   -> {i}
id   (1)    (2)      (3)
```



MyType的输出，一目了然了。

```c
void print_mynode(MyType info){   // 这个本来没必要写的，但是怕铸币看不明白
    /*
    int def;  // 是否被定义.
    char* name;   // 变量名，主键.
    int scope;   // 作用域
    int isvariable;  // 是否为VARIABLE.
    int type;  // 类型.
    int isstruct;  // 是否为STRUCT.
    int isfunc;  // 是否为FUNCTION.
    int isarr;  // 是否为ARRAY，lhy真够吧，天下策划一个傻逼样
    int dimension;   // 数组维度
    char* return_type;  // func返回类型
    struct rb_root* funcvarlist;  // func参数列表，只能放结构体和变量
    */
    printf("def : %d\n", info.def);
    printf("name : %s\n", info.name);
    if(info.isvariable || info.isarr)
        printf("type : %s\n", info.type);
    if(info.isarr)
        printf("dimension : %d\n", info.dimension);
    if(info.isfunc)
        printf("return_type : %s", info.return_type);
    if(info.isstruct){
        printf("struct : struct maybe...\n");
        my_print(&info.struct_varilist);
    }
}
```

根据假设，name是用于转换成哈希值的“主键”，整个文件的核心就是完成一个映射功能map<name, MyType>，为了让name更便于比较，我用字符串的RSHash值来作为查找的key，实现如下。

```c
unsigned int RSHash(char* str, unsigned int len)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;
   unsigned int i    = 0;
 
   for(i = 0; i < len; str++, i++)
   {
      hash = hash * a + (*str);
      a    = a * b;
   }
 
   return hash;
}

unsigned int GetVariKey(MyType a){
    char s[500];
    strcpy(s, a.name);
    return RSHash(s, strlen(s));
}
```

## "my_"系列函数

### my_search

获得哈希值后只要把红黑树的**查找**、插入函数“编译原理化”即可，在此只记录使用方法：将要查询的节点信息用一个MyType保存以后即可搜索，返回同名（name）的my_node，还需要对比所有信息是否一致，例如type，可用my_node->info.type这样方法来访问，由于struct的特殊性必须使用这个函数，其余位置可使用后文中封装的更高级的search函数。

```c
struct my_node *my_search(struct rb_root *root, MyType info)
{
    
    struct rb_node *rbnode = root->rb_node;
    Type key = GetVariKey(info);

    while (rbnode!=NULL)
    {
        struct my_node *mynode = container_of(rbnode, struct my_node, rb_node);

        if (key < mynode->key)
            rbnode = rbnode->rb_left;
        else if (key > mynode->key)
            rbnode = rbnode->rb_right;
        else
            return mynode;
    }

    return NULL;
}
```

### my_insert

下文的**插入**函数与上述查询类似，**只有struct声明变量时使用**。

我在测试的时候用MyType tmp来记录我要插入的节点信息，这样的操作需要每次注意清空。

```c
int my_insert(struct rb_root *root, MyType info)
{
    struct my_node *mynode; // 新建结点
    struct rb_node **tmp = &(root->rb_node), *parent = NULL;
    Type key = GetVariKey(info);

    /* Figure out where to put new node */
    while (*tmp)
    {
        struct my_node *my = container_of(*tmp, struct my_node, rb_node);

        parent = *tmp;
        if (key < my->key)
            tmp = &((*tmp)->rb_left);
        else if (key > my->key)
            tmp = &((*tmp)->rb_right);
        else
            return -1;
    }

    // 如果新建结点失败，则返回。
    if ((mynode=malloc(sizeof(struct my_node))) == NULL)
        return -1;
    mynode->key = key;
    mynode->info = info;
    /* Add new node and rebalance tree. */
    rb_link_node(&mynode->rb_node, parent, tmp);
    rb_insert_color(&mynode->rb_node, root);

    return 0;
}
```

### 其他函数

**删除**操作my_delete改完发现不太方便用，因为红黑树的动态特性，不熟悉的我甚至写不出clear函数😥。

**打印**操作print_rbtree和my_print也完成了进一步的封装，用后文的print即可。

## Mylink search(VariLink vt, MyType x)函数

search函数是我封装好的对作用域栈的搜索函数，用一个作用域栈指针和一个具体的节点信息作为输入，返回NULL或者找到的节点信息，注意在此返回值和输入的节点同为MyType（Mylink是MyType的指针），还是比较好用的。

## VariLink init(VariLink vl)函数

栈的构造函数，包含在main中。注意调用时应该类似：`VariLink = init(VariLink)`

## VariLink push_scope(VariLink vl)函数

压栈，新加入一个红黑树根节点指针。调用时应该类似：`VariLink = push_scope(VariLink)`

## VariLink pop_scope(VariLink vl)函数

出栈，拿去栈顶红黑树根节点指针。调用时应该类似：`VariLink = pop_scope(VariLink)`

## VariLink insert(VariLink vl, MyType x)函数

插入，跟search类似，调用时应该类似：`VariLink = insert(VariLink)`

## void print(VariLink vl)函数

打印**当前**保存的符号表，没测过不过没啥问题应该。

