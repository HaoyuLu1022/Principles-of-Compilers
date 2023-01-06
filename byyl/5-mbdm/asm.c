#include "asm.h"
int rr = 1; // 指示label编号

void genAsm(struct node* head, FILE* fp) {
    fprintf(fp, ".data\n");
    fprintf(fp, "_prompt: .asciiz \"Enter an integer:\"\n");
    fprintf(fp, "_ret: .asciiz \"\\n\"\n");
    fprintf(fp, ".globl main\n");
    fprintf(fp, ".text\n");
    fprintf(fp, "read:\n");
    fprintf(fp, "\tli $v0, 4\n");
    fprintf(fp, "\tla $a0, _prompt\n");
    fprintf(fp, "\tsyscall\n");
    fprintf(fp, "\tli $v0, 5\n");
    fprintf(fp, "\tsyscall\n");
    fprintf(fp, "\tjr $ra\n\n");
    fprintf(fp, "write:\n");
    fprintf(fp, "\tli $v0, 1\n");
    fprintf(fp, "\tsyscall\n");
    fprintf(fp, "\tli $v0, 4\n");
    fprintf(fp, "\tla $a0, _ret\n");
    fprintf(fp, "\tsyscall\n");
    fprintf(fp, "\tmove $v0, $0\n");
    fprintf(fp, "\tjr $ra\n\n");

    genExtDefList(head->child, fp);
}

void genExtDefList(struct node* head, FILE* fp) {
    if(!head->child) return;
    genExtDef(head->child, fp);
    genExtDefList(head->child->bro, fp);
}

void genExtDef(struct node* head, FILE* fp) {
    genSpecifier(head->child, fp);
    if(head->child->bro->bro) {
        if(!strcmp(head->child->bro->name, "ExtDecList")) {
            genExtDecList(head->child->bro, fp);
        }
        else if(!strcmp(head->child->bro->name, "FunDec")) {
			genFunDec(head->child->bro, fp);				
			genCompSt(head->child->bro->bro, fp);		
			fprintf(fp, "\n");
		}
    }
}

void genFunDec(struct node *head, FILE *f) { 
    // 非main函数等到main函数调用再生成
    fprintf(f, "%s:\n", head->child->id);
    if(head->child->bro) {
        genVarList(head->child->bro->bro, f);
    }
}

void genVarList(struct node *head, FILE *f) {
    // 好像不用生成，跟栈有关
}

void genParamDec(struct node *head, FILE *f);
// 作用域的翻译模式
void genCompSt(struct node *head, FILE *f) {
    genMid(head->child->bro, f);
}

void genMid(struct node *head, FILE *f) {
    // printf("%s\n", head->child->name);
    
    if(!head->child)
        return;
    else if(!strcmp(head->child->name, "Def")) {
        genDef(head->child, f);
        genMid(head->child->bro, f);
    }
    else if(!strcmp(head->child->name, "Stmt")) {
        // printf("%s\n", head->child->child->name);
        genStmt(head->child, f);
        genMid(head->child->bro, f);
    }
}

// 语句列表的翻译模式
void genStmtList(struct node *head, FILE *f);
// 语句的翻译模式
void genStmt(struct node *head, FILE *f) {
    // printf("%s\n", head->child->name);
    int back1, back2, back3;
    if(!strcmp(head->child->name, "Exp")) {
        genExp(head->child, f);
    }
    if(!strcmp(head->child->name, "CompSt")) {
        genCompSt(head->child, f);
    }
    if(!strcmp(head->child->name, "RETURN")) {
        if(head->child->bro->child->type == INT_TYPE) {
            fprintf(f, "move $v0, $%d\n", head->child->bro->child->intValue);
            fprintf(f, "jr $ra\n");
        }
        if(head->child->bro->child->type == FLOAT_TYPE) {
            fprintf(f, "move $v0, $%f\n", head->child->bro->child->floatValue);
            fprintf(f, "jr $ra\n");
        }
    }
    if(!strcmp(head->child->name, "WHILE")) {
        // WHILE LP Exp RP Stmt
        fprintf(f, "%s:\n", head->id);
        if(head->child->bro->bro->child->bro) {
            if(!strcmp(head->child->bro->bro->child->bro->id, "<")) {
                int mark1 = 0, mark2 = 0;
                for(int i = 0; i < Regcnt; i++) {
                    if(!strcmp(VarReg[i], head->child->bro->bro->child->child->id)) {
                        mark1 = i;
                        break;
                    }
                }
                for(int i = 0; i < Regcnt; i++) {
                    if(!strcmp(VarReg[i], head->child->bro->bro->child->bro->bro->child->id)) {
                        mark2 = i;
                        break;
                    }
                }
                fprintf(f, "blt $t%d, $t%d, %s\n", mark1, mark2, head->child->bro->bro->bro->bro->id);
                fprintf(f, "j %s\n", head->child->bro->bro->id);
                fprintf(f, "%s:\n", head->child->bro->bro->bro->bro->id);
                // printf("%s\n", head->child->bro->bro->bro->bro->child->child->bro->child->name);
                genStmt(head->child->bro->bro->bro->bro, f);
                fprintf(f, "j %s\n", head->id);
                fprintf(f, "%s:\n", head->child->bro->bro->id);
                if(head->bro) {
                    // printf("%s\n", head->bro->child->name);
                    if(!strcmp(head->bro->name, "Mid")) {
                        genMid(head->child, f);
                    }
                }
            }

        }
    }
}

