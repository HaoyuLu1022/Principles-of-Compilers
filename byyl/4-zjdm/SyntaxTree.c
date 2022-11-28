#include <malloc.h>
#include "SyntaxTree.h"

int t[100];		//存储临时变量，仅用于在程序中的立即数，其余变量直接用其原名
//int top = 1;	//用来指示变量名用到哪个位置了
int r = 1;		//用来指示label的标签

struct node *iniNode(char *name, int lines, NODE_TYPE t) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->bro = NULL;
    newNode->child = NULL;
    newNode->lines = lines;
    newNode->type = t;
    newNode->name = name;
    newNode->isAssignable = 1;
    if(!strcmp(newNode->name, "INT") || newNode->type == INT_TYPE) {
        newNode->intValue = atoi(yytext);
        strcpy(newNode->property, "int");
    }
        
    else if(!strcmp(newNode->name, "FLOAT") || newNode->type == FLOAT_TYPE) {
        newNode->type = atof(yytext);
        strcpy(newNode->property, "float");
    }
        
    else newNode->intValue = 1;
    return newNode;
}

struct node *insNode(struct node *n, char *name, int lines, NODE_TYPE t) {
    struct node *parent = (struct node *)malloc(sizeof(struct node));
    parent->bro = NULL;
    parent->child = n;
    parent->lines = lines;
    parent->type = t;
    parent->name = strdup(name);
    parent->intValue = 1;
    head = parent;
    return parent;
}

void printNode(struct node *n, FILE *f, int depth) {
    if(n->type == STRING_TYPE) {
        fprintf(f, "%s : %s\n", n->name, n->id);
    }
    else if(!strcmp(n->name, "INT")) { // n->type == INT_TYPE
        fprintf(f, "INT : %d\n", n->intValue);
    }
    else if(!strcmp(n->name, "FLOAT")) { // n->type == FLOAT_TYPE
        fprintf(f, "FLOAT : %f\n", n->floatValue);
    }
    else {
        // printf("%d\n", strcmp(n->name, "Mid"));
        if(strcmp(n->name, "Mid") == 0){
            // printf("Yes!!");
            fprintf(f, "Empty : Empty\n");
            if (n->child != NULL && strcmp(n->child->name, "Stmt") == 0){
                for(int i = 0; i < depth; i++) {
                    fprintf(f, "\t");
                }
                fprintf(f, "StmtList (%d)\n", n->lines);
            }
            else if(n->child != NULL){
                for(int i = 0; i < depth; i++) {
                    fprintf(f, "\t");
                }
                fprintf(f, "DefList (%d)\n", n->lines);
            }
        }
        else
            fprintf(f, "%s (%d)\n", n->name, n->lines);
    }
}

void printTree(struct node *head, int depth, FILE *f) {
    if(head == NULL) return;
    for(int i = 0; i < depth; i++) {
        fprintf(f, "\t");
    }
    printNode(head, f, depth);
    printTree(head->child, depth+1, f);
    printTree(head->bro, depth, f);
}

int findNum(int n) {
	for(int i = 0; i <= 99; i ++ ){
		if(t[i] == n) return i;
		else if(t[i] == 0 && i > 0) return i;
	}
}

void translate_Program(struct node *head, FILE *f) {
	translate_ExtDefList(head->child, f);
}

void translate_ExtDefList(struct node *head, FILE *f) {
	if(head->child == NULL) return;
	translate_ExtDef(head->child, f);
	translate_ExtDefList(head->child->bro, f);
}

void translate_ExtDef(struct node *head, FILE *f) {
	translate_Specifier(head->child, f);
	if(head->child->bro->bro != NULL){
		if(!strcmp(head->child->bro->name, "ExtDecList")){
			translate_ExtDecList(head->child->bro, f);
		}
		else if(!strcmp(head->child->bro->name, "FunDec")){
			translate_FunDec(head->child->bro, f);				
			translate_CompSt(head->child->bro->bro, f);		
		}
	}
}

void translate_Specifier(struct node *head, FILE *f) {
	if(!strcmp(head->child->name, "TYPE")) translate_TYPE(head->child, f);		
	if(!strcmp(head->child->name, "StructSpecifier")) translate_StructSpecifier(head->child, f);
}

void translate_ExtDecList(struct node *head, FILE *f) {
	translate_VarDec(head->child, f);		//to be continued	考虑增加一个参数给此函数表示来源（变量声明是否为函数的参数）
	if(head->child->bro != NULL) translate_ExtDecList(head->child->bro->bro, f);
}

void translate_FunDec(struct node *head, FILE *f) {
	fprintf(f, "FUNCTION %s :\n", head->child->id);
	if(!strcmp(head->child->bro->bro->name, "VarList")) 
		translate_VarList(head->child->bro->bro, f);	//to be continued	考虑增加一个参数表示来源（变量声明是否为函数的参数）
}

void translate_CompSt(struct node *head, FILE *f) {
	translate_Mid(head->child->bro, f);			
}

void translate_TYPE(struct node *head, FILE *f) {
	//pass
}

void translate_StructSpecifier(struct node *head, FILE *f) {
	// to be continued
}

void translate_Mid(struct node *head, FILE *f) {
	if(head->child == NULL) return;
	else if(!strcmp(head->child->name, "Def")){
		translate_Def(head->child, f);			
		translate_Mid(head->child->bro, f);
	}
	else if(!strcmp(head->child->name, "Stmt")){
		translate_Stmt(head->child, f);				
		translate_Mid(head->child->bro, f);
	}
}

