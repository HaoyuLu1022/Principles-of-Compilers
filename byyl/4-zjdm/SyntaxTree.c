#include <malloc.h>
#include "SyntaxTree.h"

int t[100];		//存储临时变量，仅用于在程序中的立即数，其余变量直接用其原名
//int top = 1;	//用来指示变量名用到哪个位置了
int r = 1;		//用来指示label的标签
int returnCNT = 0, paraCNT = 0;

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

int findNum(int n, FILE *f) {
	for(int i = 0; i <= 99; i ++ ){
		if(t[i] == n) return i;
		else if(t[i] == 0 && i > 0){
			fprintf(f, "t%d := #%d\n", i, n);
			t[i] = n;
			return i;
		}
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
			fprintf(f, "\n");
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

void translate_FunDec(struct node *head, FILE *f) { // FunDec: ID LP VarList RP
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

void translate_Stmt(struct node *head, FILE *f) {		//flag用来标记结尾是否需要再加一个跳转, 若有else则为1
	// printf("Stmt\n");
	int back1, back2, back3;
	if(!strcmp(head->child->name, "CompSt")) translate_CompSt(head->child, f);
	else if(!strcmp(head->child->name, "Exp")){
		//printf("tag1\n");
		translate_Exp(head->child, f);		
		//printf("tag2\n");
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
		back1 = r; r += 1;
		fprintf(f, "GOTO label%d\n", r);
		back2 = r; r += 1;
		fprintf(f, "LABEL label%d :\n", back1);
		//printf("before\n");
		translate_Stmt(head->child->bro->bro->bro->bro, f);
		
		//printf("after\n");
		
		if(head->child->bro->bro->bro->bro->bro != NULL){
			fprintf(f, "GOTO label%d\n", r);
			back3 = r; r += 1;
			//translate_Stmt(head->child->bro->bro->bro->bro->bro->bro, f);
		}
		fprintf(f, "LABEL label%d :\n", back2);
		if(head->child->bro->bro->bro->bro->bro != NULL){
			translate_Stmt(head->child->bro->bro->bro->bro->bro->bro, f);
		}
		fprintf(f, "LABEL label%d :\n", back3);
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
			if(!strcmp(head->child->bro->child->name, "INT")) fprintf(f, "#-%d ", head->child->bro->child->intValue);
			//else	好像也没有这种情况？
		}
	}
	else if(head->child->bro->bro->bro == NULL){
		//printf("tag3\n");
		if(!strcmp(head->child->name, "LP")) translate_Exp(head->child->bro, f);
		// else if(!strcmp(head->child))	需要补一个结构体的，对应产生式Exp DOT ID
		
		else if(!strcmp(head->child->name, "ID")){
			if(strcmp(head->child->id, "read")){		//调用对应的函数，写对应的语句
				//fprintf(f, "READ %s", );
			}

			else if(!strcmp(head->child->bro->name, "LP")) { // Exp: ID LP RP
				// fprintf(f, "ARG v%d\n", returnCNT);
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
			// printf("tag4\n");
			if(!strcmp(head->child->bro->bro->child->name, "ID") && !strcmp(head->child->bro->bro->child->id, "read")){
				// printf("tag6\n");
				fprintf(f, "READ %s", head->child->child->id);
				// printf("tag9\n");
			}
			else{
				// printf("tag5\n");
				translate_Exp(head->child, f);
				// printf("tag6\n");
				fprintf(f, ":= ");
				translate_Exp(head->child->bro->bro, f);
				// printf("tag7\n");
			}
		}
	}
	else if(head->child->bro->bro->bro->bro == NULL){
		if(!strcmp(head->child->name, "ID")){
			// printf("tag8\n");
			//调用对应的有参函数
			if(!strcmp(head->child->id, "write")){
				if(!strcmp(head->child->bro->bro->child->child->name, "ID")){
					fprintf(f, "WRITE %s", head->child->bro->bro->child->child->id);	//ext2还需要改
				}
				else if(!strcmp(head->child->bro->bro->child->child->name, "INT")){
					//fprintf(f, "%d\n", head->child->bro->bro->child->child->intValue);
					fprintf(f, "WRITE t%d", findNum(head->child->bro->bro->child->child->intValue, f));
				}
				else if(!strcmp(head->child->bro->bro->child->child->name, "MINUS")){
					fprintf(f, "WRITE t%d", findNum(-head->child->bro->bro->child->child->bro->intValue, f));
				}
			}
			else if(head->child->bro) { // Exp: ID LP Args RP
			}
		}
		// 还差一个数组调用，对应产生式Exp LB Exp RB
	}
		
}

void translate_VarDec(struct node *head, FILE *f) {
	// to be continued
}

void translate_VarList(struct node *head, FILE *f) {
	fprintf(f, "PARAM %s\n", head->child->child->bro->child->id); // 可能需要考虑数组
	// paraCNT++;
}
