#include "asm.h"

struct Func_ {
    int size;
    char tmps[10][10];
}curFunc;

char regName[5] = "a0", arg[5], stackRet[5] = "v0";
char expReg[10]; // Exp中间变量的寄存器名
struct node* currentFunc, *ndparent;

void initFuncSt(){
    curFunc.size = 0;
    for(int i = 0; i < 10; i ++)
        strcpy(curFunc.tmps[i], "\0");
}

int allocatePos(char * id, FILE* f){ // 临时变量： +  - * / func
    int i;
    for(i = 0; i < 10 && strcmp(curFunc.tmps[i], "\0"); i ++){
        if(!strcmp(id, curFunc.tmps[i])){
            
            return i + 1;
        }
    }
    // printf(" %s : %d\n", id, i);
    strcpy(curFunc.tmps[i], id);
    curFunc.size ++;
    fprintf(f, "\taddi $sp, $sp, -4\n");
    return i + 1;
}
int Check(struct node* n1, struct node* n2){ // 1. a + (Exp) 2. ID LP Args RP
    if(!strcmp(n2->name, "Exp"))
        return 0;
    if(!strcmp(n2->name, "ID") && n2->bro && !strcmp(n2->bro->name, "LP"))
        return 0;
    return 1;
}
int allocatePos_(char * id, FILE* f){
    int i;
    for(i = 0; i < 10 && strcmp(curFunc.tmps[i], "\0"); i ++){
        
    }
    // printf(" %s : %d\n", id, i);
    strcpy(curFunc.tmps[i], id);
    curFunc.size ++;
    return i + 1;
}

int findPos(char * id){
    int i;
    for(i = curFunc.size - 1; i >= 0 && strcmp(curFunc.tmps[i], "\0"); i --){
        if(!strcmp(curFunc.tmps[i], id)) return i + 1;
    }
    printf("Not Found %s\n", id);
    return -1;
}

void Check_tmp(char* tmp, FILE* f){  // 删除临时变量
    if(!strcmp(tmp, "+") || !strcmp(tmp, "-") || !strcmp(tmp, "*") || !strcmp(tmp, "/") || !strcmp(tmp, "func")){
        for(int i = 9; i >= 0; i --){
            if(strcmp(curFunc.tmps[i], "\0") && !strcmp(tmp, curFunc.tmps[i])){
                curFunc.size --;
                strcpy(curFunc.tmps[i], "\0");
                fprintf(f, "\taddi $sp, $sp, 4\n");
                return;
            }
        }
        printf("临时变量删除失败（不可能吧\n");
    }
}

void Load(struct node* nd, int rg, FILE* f){
    if(!strcmp(nd->name, "INT")){ // 常量
        fprintf(f, "\tli $t%d, %d\n", rg, nd->intValue);
    }
    else if(!strcmp(nd->name, "ID") && (nd->bro == NULL || strcmp(nd->bro->name, "LP"))) {  // 变量
        int p = findPos(nd->id); // printf("load id : %s\n", nd->id);
        fprintf(f, "\tlw $t%d, %d($fp)\n", rg, -4 * p);
    }
    else if(nd->child && !strcmp(nd->child->name, "ID") && (!strcmp(nd->child->id, "read") || !strcmp(nd->child->id, "write"))){
        genExp(nd, f);
        fprintf(f, "\tmove $t%d, $v0\n", rg);
    }
    else{ // Exp 先看看有哪几种情况
        // printf("!!!%s\n", nd->name);
        char tmp[10]; // genExp(nd, f);
        // if(!strcmp(nd->child->name, "ID"))
            // printf("??? : %s\n", nd->child->name); 
        // if(!strcmp(nd->child->name, "LP")) 
        //     {nd = nd->child->bro;printf("???%s\n", nd->name);}
        if(!strcmp(nd->name, "Exp")){
            strcpy(tmp, genExp(nd, f)); printf("tmp : %s\n", tmp);
        }
        else {
            strcpy(tmp, genExp(ndparent, f)); printf("tmp : %s\n", tmp);
        }
        // // printf("tmp == NULL? %d\n", tmp == NULL);
        int p = findPos(tmp);
        fprintf(f, "\tlw $t%d, %d($fp)\n", rg, -4 * p);
        Check_tmp(tmp, f);
    }
}

