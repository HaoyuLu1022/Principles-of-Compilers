#include <stdio.h>
#include "ir.h"

extern int Regcnt; // 寄存器计数
extern char VarReg[10][10]; // 存放变量对应的寄存器号

void genAsm(struct node* head, FILE* fp);
// 整体程序的翻译模式
void genProgram(struct node* head, FILE* fp);
void genExtDefList(struct node* head, FILE* fp);
void genExtDef(struct node* head, FILE* fp);
// 变量、函数声明的翻译模式
void genFunDec(struct node *head, FILE *f);
void genVarList(struct node *head, FILE *f);
void genParamDec(struct node *head, FILE *f);
// 作用域的翻译模式
void genCompSt(struct node *head, FILE *f);
void genMid(struct node *head, FILE *f);
// 语句列表的翻译模式
void genStmtList(struct node *head, FILE *f);
// 语句的翻译模式
void genStmt(struct node *head, FILE *f);
// 变量声明、初始化的翻译模式
void genSpecifier(struct node *head, FILE *f);
void genStructSpecifier(struct node *head, FILE *f);
void genTYPE(struct node *head, FILE *f);
void genExtDecList(struct node *head, FILE *f);
void genDefList(struct node *head, FILE *f);
void genDef(struct node *head, FILE *f);
void genDecList(struct node *head, FILE *f);
void genVarDec(struct node *head, FILE *f);
void genDec(struct node *head, FILE *f);
// 基本表达式的翻译模式
char* genExp(struct node *head, FILE *f);
//void genExp(struct node *head, FILE *f, Operand place);
// 条件表达式的翻译模式
//void genCond(struct node *head, FILE *f, Operand lable_true, Operand lable_false);

// 函数参数的翻译模式
void genArgs(struct node *head, FILE *f);