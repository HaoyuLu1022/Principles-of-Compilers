#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef int NODE_TYPE;
#define NON_TERMINAL 0
#define INT_TYPE 1
#define FLOAT_TYPE 2
#define STRING_TYPE 3
#define STRUCT_TYPE 4
#define FUNCTION_TYPE 5
extern char *yytext;
extern int yylineno;

struct node {
    struct node *child;
    struct node *bro;
    int lines;
    char *name;
    NODE_TYPE type;
    char property[20];
    int isArr;
    int isStruct;
    union {
        char *id;
        int intValue;
        float floatValue;
    };
};

struct node *head;
struct node *iniNode(char *name, int lines, NODE_TYPE t);
struct node *insNode(struct node *n, char *name, int lines, NODE_TYPE t);
void printNode(struct node *n, FILE *f, int depth);
void printTree(struct node *head, int depth, FILE *f);
int searchTree(struct node *head, char* varName);

// 整体程序的翻译模式
void translate_Program(struct node *head, FILE *f);
void translate_ExtDefList(struct node *head, FILE *f);
void translate_ExtDef(struct node *head, FILE *f);
// 变量、函数声明的翻译模式
void translate_FunDec(struct node *head, FILE *f);
void translate_VarList(struct node *head, FILE *f);
void translate_ParamDec(struct node *head, FILE *f);
// 作用域的翻译模式
void translate_CompSt(struct node *head, FILE *f);
void translate_Mid(struct node *head, FILE *f);
// 语句列表的翻译模式
void translate_StmtList(struct node *head, FILE *f);
// 语句的翻译模式
void translate_Stmt(struct node *head, FILE *f);
// 变量声明、初始化的翻译模式
void translate_Specifier(struct node *head, FILE *f);
void translate_StructSpecifier(struct node *head, FILE *f);
void translate_TYPE(struct node *head, FILE *f);
void translate_ExtDecList(struct node *head, FILE *f);
void translate_DefList(struct node *head, FILE *f);
void translate_Def(struct node *head, FILE *f);
void translate_DecList(struct node *head, FILE *f);
void translate_VarDec(struct node *head, FILE *f);
void translate_Dec(struct node *head, FILE *f);
// 基本表达式的翻译模式
char* translate_Exp(struct node *head, FILE *f);
//void translate_Exp(struct node *head, FILE *f, Operand place);
// 条件表达式的翻译模式
//void translate_Cond(struct node *head, FILE *f, Operand lable_true, Operand lable_false);

// 函数参数的翻译模式
void translate_Args(struct node *head, FILE *f);