void translate_Def(struct node *head, FILE *f) {
	//pass
}

void translate_Stmt(struct node *head, FILE *f) {
	if(!strcmp(head->child->name, "CompSt")) translate_CompSt(head->child, f);
	else if(!strcmp(head->child->name, "Exp")){
		translate_Exp(head->child, f);		
		fprintf(f, "\n");
	}
	else if(!strcmp(head->child->name, "RETURN")){
		fprintf(f, "RETURN ");
		translate_Exp(head->child->bro, f);
		fprintf(f, "\n");
	}
	else if(!strcmp(head->child->name, "IF")) {
		fprintf(f, "IF ");
		translate_Exp(head->child->bro->bro, f);
		fprintf(f, "GOTO label%d\n", r);
		r += 1;
		fprintf(f, "GOTO label%d\n", r);
		r += 1;
		fprintf("LABEL fdsfdgshdhf") //忘写了
		translate_Stmt(head->child->bro->bro->bro->bro, f);
		fprintf(f, "GOTO label%d\n", r);
		r += 1;
		if(head->child->bro->bro->bro->bro->bro != NULL) translate_Stmt(head->child->bro->bro->bro->bro->bro->bro, f);
	}
	else if(!strcmp(head->child->name, "WHILE")){
		//对应产生式: Stmt : WHILE LP Exp RP Stmt
		//to be continued
	}
}

void translate_Exp(struct node *head, FILE *f) {
	if(head->child->bro == NULL){
		if(!strcmp(head->child->name, "ID")) fprintf(f, "%s ", head->child->id);
		else if(!strcmp(head->child->name, "INT")) fprintf(f, "#%d ", head->child->intValue);
	}
	else if(head->child->bro->bro == NULL){
		//没有写NOT Exp
		if(!strcmp(head->child->name, "MINUS")){
			if(!strcmp(head->child->bro->child->name, "INT")) fprintf(f, "#-%s ", head->child->bro->child->id);
			//else	好像也没有这种情况？
		}
	}
	else if(head->child->bro->bro->bro == NULL){
		if(!strcmp(head->child->name, "LP")) translate_Exp(head->child->bro, f);
		// else if(!strcmp(head->child))	需要补一个结构体的，对应产生式Exp DOT ID
		
		else if(!strcmp(head->child->name, "ID")){
			if(strcmp(head->child->id, "read")){		//调用对应的函数，写对应的语句
				//fprintf(f, "READ %s", );
			}
			// else 	Exp AssignOp Exp处有对应的操作
		}
		else if(!strcmp(head->child->bro->name, "DIV")) {
			translate_Exp(head->child, f);
			fprintf(f, "/ ");
			translate_Exp(head->child->bro->bro, f);
		}
		else if(!strcmp(head->child->bro->name, "STAR")) {
			translate_Exp(head->child, f);
			fprintf(f, "* ");
			translate_Exp(head->child->bro->bro, f);
		}
		else if(!strcmp(head->child->bro->name, "MINUS")) {
			translate_Exp(head->child, f);
			fprintf(f, "- ");
			translate_Exp(head->child->bro->bro, f);
		}
		else if(!strcmp(head->child->bro->name, "PLUS")) {
			translate_Exp(head->child, f);
			fprintf(f, "+ ");
			translate_Exp(head->child->bro->bro, f);
		}
		else if(!strcmp(head->child->bro->name, "RELOP")) {
			translate_Exp(head->child, f);
			fprintf(f, "%s ", head->child->bro->id);
			translate_Exp(head->child->bro->bro, f);
		}
		else if(!strcmp(head->child->bro->name, "OR")) {
			translate_Exp(head->child, f);
			fprintf(f, "|| ");
			translate_Exp(head->child->bro->bro, f);
		}
		else if(!strcmp(head->child->bro->name, "AND")) {
			translate_Exp(head->child, f);
			fprintf(f, "&& ");
			translate_Exp(head->child->bro->bro, f);
		}
		else if(!strcmp(head->child->bro->name, "ASSIGNOP")) {
			if(!strcmp(head->child->bro->bro->child->id, "read")){
				fprintf(f, "READ %s\n", head->child->id);
			}
			else{
				translate_Exp(head->child, f);
				fprintf(f, ":= ");
				translate_Exp(head->child->bro->bro, f);
			}
		}
	}
	else if(head->child->bro->bro->bro->bro == NULL){
		if(!strcmp(head->child->name, "ID")){
			//调用对应的有参函数
			if(!strcmp(head->child->id, "write")){
				if(!strcmp(head->child->bro->bro->child->child->name, "ID")){
					fprintf(f, "WRITE %s\n", head->child->bro->bro->child->child->id);	//ext2还需要改
				}
				else if(!strcmp(head->child->bro->bro->child->child->name, "INT")){
					//fprintf(f, "%d\n", head->child->bro->bro->child->child->intValue);
					fprintf(f, "WRITE t%d\n", findNum(head->child->bro->bro->child->child->intValue));
				}
			}
		}
		// 还差一个数组调用，对应产生式Exp LB Exp RB
	}
		
}

void translate_VarDec(struct node *head, FILE *f) {
	// to be continued
}

void translate_VarList(struct node *head, FILE *f) {

}