int flg = 0;
int findReg(){
    return flg ++;
}

int findMark(char* id) {
	int mark = 0;
    for(int i = 0; i < Regcnt; i++) {
        if(!strcmp(VarReg[i], id)) {
            mark = i;
            break;
        }
    }
    return mark;
}

int findNum2(int n, FILE* f) {
	if(n == 0){
		fprintf(f, "\tli $t0, 0\n");
		return 0;
	} 
	for(int i = Regcnt; i < 20; i ++ ) {
		if(ImmReg[i] == n) {
			fprintf(f, "\tli $t%d, %d\n", i, n);
			return i;
		}
		else if(ImmReg[i] == 0) {
			fprintf(f, "\tli $t%d, %d\n", i, n);
			ImmReg[i] = n;
			return i;
		}
	}
}

struct Queue {
    char name[10];
    struct Queue* nxt;
};

struct Queue* hed; // 队首存main

void pushQueue(struct Queue* Qhed, char* name) { // printf("push!!\n");
    if(!strcmp(name, "read") || !strcmp(name, "write")) return;
    struct Queue* tmp;
    tmp = (struct Queue*)malloc(sizeof(struct Queue*)); // printf("1\n");
    strcpy(tmp->name, name);
    tmp->nxt = NULL; 
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue*));
    q = Qhed;
    while(q->nxt){
        if(!strcmp(q->name, name)) return;
        q = q->nxt;
    }
    q->nxt = tmp; // printf("pushover!!\n");
}

void bfsgenExtDefList(struct node* head, FILE* fp) {
    // printf("start\n");
    
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue*));
    currentFunc = (struct node*)malloc(sizeof(struct node));
    ndparent = (struct node*)malloc(sizeof(struct node));
    q = hed; // printf("%s\n", q.name);
    struct node p = *head;
    
    while(q){
    // printf("%s\n", p.child->child->bro->child->name);
        strcpy(arg, "");
        // strcpy(stackRet, "");
        // strcpy(regName, "");

        p = *head;
        while(p.child && strcmp(q->name, p.child->child->bro->child->id)) { // printf("%s\n", p.child->id);
            p = *(p.child->bro);
        }
        // printf("%s\n", p.child->child->bro->child->id);
        currentFunc = p.child->child->bro;
        // printf("%s\n", currentFunc->name);
        initFuncSt();
        genExtDef(p.child, fp);
        // if(q->nxt)
        q = q->nxt;
        // else break;
    }
}

void genAsm(struct node* head, FILE* fp) {
    // for(int i = 0; VarReg[i] && i < 10; i ++) printf("%s\n", VarReg[i]);
    
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
    fprintf(fp, "\tjr $ra\n");
    fprintf(fp, "write:\n");
    fprintf(fp, "\tlw $a0, 0($sp)\n");
    fprintf(fp, "\tli $v0, 1\n");
    fprintf(fp, "\tsyscall\n");
    fprintf(fp, "\tli $v0, 4\n");
    fprintf(fp, "\tla $a0, _ret\n");
    fprintf(fp, "\tsyscall\n");
    fprintf(fp, "\tmove $v0, $0\n");
    fprintf(fp, "\tjr $ra\n");

    
    hed = (struct Queue*)malloc(sizeof(struct Queue*));
    strcpy(hed->name, "main"); 
    hed->nxt = NULL; 
    bfsgenExtDefList(head->child, fp);
    // printf("1\n");
    // genExtDefList(head->child, fp); 
    // free(hed);
}


void genExtDefList(struct node* head, FILE* fp) {  // 懒得改了一样的道理
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
    if(!strcmp(head->child->id, "main"))
        fprintf(f, "\tmove $fp, $sp\n");
    else
        allocatePos_("$ra", f);
    if(head->child->bro) {
        genVarList(head->child->bro->bro, f);
    }
}

