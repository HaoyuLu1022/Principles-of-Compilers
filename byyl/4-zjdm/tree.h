#ifndef TREE
#define TREE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>
#define MAXCHILD 10
extern int yylineno; /*[未定义的应用]行号*/
extern char *yytext; /*[未定义的应用]*/
extern int yylex(void);

typedef struct InterCode_ InterCode;
typedef struct Operand_ Operand;
typedef struct InterCodes_ InterCodes;
typedef struct ArgList_ ArgList;

#define IS(a,b) strcmp(a->name, b)==0

/*grammer Tree Ast*/
struct Ast{
    struct Ast *left;//左孩子
	struct Ast *right;//右兄弟
	struct Ast *parent;
    char name[256];//这里 相当于id
    char *text; //记录语法单元对应标记
    int line;   //行号
    int n; //子节点个数
	char ID[256];
	char ID1[256];
    union{  //语法单元
        int i;  //有整形，对应的int型数值
        float f;    //若浮点型，对应的float型数值
    };
	char* type;    //类型名称
	int flag;//表示结点的类型
	int scope;//作用域
	int valid;//当前变量是否有效
	int struct_num;
	InterCodes *comp_head;
    InterCodes *comp_tail;
};
// 结构体成员列表
 struct StructureField
 {
    char* Name;
    struct Variable* Type;
    struct StructureField* Next;
 };

 //结构体符号表
struct Structure
{
    int Define; // 是否被定义
    char* Name;
    struct StructureField * Type;
    struct Structure * Next;
}*structhead,*structtail;

//变量符号表
struct Variable
{
	char* name;//变量名
	char* type;//类型
	char belong[64];//记录该变量所丛属的结构体名，如果该变量不属于结构体，则记录为“”
	int flag;//0表示一般的变量，1表示数组变量
	int size;//数组大小
	int dimension; // 数组维度。如果不是数组变量，则维度标记为零
	struct Variable *next_dimension;//用来链接数组
	struct Variable *next;
  int len;//为变量分配的空间
	int scope;//作用域
	int valid;
	int struct_num;
	Operand *ir_var_no;
	char *shuzu;
  int field_size;//当前空间
  int offset;//总偏移
}*varihead, *varitail;

//函数符号表
struct Function
{
	int define;// 是否被定义
	char* funname; // 函数名
	char return_type[256]; //返回类型
	//char* return_type; 
	int valist_num;// 参数个数
	char* valist_type; // 参数类型
	int line;
	struct Function *next;
	char* valist_name;
}*funchead, *functail;


struct Operand_ {
    enum { OP_VARIABLE, OP_TEMP, OP_CONSTANT, OP_ADDRESS, OP_FUNCTION, OP_LABEL, OP_RELOP} op_kind;
    union {
      int var_no;
      int tmp_no;
      int const_value;
      char* func_name;
      int label_no;
      char* relop;
    };
    enum{ ISVALUE=199, ISADDRESS } addr_pos_kind; // Used when op_kind = OP_ADDRESS. 
    int is_param; // Used when op is param
};

struct InterCode_ {
    enum { 
      IR_LABEL, 
      IR_FUNCTION, 
      IR_ASSIGN, 
      IR_ADD, IR_SUB, IR_MUL, IR_DIV, 
      IR_GET_ADDR,
      IR_GET_ADDR_VAL,
      IR_TO_ADDR,
      IR_GOTO,
      IR_IF,
      IR_RETURN,
      IR_DEC,
      IR_ARG,
      IR_CALL_FUNC,
      IR_PARAM,
      IR_READ, IR_WRITE
    } ir_kind;
    union {
      struct {Operand *op1, *op2; } lr; 
      struct {Operand *op; } unop; // unary
      struct {Operand *result, *op1, *op2; } binop;
      struct {Operand *op1, *relop, *op2, *op3; } cond;//条件
    };
};

struct InterCodes_ {
    InterCode *code;
    InterCodes* prev;
    InterCodes* next;
};

struct ArgList_ {
    Operand *arg;
    ArgList* next;
};
// assert.h
#define NDEBUG

#ifdef NDEBUG
  #define Assert(cond) 1
#else
  #define Assert(cond) \
    do { \
      if (!(cond)) { \
        printk("Assertion fail at %s:%d\n", __FILE__, __LINE__); \
        exit(0); \
      } \
    } while (0)
#endif

#ifdef NDEBUG
  #define log(...) ;
#else
  #define log(...) printf(__VA_ARGS__)
#endif


void insert_ir(InterCode *ir);
void gen_ir_1(Operand *op, int ir_kind);
void gen_ir_2(Operand *op1, Operand *op2, int ir_kind);
void gen_ir_3(Operand *op1, Operand *op2, Operand *result, int ir_kind);
void gen_if_goto(Operand *op1, Operand *relop, Operand *op2, Operand *op3);
Operand *gen_im(int im);
Operand *get_var(char *var_name);
Operand *new_temp();
Operand *new_label();
void add_arg_list(Operand *new_arg, ArgList *arg_head);
void translate_Args(struct Ast *Args, ArgList *arg_head);
Operand *get_addr_value(Operand *place);
struct Variable *get_array_type(struct Ast *Exp);
void translate_Exp(struct Ast *Exp, Operand *place);
void translate_Cond(struct Ast *Exp, Operand *label_true, Operand *label_false);
void translate_VarList(struct Ast *VarList);
void translate_FuncDec(struct Ast *FuncDec);
void translate_Stmt(struct Ast *Stmt);
void translate_VarDec(struct Ast *VarDec, Operand *place);
void translate_Def(struct Ast *Def);
void translate_CompSt(struct Ast *CompSt);
void print_op(FILE *fp, Operand *op);
void print_binop(FILE *fp, InterCode *ir);
void print_ir(FILE *fp, InterCodes *start);

struct Ast* newLeaf(char *s,int yyline,int scope);
struct Ast* newNode(char *s,int yyline,int num,struct Ast* arr[]);
struct Ast* newNode0(char *s,int num); 
void printTree(struct Ast* r,int layer);
int get_len(struct Variable *var_type);
int find_dimension(struct Ast* s,struct Variable* local);
struct Variable* Insert_Var_Table(int num, struct Ast* arr[]);
struct Variable *find_var(struct Ast *s);
struct Variable *search(char *s);
struct Function *search_fun(char *s);
char *var_type(struct Ast *s);
char* find_valist(struct Ast* FunDec,int* valist_num);
char *find_val_args(struct Ast *FunDec);
char *find_valist_varname(struct Ast *FunDec);
char *find_args(struct Ast *Args);
struct Function* Insert_Func_Table(int num,struct Ast* arr[]);
struct Function *find_func(struct Ast *s);
struct Function *find_fundec(struct Ast *s1, struct Ast *s2);
struct Structure *Insert_Struct_Table(int num, struct Ast *arr[]);
struct Structure * find_struct(struct Ast *s);
int Find_Field_Var(struct Variable * s,struct Variable* n);
struct Ast * check_return_type(struct Ast *fundec, struct Ast* s);
void Show_Var_Table();
void Show_Func_Table();
void Show_Struct_Table();
struct Variable * find_var_def(struct Ast *s);
struct Function *findError18();
void find_ALLfunc(struct Ast *r);
void add_read_write_function();
void parsing(struct Ast *cur);
#endif