#include <assert.h>
#include <stdio.h>
#include "SyntaxTree.h"


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