void genVarList(struct node *head, FILE *f) { // printf("%s\n", currentFunc->id);
    // 好像不用生成，跟栈有关
    if(strcmp(head->name, "VarList")) return;
    if(head->child) {
        // printf("Var: %s\n", head->child->child->bro->child->name);
        // Load(head->child->child->bro->child, 0, f);
        // allocatePos(head->child->child->bro->child->id, f);
        allocatePos_(head->child->child->bro->child->id, f);
        // fprintf(f, "\tsw $t0, 0($fp)\n");
        if(head->child->bro)
            genVarList(head->child->bro->bro, f);   
    }
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
        genStmt(head->child, f);
        genMid(head->child->bro, f);
    }
}

// 语句列表的翻译模式
void genStmtList(struct node *head, FILE *f);
// 语句的翻译模式
void genStmt(struct node *head, FILE *f) {
    int back1, back2, back3;
    if(!strcmp(head->child->name, "Exp")) {
    	//printf("tag1\n");
        genExp(head->child, f);
    }
    if(!strcmp(head->child->name, "CompSt")) {
        genCompSt(head->child, f);
    }
    if(!strcmp(head->child->name, "RETURN")) { 
        // RETURN Exp
        printf("st\n");
        if(head->child->bro->child->type == INT_TYPE) {
            fprintf(f, "\tmove $v0, $%d\n", head->child->bro->child->intValue);
            fprintf(f, "\tjr $ra\n");
        }
        else if(head->child->bro->child->type == FLOAT_TYPE) {
            fprintf(f, "\tmove $v0, $%f\n", head->child->bro->child->floatValue);
            fprintf(f, "\tjr $ra\n");
        }
        else if(!strcmp(head->child->bro->child->name, "ID")) {
            Load(head->child->bro->child, 0, f);
            fprintf(f, "\tmove $v0, $t0\n");
            fprintf(f, "\tjr $ra\n");
        }
        else if(head->child->bro->child->bro) { // return一个运算式
             char tmp[10];
             strcpy(tmp, genExp(head->child->bro, f)); printf("return : %s\n", tmp);
            // Load(head->child->bro->child->bro, 0, f);
            // fprintf(f, "\tmove $v0, $t0\n");
            int p = findPos(tmp);
            fprintf(f, "\tlw $v0, %d($fp)\n", -4 * p);
            Check_tmp(tmp, f);
            fprintf(f, "\tjr $ra\n");
        }
        printf("ed\n");
    }
    if(!strcmp(head->child->name, "IF")) {
    	// 仅考虑IF LP Exp RP Stmt ELSE Stmt, 未考虑不存在ELSE的情况
    	//fprintf(f, "before\n");
    	if(head->child->bro->bro->child->bro) {
    		//fprintf(f, "tag1\n");
            if(!strcmp(head->child->bro->bro->child->bro->name, "RELOP")){ // EXP RELOP EXP 不包括Exp非INT/ID的情况！
                // printf("%s %s %s\n", head->child->bro->bro->child->child->id, head->child->bro->bro->child->bro->id, head->child->bro->bro->child->bro->bro->child->name);
                // 先翻译 左边 t0
                if(!strcmp(head->child->bro->bro->child->child->name, "INT")){
                    fprintf(f, "\tli $t0, %d\n", head->child->bro->bro->child->child->intValue);
                }
                else if(!strcmp(head->child->bro->bro->child->child->name, "ID")) {
                    int p = findPos(head->child->bro->bro->child->child->id);
                    fprintf(f, "\tlw $t0, %d($fp)\n", -4 * p);
                }
                // 再翻译 右边 t1
                 if(!strcmp(head->child->bro->bro->child->bro->bro->child->name, "INT")){
                    fprintf(f, "\tli $t1, %d\n", head->child->bro->bro->child->bro->bro->child->intValue);
                }
                else if(!strcmp(head->child->bro->bro->child->bro->bro->child->name, "ID")) {
                    int p = findPos(head->child->bro->bro->child->bro->bro->child->id);
                    fprintf(f, "\tlw $t1, %d($fp)\n", -4 * p);
                }
                char * relop = (char*)malloc(sizeof(head->child->bro->bro->child->bro->id));
                strcpy(relop, head->child->bro->bro->child->bro->id);
                if(strcmp(relop, "==")==0){
                    fprintf(f, "\tbeq $t0, $t1, %s\n", head->child->bro->bro->bro->bro->id);
                }
                else if(strcmp(relop, "!=")==0){
                    fprintf(f, "\tbne $t0, $t1, %s\n", head->child->bro->bro->bro->bro->id);
                }
                else if(strcmp(relop, ">")==0){
                    fprintf(f, "\tbgt $t0, $t1, %s\n", head->child->bro->bro->bro->bro->id);
                }
                else if(strcmp(relop, "<")==0){
                    fprintf(f, "\tblt $t0, $t1, %s\n", head->child->bro->bro->bro->bro->id);
                }
                else if(strcmp(relop, ">=")==0){
                    fprintf(f, "\tbge $t0, $t1, %s\n", head->child->bro->bro->bro->bro->id);
                }
                else if(strcmp(relop, "<=")==0){
                    fprintf(f, "\tble $t0, $t1, %s\n", head->child->bro->bro->bro->bro->id);
                }
            }
    	}
    	//fprintf(f, "after\n");
    	fprintf(f, "\tj %s\n", head->child->bro->bro->bro->bro->bro->bro->id);
    	fprintf(f, "%s:\n", head->child->bro->bro->bro->bro->id);
        // printf("%s\n", head->child->bro->bro->bro->bro->child->name);
    	genStmt(head->child->bro->bro->bro->bro, f);
    	// fprintf(f, "after\n");
    	fprintf(f, "\tj %s\n", head->id);			// to be revised
    	fprintf(f, "%s:\n", head->child->bro->bro->bro->bro->bro->bro->id);
    	//printf("before\n");
        // printf("%s\n", head->child->bro->bro->bro->bro->bro->bro->child->name);
    	genStmt(head->child->bro->bro->bro->bro->bro->bro, f);
    	fprintf(f, "%s:\n", head->id);				// to be revised
    }
    if(!strcmp(head->child->name, "WHILE")) {
        // WHILE LP Exp RP Stmt
        // whilecnt = 0;
        
        fprintf(f, "%s:\n", head->id);
        if(head->child->bro->bro->child->bro) {
            if(!strcmp(head->child->bro->bro->child->bro->id, "<")) {
                fprintf(f, "\tmove $a1, $sp\n");
                // int mark1 = 0, mark2 = 0;
                // for(int i = 0; i < Regcnt; i++) {
                //     if(!strcmp(VarReg[i], head->child->bro->bro->child->child->id)) {
                //         mark1 = i;
                //         break;
                //     }
                // }
                // for(int i = 0; i < Regcnt; i++) {
                //     if(!strcmp(VarReg[i], head->child->bro->bro->child->bro->bro->child->id)) {
                //         mark2 = i;
                //         break;
                //     }
                // }
                // fprintf(f, "\tblt $t%d, $t%d, %s\n", mark1, mark2, head->child->bro->bro->bro->bro->id);
                if(Check(head->child->bro->bro->child->child, head->child->bro->bro->child->bro->bro->child)){
                    Load(head->child->bro->bro->child->child, 0, f);
                    Load(head->child->bro->bro->child->bro->bro->child, 1, f);
                }
                else {
                    Load(head->child->bro->bro->child->bro->bro->child, 1, f);
                    Load(head->child->bro->bro->child->child, 0, f);
                }
                char * relop = (char*)malloc(sizeof(head->child->bro->bro->child->bro->id));
                strcpy(relop, head->child->bro->bro->child->bro->id);
                if(strcmp(relop, "==")==0){
                    fprintf(f, "\tbeq $t0, $t1, %s\n", head->child->bro->bro->bro->bro->id);
                }
                else if(strcmp(relop, "!=")==0){
                    fprintf(f, "\tbne $t0, $t1, %s\n", head->child->bro->bro->bro->bro->id);
                }
                else if(strcmp(relop, ">")==0){
                    fprintf(f, "\tbgt $t0, $t1, %s\n", head->child->bro->bro->bro->bro->id);
                }
                else if(strcmp(relop, "<")==0){
                    fprintf(f, "\tblt $t0, $t1, %s\n", head->child->bro->bro->bro->bro->id);
                }
                else if(strcmp(relop, ">=")==0){
                    fprintf(f, "\tbge $t0, $t1, %s\n", head->child->bro->bro->bro->bro->id);
                }
                else if(strcmp(relop, "<=")==0){
                    fprintf(f, "\tble $t0, $t1, %s\n", head->child->bro->bro->bro->bro->id);
                }
                
                fprintf(f, "\tj %s\n", head->child->bro->bro->id);
                fprintf(f, "%s:\n", head->child->bro->bro->bro->bro->id);
                // printf("%s\n", head->child->bro->bro->bro->bro->child->child->bro->child->name);
                genStmt(head->child->bro->bro->bro->bro, f);
                fprintf(f, "\tmove $sp, $a1\n");
                fprintf(f, "\tj %s\n", head->id);
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
        // do{
            genDecList(newnode, f);
        //     if(newnode->child->bro)
        //         newnode = newnode->child->bro->bro;
        //     else break;
        // } while(newnode->child->bro);
        // 数组，留着
    }
}

void genDecList(struct node *head, FILE *f) {
    if(head && strcmp(head->name, "DecList")) return;
    genDec(head->child, f);
    if(head->child->bro)
        genDecList(head->child->bro->bro, f);
}

void genVarDec(struct node *head, FILE *f) {
    // Load();
    // allocatePos(head->child->id, f);
    // fprintf(f, "\tli $t%d, ", mark);
    // // fprintf(f, "li $t%d, ", --Regcnt); // 维护Regcnt
    // // 如何建立寄存器名与变量名的对应关系
}

void genDec(struct node *head, FILE *f) { // printf("!!!\n");
    // printf("%s\n", head)
    if(head->child->bro) {
        if(!strcmp(head->child->bro->bro->child->name, "INT") || !strcmp(head->child->bro->bro->child->name, "FLOAT")) {
            // genVarDec(head->child, f);
            // // // genExp(head->child->bro->bro, f); // 可能涉及打印先后次序问题，暂不调用
            // if(!strcmp(head->child->bro->bro->child->name, "INT")) {
            //     fprintf(f, "%d\n", head->child->bro->bro->child->intValue);
            // }
            // if(!strcmp(head->child->bro->bro->child->name, "FLOAT")) {
            //     fprintf(f, "%f\n", head->child->bro->bro->child->floatValue);
            // }
            Load(head->child->bro->bro->child, 0, f);
            int p = allocatePos(head->child->child->id, f);
            fprintf(f, "\tsw $t0, %d($fp)\n", -4 * p);
            
        }
        else if(!strcmp(head->child->bro->bro->child->bro->name, "PLUS")) { // printf("PPPlus\n");
            struct node* newnode = head->child->bro->bro->child; // newnode指向PLUS前面的Exp
            
            if(Check(head->child->bro->bro->child->child, head->child->bro->bro->child->bro->bro->child)){
                Load(head->child->bro->bro->child->child, 1, f); // printf("PPPlus\n");
                Load(head->child->bro->bro->child->bro->bro->child, 2, f); // printf("PPPlus\n");
            }
            else {
                Load(head->child->bro->bro->child->bro->bro->child, 2, f); // printf("PPPlus\n");
                Load(head->child->bro->bro->child->child, 1, f); // printf("PPPlus\n");
            }
            
            // printf("!@#%s\n", head->child->bro->bro->child->bro->bro->child->id);
            fprintf(f, "\tadd $t0, $t1, $t2\n");// printf("all: %s\n", head->child->child->name);
            int p = allocatePos(head->child->child->id, f);
            fprintf(f, "\tsw $t0, %d($fp)\n", -4 * p);
        }
    }
    else{
        allocatePos(head->child->child->id, f);
    }

}

// 基本表达式的翻译模式
char* genExp(struct node *head, FILE *f) {
    if(!strcmp(head->child->name, "LP")) {
        return genExp(head->child->bro, f);
    }
    // printf("%s\n", head->child->name);
    /*if(!strcmp(head->child->name, "INT")) {
        sprintf(expReg, "%d", head->child->intValue);
        return expReg;
    }
    else if(!strcmp(head->child->name, "FLOAT")) {
        sprintf(expReg, "%f", head->child->floatValue);
        return expReg;
    }
    else if(!strcmp(head->child->name, "ID")) {
        sprintf(expReg, "%s", head->child->id);
        return expReg;
    }*/

    if(head->child->bro) {
        // printf("ddd%s\n", head->child->bro->name);
        if(!strcmp(head->child->bro->name, "ASSIGNOP")) {
            // Exp ASSIGNOP Exp
            // printf("left: %s\n", head->child->child->id);
            // 先处理右边
            if(!strcmp(head->child->bro->bro->child->name, "INT")) {
            	int p = findPos(head->child->child->id);
            	fprintf(f, "\tli $t0, %d\n", head->child->bro->bro->child->intValue);
                
                fprintf(f, "\tsw $t0, %d($fp)\n", -4 * p);
                sprintf(expReg, "t0");
                return expReg;
            }
            else if(!strcmp(head->child->bro->bro->child->name, "ID") && !head->child->bro->bro->child->bro) {
                // Exp(ID) = Exp(ID)
                //  printf("!!!%s\n", head->child->bro->bro->child->id);
                // 先右边
                int p = findPos(head->child->bro->bro->child->id);
                fprintf(f, "\tlw $t1, %d($fp)\n", -4 * p);

                fprintf(f, "\tmove $t0, $t1\n");
                // 在左边
                p = findPos(head->child->child->id);
                fprintf(f, "\tsw $t0, %d($fp)\n", -4 * p);

                sprintf(expReg, "t0");
                return expReg;
            }
            else if(head->child->bro->bro->child->bro->bro->bro) {	// 一定要注意先写长的再写短的
            	// ID LP Args RP
                // printf("!!!%s\n", head->child->bro->bro->child->id);
                pushQueue(hed, head->child->bro->bro->child->id);
                genExp(head->child->bro->bro, f);
                int p = findPos(head->child->child->id);
                fprintf(f, "\tmove $t0, $v0\n"); // 赋值
                fprintf(f, "\tsw $t0, %d($fp)\n", -4*p);

                sprintf(expReg, "t0");
                return expReg;
            }
            else if(head->child->bro->bro->child->bro) {
                // 运算式/函数调用赋值给变量
            	// printf("choice3\n");
                // printf("!!!%s\n", head->child->bro->bro->child->id);
                char tmp[5];
                // strcpy(tmp, genExp(head->child->bro->bro, f));
                // printf("%s\n", tmp);
                Load(head->child->bro->bro, 1, f);
                sprintf(expReg, "t0");
                if(strcmp(expReg, tmp)) { // 不是自增
                    fprintf(f, "\tmove $t0, $t1\n");
                }
                int p = findPos(head->child->child->id);
                fprintf(f, "\tsw $t0, %d($fp)\n", -4*p);
                return expReg;
            }
            else {
                printf("no\n");
            }
        }
        // else if(!strcmp(head->child->bro->name, "RELOP")){
        //     // 先翻译 左边 t0
        //     Load(head->child->child, 0, f);
            
        //     // 再翻译 右边 t1
        //     Load(head->child->bro->child, 1, f);
            
        // }
        // else if(!strcmp(head->child->bro->name, "LP")){ // printf("HERE\n");
        //     // ID LP Exp RP
        //     fprintf(f, "\taddi $sp, $sp, -4\n");
        //         // fprintf(f, "\tsw $a0, 0($sp)\n");
        //     fprintf(f, "\tsw $ra, 4($sp)\n");
        //     int Vnum = genArgs(head->child->bro->bro, f);
            
        //     fprintf(f, "\tjal %s\n", head->child->id);
        //     // fprintf(f, "\tlw $a0, 0($sp)\n");
        //     fprintf(f, "\tlw $ra, %d($sp)\n", 4*Vnum);
        //     fprintf(f, "\taddi $sp, $sp, %d\n", 4 + Vnum*4);
        //     for(int i = Vnum;i;i--){
        //         strcpy(curFunc.tmps[curFunc.size - 1], "\0");
        //         curFunc.size -- ;
        //     }
        //     fprintf(f, "\tmove $fp, $sp\n");
        // }
        else if(!strcmp(head->child->bro->name, "STAR")) {
            char tmp1[5], tmp2[5];
            if(Check(head->child->child, head->child->bro->bro->child)){
                ndparent = head->child;
                Load(head->child->child, 1, f);
                Load(head->child->bro->bro->child, 2, f);
            }
            else {
                ndparent = head->child->bro->bro;
                Load(head->child->bro->bro->child, 2, f);
                Load(head->child->child, 1, f);
            }
            fprintf(f, "\tmul $t0, $t1, $t2\n");
            
            int p = allocatePos("*", f);
            fprintf(f, "\tsw $t0, %d($fp)\n", -4 * p);
            return "*";
            
        }
        else if(!strcmp(head->child->bro->name, "MINUS")) {
            if(Check(head->child->child, head->child->bro->bro->child)){
                Load(head->child->child, 1, f);
                Load(head->child->bro->bro->child, 2, f);
            }
            else {
                Load(head->child->bro->bro->child, 2, f);
                Load(head->child->child, 1, f);
            }
            fprintf(f, "\tsub $t0, $t1, $t2\n");
            
            int p = allocatePos("-", f);
            fprintf(f, "\tsw $t0, %d($fp)\n", -4 * p);
            return "-";
        }
        else if(!strcmp(head->child->bro->name, "PLUS")) { // printf("yes\n");

            if(Check(head->child->child, head->child->bro->bro->child)){
                Load(head->child->child, 1, f);
                Load(head->child->bro->bro->child, 2, f);
            }
            else {
                Load(head->child->bro->bro->child, 2, f);
                Load(head->child->child, 1, f);
            }
            fprintf(f, "\tadd $t0, $t1, $t2\n");
            
            int p = allocatePos("+", f);
            fprintf(f, "\tsw $t0, %d($fp)\n", -4 * p);
            return "+";
        }
        else if(!strcmp(head->child->bro->name, "DIV")) {
            
            if(Check(head->child->child, head->child->bro->bro->child)){
                Load(head->child->child, 1, f);
                Load(head->child->bro->bro->child, 2, f);
            }
            else {
                Load(head->child->bro->bro->child, 2, f);
                Load(head->child->child, 1, f);
            }
            fprintf(f, "\tdiv $t1, $t2\n");
            fprintf(f, "\tmflo $t0\n");
            int p = allocatePos("/", f);
            fprintf(f, "\tsw $t0, %d($fp)\n", -4 * p);
            return "/";
        }
        else if(!strcmp(head->child->bro->bro->name, "Args")) {
            // Exp : ID LP ARGS RP
            // printf("%s %s\n", head->child->id, currentFunc->child->id);



            if(strcmp(head->child->id, currentFunc->child->id)) { // 如果当前翻译的函数不是递归的，则需单独传参
                
                // fprintf(f, "\tmove $a0, $t%d\n", findMark(head->child->bro->bro->child->child->id));
            }
            if(!strcmp(currentFunc->child->bro->bro->name, "VarList")) { // 如果当前函数是有参函数
            // if(!strcmp(head->child->bro->bro->name, "Args")) {
                // fprintf(f, "\tmove $fp, $sp\n");
                fprintf(f, "\taddi $sp, $sp, -4\n");
                // fprintf(f, "\tsw $a0, 0($sp)\n");
                fprintf(f, "\tsw $ra, 0($sp)\n");
                allocatePos_("$ra", f);
                int Vnum = genArgs(head->child->bro->bro, f);
                fprintf(f, "\taddi $fp, $sp, %d\n", 4 + Vnum*4);
                fprintf(f, "\tjal %s\n", head->child->id);
                // fprintf(f, "\tlw $a0, 0($sp)\n");
                fprintf(f, "\tlw $ra, %d($sp)\n", 4*Vnum);
                fprintf(f, "\taddi $sp, $sp, %d\n", 4 + Vnum*4);
                
                for(int i = Vnum+1;i;i--){
                    strcpy(curFunc.tmps[curFunc.size - 1], "\0");
                    curFunc.size -- ;
                }
                fprintf(f, "\taddi $fp, $sp, %d\n", 4 * curFunc.size);
                // fprintf(f, "\tmove $fp, $sp\n");
                int p = allocatePos("func", f);
                fprintf(f, "\tmove $t0, $v0\n"); // 赋值
                fprintf(f, "\tsw $t0, %d($fp)\n", -4 * p);
                return "func";
            }
            else { // 如果当前函数是无参函数
                fprintf(f, "\taddi $sp, $sp, -4\n");
                fprintf(f, "\tsw $ra, 0($sp)\n");
                allocatePos_("$ra", f);
                int Vnum = genArgs(head->child->bro->bro, f);
                fprintf(f, "\taddi $fp, $sp, %d\n", 4 + Vnum*4);
                fprintf(f, "\tjal %s\n", head->child->id);
                fprintf(f, "\tlw $ra, %d($sp)\n", 4*Vnum);
                fprintf(f, "\taddi $sp, $sp, %d\n", 4 + Vnum*4);
                for(int i = Vnum+1;i;i--){
                    strcpy(curFunc.tmps[curFunc.size - 1], "\0");
                    curFunc.size -- ;
                }
                fprintf(f, "\taddi $fp, $sp, %d\n", 4 * curFunc.size);
                // fprintf(f, "\tmove $fp, $sp\n");
            }
            // 打表式翻译
            strcpy(regName, "a0"); // 传入的参数寄存器
            strcpy(arg, head->child->bro->bro->child->child->id); // 参数名，暂只考虑单个
            strcpy(stackRet, "v0"); // 函数的返回值寄存器

            return stackRet;
        }
        else if(!strcmp(head->child->bro->name, "LP") && !strcmp(head->child->bro->bro->name, "RP")) {
            // ID LP RP
            pushQueue(hed, head->child->id);
            
            fprintf(f, "\taddi $sp, $sp, -4\n");
            fprintf(f, "\tsw $ra, 0($sp)\n");
            fprintf(f, "\tjal %s\n", head->child->id);
            fprintf(f, "\tlw $ra, 0($sp)\n");
            fprintf(f, "\taddi $sp, $sp, 4\n");
            
            strcpy(expReg, "v0");
            return expReg;
        }
        
    }
    else if(head->bro){
        if(!strcmp(head->bro->name, "MINUS")) {
            
            if(Check(head->child, head->bro->bro->child)){
                Load(head->child, 1, f);
                Load(head->bro->bro->child, 2, f);
            }
            else {
                Load(head->bro->bro->child, 2, f);
                Load(head->child, 1, f);
            }
            fprintf(f, "\tsub $t0, $t1, $t2\n");
            
            int p = allocatePos("-", f);
            fprintf(f, "\tsw $t0, %d($fp)\n", -4 * p);
            return "-";
        }
    }
    // else { 
    //     if(head->child) genExp(head->child);
    // }
}

//void genExp(struct node *head, FILE *f, Operand place);
// 条件表达式的翻译模式
//void genCond(struct node *head, FILE *f, Operand lable_true, Operand lable_false);

// 函数参数的翻译模式
int genArgs(struct node *head, FILE *f) {
    // Exp COMMA Args
    int Varnum = 0;
    struct node* newArg = head; // newArg始终指向Args
    do {
        Varnum ++;
        Load(newArg->child->child, 0, f);
        // printf("%s\n", newArg->child->child->name);
        char tmp[10];
        sprintf(tmp, "Var_%d", Varnum);
        int p = allocatePos(tmp, f);
        fprintf(f, "\tsw $t0, %d($fp)\n", -4 * p);
        
        if(newArg->child->bro) {
            newArg = newArg->child->bro->bro;
        }
        else {
            break;
        }
    } while(newArg->bro);
    return Varnum;
}