// 变量声明、初始化的翻译模式
void genSpecifier(struct node *head, FILE *f) {
    if(!strcmp(head->child->name, "TYPE")) 
		genTYPE(head->child, f);		
	if(!strcmp(head->child->name, "StructSpecifier"))
		genStructSpecifier(head->child, f); // 留着
}


void genStructSpecifier(struct node *head, FILE *f) {
    // 留着
}

void genTYPE(struct node *head, FILE *f) {
    // 用不到
}

void genExtDecList(struct node *head, FILE *f) {
    genVarDec(head->child, f);
    if(head->child->bro) {
        genExtDecList(head->child->bro->bro, f);
    }
}
void genDefList(struct node *head, FILE *f);
void genDef(struct node *head, FILE *f) {
    if(!strcmp(head->child->child->name, "StructSpecifier")) {
        // 结构体，留着
    }
    else {
        struct node* newnode = head->child->bro; // newnode始终指向DecList
        do{
            genDecList(newnode, f);
            if(newnode->child->bro)
                newnode = newnode->child->bro->bro;
            else break;
        } while(newnode->child->bro);
        // 数组，留着
    }
}

void genDecList(struct node *head, FILE *f) {
    genDec(head->child, f);
}

void genVarDec(struct node *head, FILE *f) {
    int mark = 0;
    for(int i = 0; i < Regcnt; i++) {
        if(!strcmp(VarReg[i], head->child->id)) {
            mark = i;
            break;
        }
    }
    fprintf(f, "li $t%d, ", mark);
    // fprintf(f, "li $t%d, ", --Regcnt); // 维护Regcnt
    // 如何建立寄存器名与变量名的对应关系
}

void genDec(struct node *head, FILE *f) {
    if(head->child->bro) {
        if(!strcmp(head->child->bro->bro->child->name, "INT") || !strcmp(head->child->bro->bro->child->name, "FLOAT")) {
            genVarDec(head->child, f);
            // genExp(head->child->bro->bro, f); // 可能涉及打印先后次序问题，暂不调用
            if(!strcmp(head->child->bro->bro->child->name, "INT")) {
                fprintf(f, "%d\n", head->child->bro->bro->child->intValue);
            }
            if(!strcmp(head->child->bro->bro->child->name, "FLOAT")) {
                fprintf(f, "%f\n", head->child->bro->bro->child->floatValue);
            }
        }
        else if(!strcmp(head->child->bro->bro->child->bro->name, "PLUS")) {
            struct node* newnode = head->child->bro->bro->child; // newnode指向PLUS前面的Exp
            int mark1 = 0, mark2 = 0, mark3 = 0;
            for(int i = 0; i < Regcnt; i++) {
                if(!strcmp(VarReg[i], head->child->child->id)) {
                    mark1 = i;
                    break;
                }
            }
            for(int i = 0; i < Regcnt; i++) {
                if(!strcmp(VarReg[i], newnode->child->id)) {
                    mark2 = i;
                    break;
                }
            }
            for(int i = 0; i < Regcnt; i++) {
                if(!strcmp(VarReg[i], newnode->bro->bro->child->id)) {
                    mark3 = i;
                    break;
                }
            }
            fprintf(f, "add $t%d, $t%d, $t%d\n", mark1, mark2, mark3);
        }
    }
    
}

// 基本表达式的翻译模式
char* genExp(struct node *head, FILE *f) {
    // if(!strcmp(head->child->name, "Exp")) {
    //     genExp(head->child, f);
    // }
    if(head->child->bro) {
        if(!strcmp(head->child->bro->name, "ASSIGNOP")) {
            // Exp ASSIGNOP Exp
            // printf("%s\n", head->child->bro->bro->child->name);
            if(!strcmp(head->child->bro->bro->child->name, "ID") && !head->child->bro->bro->child->bro) {
                int mark1 = 0, mark2 = 0;
                for(int i = 0; i < Regcnt; i++) {
                    if(!strcmp(VarReg[i], head->child->child->id)) {
                        mark1 = i;
                        break;
                    }
                }
                for(int i = 0; i < Regcnt; i++) {
                    if(!strcmp(VarReg[i], head->child->bro->bro->child->id)) {
                        mark2 = i;
                        break;
                    }
                }
                // printf("%d %d\n", mark1, mark2);
                fprintf(f, "move $t%d, $t%d\n", mark1, mark2);
            }
            else if(head->child->bro->bro->child->bro) {
                if(!strcmp(head->child->bro->bro->child->bro->bro->name, "RP")) {
                    // ID LP RP
                    fprintf(f, "add $sp, $sp, -4\n");
                    fprintf(f, "sw, $ra, 0($sp)\n");
                    fprintf(f, "jal %s\n", head->child->bro->bro->child->id);
                    fprintf(f, "lw $ra, 0($sp)\n");
                    fprintf(f, "addi $sp, $sp, 4\n");
                    // fprintf(f, "move $t%d, $v0\n", --Regcnt);
                    int mark = 0;
                    for(int i = 0; i < Regcnt; i++) {
                        if(!strcmp(VarReg[i], head->child->child->id)) {
                            mark = i;
                            break;
                        }
                    }
                    fprintf(f, "move $t%d, $v0\n", mark);
                    // 打表式翻译
                }
                else if(!strcmp(head->child->bro->bro->child->bro->name, "PLUS")) {
                    if(!strcmp(head->child->bro->bro->child->child->id, head->child->child->id)) {
                        // 特殊情况，如i = i + 1，先不考虑寄存器分配
                        int mark = 0;
                        for(int i = 0; i < Regcnt; i++) {
                            if(!strcmp(VarReg[i], head->child->child->id)) {
                                mark = i;
                                break;
                            }
                        }
                        fprintf(f, "addi, $t%d, $t%d, %d\n", mark, mark, head->child->bro->bro->child->bro->bro->child->intValue);
                    }
                }
            }
            else if(head->child->bro->bro->child->bro->bro->bro) {
                // ID LP Args RP，没遇到暂时不写
                if(!strcmp(head->child->bro->bro->child->bro->bro->bro->name, "RP")) {
                // ID LP Args RP，没遇到暂时不写
                }
            }
            else {
                printf("no\n");
            }
        }
        if(!strcmp(head->child->bro->bro->name, "Args")) { // ID LP ARGS RP
            int mark = 0; // 默认值可能有问题
            for(int i = 0; i < Regcnt; i++) {
                if(!strcmp(VarReg[i], head->child->bro->bro->child->child->id)) {
                    // 只针对单个参数
                    mark = i;
                    break;
                }
            }
            fprintf(f, "move $a0, $t%d\n", mark);
            fprintf(f, "addi, $sp, $sp, -4\n");
            fprintf(f, "sw $ra, 0($sp)\n");
            fprintf(f, "jal %s\n", head->child->id);
            fprintf(f, "lw, $ra, 0($sp)\n");
            fprintf(f, "addi, $sp, $sp, 4\n");
            // 打表式翻译
        }
    }
}

//void genExp(struct node *head, FILE *f, Operand place);
// 条件表达式的翻译模式
//void genCond(struct node *head, FILE *f, Operand lable_true, Operand lable_false);

// 函数参数的翻译模式
void genArgs(struct node *head, FILE *f);