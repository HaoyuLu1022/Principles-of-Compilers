%{
	#include <stdio.h>
	#include <stdlib.h>
    #include <ctype.h>
    #include <assert.h>
	#include "SyntaxTree.h"
    // #include "RBTtest.c"

	#define YYSTYPE struct node*
    #include "lex.yy.c"

    #define UNDEFINED_VARIABLE 1
    #define UNDEFINED_FUNCTION 2
    #define REDEFINED_VARIABLE 3
    #define REDEFINED_FUNCTION 4
    #define TYPE_MISMATCH_ASSIGNMENT 5
    #define NEED_VARIABLE 6
    #define TYPE_MISMATCH_OPERAND 7
    #define TYPE_MISMATCH_RETURN 8
    #define FUNCTION_MISMATCH 9
    #define NOT_ARRAY 10
    #define NOT_FUNCTION 11
    #define ARRAY_ACCESS_OPERATEOR_NOT_INTEGER 12
    #define DOT_ILLEGAL_USE 13
    #define NOT_EXISTENT_FIELD 14
    #define REDEFINED_FIELD 15
    #define REDEFINED_STRUCT 16
    #define UNDEFINED_STRUCT 17
    #define DECLARED_BUT_NOT_DEFINED 18
    #define AMBIGUATING_FUNCTION_DECLARATION 19

    #define MIN(i, j) (((i) < (j)) ? (i) : (j))
    #define MAX(i, j) (((i) > (j)) ? (i) : (j))


	void yyerror(char*);
	void myerror(char*);
	int yylex();
	extern int yylineno;
	extern int last_row;
	int errors = 0;
    int yydebug = 1;
    int flgStruct = 0, flgArr = 0;
    char Compst_return_type[20] = "null";
    struct rb_root mytree = RB_ROOT;
    // MyType tmp; // 从全局变量改用局部变量
    VariLink this_scope;

    char *strlwr(char *str) {
        char *ptr = str;

        while (*ptr != '\0') {
            if (isupper(*ptr))
                *ptr = tolower(*ptr);
                ptr++;
        }

        return str;
    }
%}

%token INT
%token FLOAT
%token TYPE
%token NEWLINE
%token ID
%token SEMI COMMA DOT
%token ASSIGNOP RELOP
%token PLUS MINUS STAR DIV
%token AND OR NOT
%token LP RP LB RB LC RC
%token STRUCT
%token RETURN
%token IF
%token ELSE
%token WHILE

%left COMMA
%right ASSIGNOP
%left AND OR
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NAGATE NOT
%left LOWER_THAN_RB
%left DOT LP LB RP RB
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
Program : ExtDefList {
        $$ = insNode($1, "Program", $1->lines, NON_TERMINAL);
    }
    ;

ExtDefList : ExtDef ExtDefList {
        $$ = insNode($1, "ExtDefList", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
    }
    | {
        $$ = insNode(NULL, "ExtDefList", yylineno, NON_TERMINAL);
    }
    ;

ExtDef : Specifier ExtDecList SEMI {
        $$ = insNode($1, "ExtDef", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        struct node* newnode = $2;          
        do {
            MyType tmp = MyType_default;
            tmp.def = 1;
            // printf("flgArr = %d\n", flgArr);
            if(!flgArr) { // 不是数组
                // printf("%s\n", newnode->child->child->id);
                // tmp.name = (char*)malloc(sizeof(newnode->child->child->id));
                strcpy(tmp.name, newnode->child->child->id);
            }
            else { // 是数组
                // tmp.name = (char*)malloc(sizeof(newnode->child->child->child->child->id));
                // printf("array name: %s\n", newnode->child->child->child->child->id);
                strcpy(tmp.name, newnode->child->child->child->child->id);
            }

            // printf("Scope: %d\n", this_scope->top);
            if(search(this_scope, tmp)) { // 两种可能：struct xx {...} yy; 或 int a;
                char msg[100];
                if(!flgStruct) {// 普通变量声明
                    errors++;
                    printf("Error %d at line %d : Redefined variable \'%s\'\n", REDEFINED_VARIABLE, last_row, tmp.name);
                    // sprintf(msg, "Error %d at line %d : Redefined variable \'%s\'", REDEFINED_VARIABLE, last_row, tmp.name);
                }
                else {// 结构体变量声明
                    errors++;
                    printf("Error %d at line %d : Redefined field \'%s\'\n", REDEFINED_FIELD, last_row, tmp.name);
                    // sprintf(msg, "Error %d at line %d : Redefined field \'%s\'", REDEFINED_FIELD, last_row, tmp.name);
                }
                // myerror(msg);
            }

            // printf("flgStruct: %d\n", flgStruct);
            if(flgStruct) { // 是struct tag的情况，如struct sa nn;
                tmp.isstruct = 1;
                // printf("struct type: %s with isStruct: %d\n", $1->child->child->bro->child->id, tmp.isstruct);
                // tmp.type = (char*)malloc(sizeof($1->child->child->bro->child->id));
                
                strcpy(tmp.type, $1->child->child->bro->child->id);
                flgStruct = 0;
            }
            else { // 一般变量，如int a，结构体内和一般声明均是;
                // printf("%s\n", $1->child->id);
                // tmp.type = (char*)malloc(sizeof($1->child->id));
                strcpy(tmp.type, $1->child->id);
                if(flgArr) { // 是数组
                    tmp.isarr = 1;
                    tmp.dimension = newnode->child->child->child->bro->bro->intValue;
                    // flgArr = 0;
                }
            }
            // printf("Variable %s has type %s\n", tmp.name, tmp.type);
            tmp.isvariable = 1;
            this_scope = insert(this_scope, tmp);
                
            if(newnode->child->bro != NULL) // 不这么写感觉没办法写循环
                newnode = newnode->child->bro->bro; // 让newnode始终指向DecList
            else break; // 可能为NULL，提前终止，避免报错
        } while(newnode != NULL);

        // flgStruct = 0;
        flgArr = 0;        
    }
    | Specifier SEMI {
        $$ = insNode($1, "ExtDef", @1.first_line, NON_TERMINAL);
        $1->bro = $2;

        flgStruct = 0;
    }
    | Specifier FunDec CompSt {
        $$ = insNode($1, "ExtDef", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        MyType tmp = MyType_default;
        // tmp.name = (char*)malloc(sizeof($2->child->id));
        strcpy(tmp.name, $2->child->id);
        tmp.isfunc = 1;
        // tmp.return_type = (char*)malloc(sizeof($1->child->id));
        strcpy(tmp.return_type, $1->child->id);
        if(strcmp(Compst_return_type, "null")) {
            if(strcmp(tmp.return_type, Compst_return_type)) {
            // if(tmp.return_type != Compst_return_type) {
                errors++;
                printf("Error %d at line %d : Type mismatched for return\n", TYPE_MISMATCH_RETURN, last_row);
                // char msg[100];
                // sprintf(msg, "Error %d at line %d : Type mismatched for return", TYPE_MISMATCH_RETURN, last_row);
                // myerror(msg);
            }
        }

        if(search(this_scope, tmp)) {
            errors++;
            printf("Error %d at line %d : Redefined function \'%s\'\n", REDEFINED_FUNCTION, last_row, tmp.name);
            // char msg[100];
            // sprintf(msg, "Error %d at line %d : Redefined function \'%s\'", REDEFINED_FUNCTION, last_row, tmp.name);
            // myerror(msg);
        }
		else {
            tmp.isfunc = 1;
            tmp.def = 1;
            if($2->child->bro->bro->bro) { // 说明 FunDec -> ID LP VarList RP
                struct node* n = $2->child->bro->bro; // n始终指向VarList
                char varifunc[12] = {"00_varifunc"};
                do {
                    MyType t = MyType_default;
                    t.def = 1;
                    t.isvariable = 1;
                    strcpy(t.type, n->child->child->child->id);
                    strcpy(t.name, n->child->child->bro->child->id);
                    int result = my_insert(&tmp.varilist, t);

                    t = MyType_default;
                    strcpy(t.type, n->child->child->child->id);
                    strcpy(t.name, varifunc);
                    varifunc[1] += 1;
                    if(varifunc[1] > '9'){
                        varifunc[0] += 1;
                        varifunc[1] = 0;
                    }
                    result = my_insert(&tmp.varilist, t);

                    if(n->child->bro) {
                        n = n->child->bro->bro;
                    }
                    else break;
                } while(n);
                
            }
            else {
                // printf("没啥\n");
            }
            // my_print(&tmp.varilist);
            this_scope = insert(this_scope, tmp);
            my_insert(&this_scope->last->my_root, tmp);
        }
		// jcy 8	
        
        this_scope = pop_scope(this_scope);
    }
    | Specifier FunDec SEMI {
        $$ = insNode($1, "ExtDef", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;


    }
    ;

ExtDecList : VarDec {
        $$ = insNode($1, "ExtDecList", @1.first_line, NON_TERMINAL);
    }
    | VarDec COMMA ExtDecList {
        $$ = insNode($1, "ExtDecList", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
    }
	// | VarDec error ExtDecList {
	// 	char msg[100];
	// 	sprintf(msg, "text.");
	// 	myerror(msg);
	// }
    ;

Specifier : TYPE {
        $$ = insNode($1, "Specifier", @1.first_line, NON_TERMINAL);
    }
    | StructSpecifier {
        $$ = insNode($1, "Specifier", @1.first_line, NON_TERMINAL);
    }
    
    ;

// StructSpecifier : STRUCT OptTag LC Stmt RC {
StructSpecifier : STRUCT OptTag LC Mid RC {
// StructSpecifier : STRUCT OptTag LC DefList RC {
        $$ = insNode($1, "StructSpecifier", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        $3->bro = $4;
        $4->bro = $5;

        MyType tmp = MyType_default;
        // free(tmp.type); // 没有这行，tmp.type会很奇怪地一开始就是"Mid"
        // tmp.name = (char*)malloc(sizeof($2->child->id));
        
        strcpy(tmp.name, $2->child->id);
        // tmp.type = (char*)malloc(sizeof($1->id));
        strcpy(tmp.type, $1->id);
        // printf("%s is named %s\n", tmp.type, tmp.name);
        if(search(this_scope, tmp)) { // 结构体名字重复
            errors++;
            printf("Error %d at line %d : Duplicate name \'%s\'\n", REDEFINED_STRUCT, last_row, tmp.name);
            // char msg[100];
            // sprintf(msg, "Error %d at line %d : Duplicate name \'%s\'", REDEFINED_STRUCT, last_row, tmp.name);
            // myerror(msg);
        }
        else {
            tmp.def = 1;
            tmp.isstruct = 1;
            // printf("%s\n", tmp.name);
            struct node* newnode = $4; // newnode保持指向Mid
            
            // char* mid = "Mid";
            // tmp.varilist = (struct rb_root*)malloc(sizeof(struct rb_root*));
            do {
                MyType temp = MyType_default;
                temp.def = 1;
                temp.isvariable = 1;

                // temp.type = (char*)malloc(sizeof(newnode->child->child->child->id));
                strcpy(temp.type, newnode->child->child->child->id);

                struct node* newnew = newnode->child->child->bro; // newnew保持指向DecList
                do {
                    // temp.name = (char*)malloc(sizeof(newnew->child->child->child->id));
                    strcpy(temp.name, newnew->child->child->child->id);
                    // printf("Struct \'%s\' has variable \'%s\' of type \'%s\'\n", tmp.name, temp.name, temp.type);

                    // tmp.varilist = (struct rb_root*)malloc(sizeof(struct rb_root*));
                    int result = my_insert(&tmp.varilist, temp);
                    // printf("Whether successful: %d\n", result);

                    if(newnew->child->bro != NULL) {
                        newnew = newnew->child->bro->bro;
                    }
                    else break;
                } while(newnew != NULL);
                // free(temp.type);

                // printf("newnode->child->bro: %s\n", newnode->child->bro->name);
                if(newnode->child) { // strcmp(newnode->child->bro->name, "Mid") == 0
                    newnode = newnode->child->bro;
                }
                else break;
            } while(newnode->child);
            // tmp.isarr = 0;
            // tmp.dimension = 0;

            this_scope = insert(this_scope, tmp); // 插入当前作用域
            // printf("struct name %s of type %s, %d\n", tmp.name, tmp.type, tmp.isarr);
            int result = my_insert(&this_scope->last->my_root, tmp); // 插入上一级作用域
            // 这里是为了pop结构体的子作用域时不会扔掉结构体这个结点
            // print(this_scope);
            // printf("\n");

            tmp.def = 0;
            tmp.isstruct = 0;
            // flgStruct = 1;
        }
        // free(tmp.name);
        // free(tmp.type);
        // free(tmp.varilist);

        this_scope = pop_scope(this_scope);
    }
    | STRUCT Tag {
        $$ = insNode($1, "StructSpecifier", @1.first_line, NON_TERMINAL);
        $1->bro = $2;

        MyType tmp = MyType_default;
        // tmp.name = (char*)malloc(sizeof($2->child->id));
        strcpy(tmp.name, $2->child->id);
        // printf("Scope: %d\n", this_scope->top);
        if(!search(this_scope, tmp)) {
            errors++;
            printf("Error %d at line %d : Undefined struct \'%s\'\n", UNDEFINED_STRUCT, last_row, tmp.name);
            // char msg[100];
            // sprintf(msg, "Error %d at line %d : Undefined struct \'%s\'", UNDEFINED_STRUCT, last_row, tmp.name);
            // myerror(msg);
        }
        else {
            // printf("insert struct \'%s\'\n", tmp.name);
            tmp.def = 1;
            tmp.isstruct = 1;
            // tmp.type = (char*)malloc(sizeof($2->child->id));
            strcpy(tmp.type, $2->child->id);
            // this_scope = insert(this_scope, tmp);
            
            tmp.def = 0;
            tmp.isstruct = 0;
            // flgStruct = 1;
        }
        // printf("struct type: %s\n", tmp.type);
        // free(tmp.name);
        // free(tmp.type);
        flgStruct = 2;
    }
    ;

OptTag : ID {
        $$ = insNode($1, "OptTag", @1.first_line, NON_TERMINAL);
    }
    | {
        $$ = insNode(NULL, "OptTag", yylineno, NON_TERMINAL);
    }
    ;

Tag : ID {
        $$ = insNode($1, "Tag", @1.first_line, NON_TERMINAL);
    }
    ;

FunDec : ID LP VarList RP {
        $$ = insNode($1, "FunDec", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        $3->bro = $4;

        // MyType tmp = MyType_default;
        // // tmp.name = (char*)malloc(sizeof($1->id));
        // strcpy(tmp.name, $1->id);
        // if(search(this_scope, tmp)) { // 函数重定义
        //     char msg[100];
        //     sprintf(msg, "Error %d at line %d : Redefined function \'%s\'", REDEFINED_FUNCTION, last_row, tmp.name);
        //     myerror(msg);
        // }
        // else {
            // printf("insert function \'%s\'\n", tmp.name);
        //     tmp.def = 1;
        //     tmp.isfunc = 1;
        //     struct node *newnode = $3;
        //     do { // 函数的参数列表
        //     MyType temp = MyType_default;
        //         temp.def = 1;
        //         temp.isvariable = 1;

        //         strcpy(temp.type, newnode->child->child->child->id);
        //         strcpy(temp.name, newnode->child->child->bro->child->id);

        //         int result = my_insert(&tmp.varilist, temp);

        //         if(newnode->child->bro != NULL) {
        //             newnode = newnode->child->bro->bro;
        //         }
        //         else break;
        //     } while(newnode != NULL);

            // this_scope = insert(this_scope, tmp);
        // }
    }
    | ID LP RP {
        $$ = insNode($1, "FunDec", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        
        // strcpy(tmp.name, $1->id);
        // if(search(this_scope, tmp)) { // 函数重定义
        
        //     char msg[100];
        //     sprin zxxxdxxxxxxxxxxx        tf(msg, "Error %d at line %d : Redefined function \'%s\'", REDEFINED_FUNCTION, last_row, tmp.name);
        //     myerror(msg);
        // }
        // else {
        
        //     tmp.def = 1;
        //     tmp.isfunc = 1;
        //     this_scope = insert(this_scope, tmp);

        //     tmp.def = 0;
        //     tmp.isfunc = 0;
        // }
    }
	| ID LP error RP {
		char msg[100];
		sprintf(msg, "VarList.");
		myerror(msg);
	}
    ;

VarList : ParamDec COMMA VarList {
        $$ = insNode($1, "VarList", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
    }
    | ParamDec {
        $$ = insNode($1, "VarList", @1.first_line, NON_TERMINAL);
    }
    ;

ParamDec : Specifier VarDec {
        $$ = insNode($1, "ParamDec", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
    }
    ;

// CompSt : LC DefList StmtList RC {
// //CompSt : LC StmtList RC {
//         $$ = insNode($1, "CompSt", @1.first_line, NON_TERMINAL);
//         $1->bro = $2;
//         $2->bro = $3;
//         $3->bro = $4;
//     }
//     ;


//CompSt : LC Stmt RC {
CompSt : LC Mid RC {
        $$ = insNode($1, "CompSt", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
    }
    ;
    
    
Mid : Def Mid {
        $$ = insNode($1, "Mid", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
	}
	| Stmt Mid {
        $$ = insNode($1, "Mid", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
	}
	| {
        $$ = insNode(NULL, "Mid", yylineno, NON_TERMINAL);
	}
	;

// StmtList : Stmt StmtList {
//         $$ = insNode($1, "StmtList", @1.first_line, NON_TERMINAL);
//         $1->bro = $2;
//     }/*
//     | DefList StmtList {
    
//     }
//     | StmtList DefList {
    
//     }*/
//     | {
//         $$ = insNode(NULL, "FunDec", yylineno, NON_TERMINAL);
//     }
//     ;

Def : Specifier DecList SEMI {
        $$ = insNode($1, "Def", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        struct node* newnode = $2; // newnode始终指向DecList
            
        do {
            MyType tmp = MyType_default;
            tmp.def = 1;
            // printf("flgArr = %d\n", flgArr);
            if(!flgArr) { // 不是数组
                // tmp.name = (char*)malloc(sizeof(newnode->child->child->child->id));
                strcpy(tmp.name, newnode->child->child->child->id);
            }
            else { // 是数组
                // tmp.name = (char*)malloc(sizeof(newnode->child->child->child->child->id));
                // printf("array name: %s\n", newnode->child->child->child->child->id);
                strcpy(tmp.name, newnode->child->child->child->child->id);
            }

            if(my_search(&this_scope->my_root, tmp)) { // 两种可能：struct xx {...} yy; 或 int a;
                char msg[100];
                if(!flgStruct)  {// 普通变量声明
                    errors++;
                    printf("Error %d at line %d : Redefined variable \'%s\'\n", REDEFINED_VARIABLE, last_row, tmp.name);
                    // sprintf(msg, "Error %d at line %d : Redefined variable \'%s\'", REDEFINED_VARIABLE, last_row, tmp.name);
                }
                else {// 结构体变量声明
                    errors++;
                    printf("Error %d at line %d : Redefined field \'%s\'\n", REDEFINED_FIELD, last_row, tmp.name);
                    // sprintf(msg, "Error %d at line %d : Redefined field \'%s\'", REDEFINED_FIELD, last_row, tmp.name);
                }
                // myerror(msg);
            }
            else {
                if(flgStruct == 2) { // 是struct tag的情况，如struct sa nn;
                    // tmp.type = (char*)malloc(sizeof($1->child->child->bro->child->id));
                    strcpy(tmp.type, $1->child->child->bro->child->id);
                    tmp.isstruct = 1;
                    flgStruct = 0;
                }
                // else if(flgStruct == 1) {

                // }
                else { // 一般变量，如int a，结构体内和一般声明均是;
                    // tmp.type = (char*)malloc(sizeof($1->child->id));
                    // printf("%s\n", $1->child->id);
                    
                    strcpy(tmp.type, $1->child->id);
                    if(flgArr) { // 是数组
                        tmp.isarr = 1;
                        tmp.dimension = newnode->child->child->child->bro->bro->intValue;
                        // flgArr = 0;
                    }
                    if(newnode->child->child->bro) {
                        if(!strcmp(newnode->child->child->bro->bro->child->name, "ID")) {
                            MyType t1 = MyType_default;
                            strcpy(t1.name, newnode->child->child->bro->bro->child->id);
                            MyType* t2 = search(this_scope, t1);
                            if(strcmp(t2->type, $1->child->id)) {
                                errors++;
                                printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                                // char msg[100];
                                // sprintf(msg, "Error %d at line %d : Type mismatched for assignment", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                                // myerror(msg);
                            }
                        }
                        else if(!strcmp(newnode->child->child->bro->bro->child->name, "INT")) {
                            if(strcmp("int", $1->child->id)) {
                                errors++;
                                printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                                // char msg[100];
                                // sprintf(msg, "Error %d at line %d : Type mismatched for assignment", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                                // myerror(msg);
                            }
                        }
                        else if(!strcmp(newnode->child->child->bro->bro->child->name, "FLOAT")) {
                            if(strcmp("float", $1->child->id)) {
                                errors++;
                                printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                                // char msg[100];
                                // sprintf(msg, "Error %d at line %d : Type mismatched for assignment", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                                // myerror(msg);
                            }
                        }
                    }
                }
            }
            
            // printf("Variable %s has type %s\n", tmp.name, tmp.type);
            tmp.isvariable = 1;
            this_scope = insert(this_scope, tmp);

            // free(tmp.type);
            // free(tmp.name);
                
            if(newnode->child->bro) // 不这么写感觉没办法写循环
                newnode = newnode->child->bro->bro; // 让newnode始终指向DecList
            else break; // 可能为NULL，提前终止，避免报错
        } while(newnode);
        
        // print(this_scope);

        // flgStruct = 0;
        flgArr = 0;        
    }
	| Specifier DecList error{
		char msg[100];
		sprintf(msg, "error: Missing \";\"");	//necessary
		myerror(msg);
	}
    | error DecList SEMI {
    	char msg[100];
		sprintf(msg, "Syntax error.");
		myerror(msg);
    }
	| Specifier error SEMI {
		char msg[100];
		sprintf(msg, "Syntax error.");
		myerror(msg);
	}
	;

    
Stmt : 
    Exp SEMI {
        $$ = insNode($1, "Stmt", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
    }
    | Exp error {
		char msg[100];
		sprintf(msg, "error: Missing \";\"");
		myerror(msg);
	}
    | CompSt {
        $$ = insNode($1, "Stmt", @1.first_line, NON_TERMINAL);
    }
    | RETURN Exp SEMI {
        $$ = insNode($1, "Stmt", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        if(!strcmp($2->child->name, "int")) { // $2->child->type == INT_TYPE
            strcpy(Compst_return_type, "int");
        }
        else if(!strcmp($2->child->name, "float")) { // $2->child->type == FLOAT_TYPE
            strcpy(Compst_return_type, "float");
        }
        else if($2->child->type == STRING_TYPE) {
            strcpy(Compst_return_type, $2->child->name);
        }

        // Compst_return_type = (char*)malloc(sizeof($2->name));
        // printf("return type name: %s\n", $2->child->name);
        // strcpy(Compst_return_type, $2->child->name);
    }
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {
        $$ = insNode($1, "Stmt", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        $3->bro = $4;
        $4->bro = $5;
    }
    | IF LP Exp RP Stmt ELSE Stmt {
        $$ = insNode($1, "Stmt", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        $3->bro = $4;
        $4->bro = $5;
        $5->bro = $6;
        $6->bro = $7;
    }
    | WHILE LP Exp RP Stmt {
        $$ = insNode($1, "Stmt", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        $3->bro = $4;
        $4->bro = $5;
    }
    ;

// DefList : Def DefList {
//         $$ = insNode($1, "DefList", @1.first_line, NON_TERMINAL);
//         $1->bro = $2;
//     }
//     | {
//         $$ = insNode(NULL, "DefList", yylineno, NON_TERMINAL);
//     }
//     ;

DecList : Dec {
        $$ = insNode($1, "DecList", @1.first_line, NON_TERMINAL);
    }
    | Dec COMMA DecList {
        $$ = insNode($1, "DecList", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
    }
	;

Dec : VarDec {
        $$ = insNode($1, "Dec", @1.first_line, NON_TERMINAL);
    }
    | VarDec ASSIGNOP Exp {
        $$ = insNode($1, "Dec", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
    }
    ;

VarDec : ID {
        $$ = insNode($1, "VarDec", @1.first_line, NON_TERMINAL);
    }
    | VarDec LB INT RB {
        $$ = insNode($1, "VarDec", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        $3->bro = $4;
    }
    | VarDec LB ID RB {
        $$ = insNode($1, "VarDec", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        $3->bro = $4;
    }
    | VarDec LB ID error {
        char msg[100];
        sprintf(msg, "Missing \"]\".");
		myerror(msg);
    }
	| VarDec LB FLOAT RB{
		char msg[100];
		sprintf(msg, "int.");
		myerror(msg);
	}
    ;

Exp : Exp ASSIGNOP Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        // printf("exp: %s\n", $1->child->name);
        if($1->child->type != STRING_TYPE && $1->child->type != NON_TERMINAL) {
            errors++;
            printf("Error %d at line %d : The left-hand side of assignment must be a variable\n", NEED_VARIABLE, last_row); 
            // char msg[100];
        	// sprintf(msg, "Error %d at line %d : The left-hand side of assignment must be a variable", NEED_VARIABLE, last_row); 
			// myerror(msg);
        }
        else if($1->child->type == NON_TERMINAL) { // 说明可能是数组
            MyType t1 = MyType_default;
            strcpy(t1.name, $1->child->child->id);
            MyType *t2 = search(this_scope, t1);

            // printf("%s\n", $3->child->name);
            if(!strcmp($3->child->name, "ID")) { // $3->child->type == STRING_TYPE
                MyType t3 = MyType_default;
                // printf("%s\n", $3->child->child->id);
                strcpy(t3.name, $3->child->child->id);
                MyType* t4 = search(this_scope, t3);
                if(strcmp(t2->type, t4->type)) {
                    errors++;
                    printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    // char msg[100];
                    // sprintf(msg, "Error %d at line %d : Type mismatched for assignment", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    // myerror(msg);
                }
            }
            else if(!strcmp($3->child->name, "FLOAT")) {
                if(strcmp(t2->type, "float")) {
                    errors++;
                    printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    // char msg[100];
                    // sprintf(msg, "Error %d at line %d : Type mismatched for assignment", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    // myerror(msg);
                }
            }
            else if(!strcmp($3->child->name, "INT")) {
                if(strcmp(t2->type, "int")) {
                    errors++;
                    printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    // char msg[100];
                    // sprintf(msg, "Error %d at line %d : Type mismatched for assignment", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    // myerror(msg);
                }
            }
        }
        else {
            MyType t1 = MyType_default;
            strcpy(t1.name, $1->child->id);
            MyType *t2 = search(this_scope, t1);

            // printf("%s\n", $3->child->id);
            if(!strcmp($3->child->name, "ID")) { // $3->child->type == STRING_TYPE
                MyType t3 = MyType_default;
                // printf("%s\n", $3->child->child->id);
                strcpy(t3.name, $3->child->id);
                MyType* t4 = search(this_scope, t3);
                if(strcmp(t2->type, t4->type)) {
                    errors++;
                    printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    // char msg[100];
                    // sprintf(msg, "Error %d at line %d : Type mismatched for assignment", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    // myerror(msg);
                }
            }
            else if(!strcmp($3->child->name, "FLOAT")) {
                if(strcmp(t2->type, "float")) {
                    errors++;
                    printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    // char msg[100];
                    // sprintf(msg, "Error %d at line %d : Type mismatched for assignment", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    // myerror(msg);
                }
            }
            else if(!strcmp($3->child->name, "INT")) {
                if(strcmp(t2->type, "int")) {
                    errors++;
                    printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    // char msg[100];
                    // sprintf(msg, "Error %d at line %d : Type mismatched for assignment", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    // myerror(msg);
                }
            }
        }
        
        // if($1->isAssignable == 0) {
        //    	char msg[100];
        // 	sprintf(msg, "Error %d at line %d : The left-hand side of assignment must be a variable", NEED_VARIABLE, last_row); 
		// 	myerror(msg);
        // }
        // // \end{jcy 6}
    }
	| Exp ASSIGNOP error { 
		char msg[100];
        sprintf(msg, "Syntax error."); // ASSIGNOP not in front of Exp
        // fprintf(stderr, "Error type B at line %d: %s\n", yylineno, msg);
		// errors++;
		myerror(msg);
	}
    | Exp AND Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        
        if(strcmp($1->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp($1->child->name, "INT")) {
                sprintf(num1, "%d", $1->child->intValue);
            }
            else if(!strcmp($1->child->name, "FLOAT")) {
                sprintf(num1, "%f", $1->child->floatValue);
            }
            
            strcpy(t1.name, num1);
            t2 = search(this_scope, t1);
        }
        else {
            strcpy(t1.name, $1->child->id);
            t2 = search(this_scope, t1);
        }
        
        char num2[20] = {0};
        MyType t3 = MyType_default;
        MyType* t4;
        if(strcmp($3->child->name, "ID")) {
            if(!strcmp($3->child->name, "INT")) {
                sprintf(num2, "%d", $3->child->intValue);
            }
            else if(!strcmp($3->child->name, "FLOAT")) {
                sprintf(num2, "%f", $3->child->floatValue);
            }
            
            strcpy(t3.name, num2);
            t4 = search(this_scope, t3);
        }
        else {
            strcpy(t3.name, $3->child->id);
            t4 = search(this_scope, t3);
        }
        // print_mynode(*t2);
        // print_mynode(*t4);
        if(strcmp(t2->type, t4->type)) {
            errors++;
            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
            // char msg[100];
            // sprintf(msg, "Error %d at line %d : Type mismatched for operands", TYPE_MISMATCH_OPERAND, last_row);
            // myerror(msg);
        }

        // $$->isAssignable = 0;
        // // printf("%s\n%s\n", $1->name, $3->name);
        // // if(!strcmp($1->child->name, $3->child->name)) $$->name = $1->name;
        // if(strcmp($1->name, $3->name)) {
        // 	char msg[100];
        //     sprintf(msg, "Error %d at line %d : Type mismatched for operands", TYPE_MISMATCH_OPERAND, last_row);
        //     myerror(msg);
        // }
    }
    | Exp OR Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        
        if(strcmp($1->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp($1->child->name, "INT")) {
                sprintf(num1, "%d", $1->child->intValue);
            }
            else if(!strcmp($1->child->name, "FLOAT")) {
                sprintf(num1, "%f", $1->child->floatValue);
            }
            
            strcpy(t1.name, num1);
            t2 = search(this_scope, t1);
        }
        else {
            strcpy(t1.name, $1->child->id);
            t2 = search(this_scope, t1);
        }
        
        char num2[20] = {0};
        MyType t3 = MyType_default;
        MyType* t4;
        if(strcmp($3->child->name, "ID")) {
            if(!strcmp($3->child->name, "INT")) {
                sprintf(num2, "%d", $3->child->intValue);
            }
            else if(!strcmp($3->child->name, "FLOAT")) {
                sprintf(num2, "%f", $3->child->floatValue);
            }
            
            strcpy(t3.name, num2);
            t4 = search(this_scope, t3);
        }
        else {
            strcpy(t3.name, $3->child->id);
            t4 = search(this_scope, t3);
        }
        // print_mynode(*t2);
        // print_mynode(*t4);
        if(strcmp(t2->type, t4->type)) {
            errors++;
            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
            // char msg[100];
            // sprintf(msg, "Error %d at line %d : Type mismatched for operands", TYPE_MISMATCH_OPERAND, last_row);
            // myerror(msg);
        }

        // $$->isAssignable = 0;
        // // if($1->name == $3->name) $$->name = $1->name;
        // if(strcmp($1->name, $3->name)) {
        // 	char msg[100];
        //     sprintf(msg, "Error %d at line %d : Type mismatched for operands", TYPE_MISMATCH_OPERAND, last_row);
        //     myerror(msg);
        // }
    }
    | Exp RELOP Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        
        if(strcmp($1->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp($1->child->name, "INT")) {
                sprintf(num1, "%d", $1->child->intValue);
            }
            else if(!strcmp($1->child->name, "FLOAT")) {
                sprintf(num1, "%f", $1->child->floatValue);
            }
            
            strcpy(t1.name, num1);
            t2 = search(this_scope, t1);
        }
        else {
            strcpy(t1.name, $1->child->id);
            t2 = search(this_scope, t1);
        }
        
        char num2[20] = {0};
        MyType t3 = MyType_default;
        MyType* t4;
        if(strcmp($3->child->name, "ID")) {
            if(!strcmp($3->child->name, "INT")) {
                sprintf(num2, "%d", $3->child->intValue);
            }
            else if(!strcmp($3->child->name, "FLOAT")) {
                sprintf(num2, "%f", $3->child->floatValue);
            }
            
            strcpy(t3.name, num2);
            t4 = search(this_scope, t3);
        }
        else {
            strcpy(t3.name, $3->child->id);
            t4 = search(this_scope, t3);
        }
        // print_mynode(*t2);
        // print_mynode(*t4);
        if(strcmp(t2->type, t4->type)) {
            errors++;
            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
            // char msg[100];
            // sprintf(msg, "Error %d at line %d : Type mismatched for operands", TYPE_MISMATCH_OPERAND, last_row);
            // myerror(msg);
        }

        // $$->isAssignable = 0;
        // // if($1->name == $3->name) $$->name = $1->name;
        // if(strcmp($1->name, $3->name)) {
        // 	char msg[100];
        //     sprintf(msg, "Error %d at line %d : Type mismatched for operands", TYPE_MISMATCH_OPERAND, last_row);
        //     myerror(msg);
        // }
    }
    | Exp PLUS Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        
        if(strcmp($1->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp($1->child->name, "INT")) {
                sprintf(num1, "%d", $1->child->intValue);
            }
            else if(!strcmp($1->child->name, "FLOAT")) {
                sprintf(num1, "%f", $1->child->floatValue);
            }
            
            strcpy(t1.name, num1);
            t2 = search(this_scope, t1);
        }
        else {
            strcpy(t1.name, $1->child->id);
            t2 = search(this_scope, t1);
        }
        
        char num2[20] = {0};
        MyType t3 = MyType_default;
        MyType* t4;
        if(strcmp($3->child->name, "ID")) {
            if(!strcmp($3->child->name, "INT")) {
                sprintf(num2, "%d", $3->child->intValue);
            }
            else if(!strcmp($3->child->name, "FLOAT")) {
                sprintf(num2, "%f", $3->child->floatValue);
            }
            
            strcpy(t3.name, num2);
            t4 = search(this_scope, t3);
        }
        else {
            strcpy(t3.name, $3->child->id);
            t4 = search(this_scope, t3);
        }
        // print_mynode(*t2);
        // print_mynode(*t4);
        if(strcmp(t2->type, t4->type)) {
            errors++;
            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
            // char msg[100];
            // sprintf(msg, "Error %d at line %d : Type mismatched for operands", TYPE_MISMATCH_OPERAND, last_row);
            // myerror(msg);
        }

        // $$->isAssignable = 0;
        // // printf("%s\n%s\n", $1->name, $3->name);
        // // if(!strcmp($1->name, $3->name)) $$->name = $1->name;
        // if(strcmp($1->name, $3->name)) {
        // 	char msg[100];
        //     sprintf(msg, "Error %d at line %d : Type mismatched for operands", TYPE_MISMATCH_OPERAND, last_row);
        //     myerror(msg);
        // }
    }
    | Exp MINUS Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        
        if(strcmp($1->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp($1->child->name, "INT")) {
                sprintf(num1, "%d", $1->child->intValue);
            }
            else if(!strcmp($1->child->name, "FLOAT")) {
                sprintf(num1, "%f", $1->child->floatValue);
            }
            
            strcpy(t1.name, num1);
            t2 = search(this_scope, t1);
        }
        else {
            strcpy(t1.name, $1->child->id);
            t2 = search(this_scope, t1);
        }
        
        char num2[20] = {0};
        MyType t3 = MyType_default;
        MyType* t4;
        if(strcmp($3->child->name, "ID")) {
            if(!strcmp($3->child->name, "INT")) {
                sprintf(num2, "%d", $3->child->intValue);
            }
            else if(!strcmp($3->child->name, "FLOAT")) {
                sprintf(num2, "%f", $3->child->floatValue);
            }
            
            strcpy(t3.name, num2);
            t4 = search(this_scope, t3);
        }
        else {
            strcpy(t3.name, $3->child->id);
            t4 = search(this_scope, t3);
        }
        // print_mynode(*t2);
        // print_mynode(*t4);
        if(strcmp(t2->type, t4->type)) {
            errors++;
            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
            // char msg[100];
            // sprintf(msg, "Error %d at line %d : Type mismatched for operands", TYPE_MISMATCH_OPERAND, last_row);
            // myerror(msg);
        }

        // $$->isAssignable = 0;
        // // if(!strcmp($1->name, $3->name)) $$->name = $1->name;
        // if(strcmp($1->name, $3->name)) {
        // 	char msg[100];
        //     sprintf(msg, "Error %d at line %d : Type mismatched for operands", TYPE_MISMATCH_OPERAND, last_row);
        //     myerror(msg);
        // }
    }
    | Exp STAR Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        
        if(strcmp($1->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp($1->child->name, "INT")) {
                sprintf(num1, "%d", $1->child->intValue);
            }
            else if(!strcmp($1->child->name, "FLOAT")) {
                sprintf(num1, "%f", $1->child->floatValue);
            }
            
            strcpy(t1.name, num1);
            t2 = search(this_scope, t1);
        }
        else {
            strcpy(t1.name, $1->child->id);
            t2 = search(this_scope, t1);
        }
        
        char num2[20] = {0};
        MyType t3 = MyType_default;
        MyType* t4;
        if(strcmp($3->child->name, "ID")) {
            if(!strcmp($3->child->name, "INT")) {
                sprintf(num2, "%d", $3->child->intValue);
            }
            else if(!strcmp($3->child->name, "FLOAT")) {
                sprintf(num2, "%f", $3->child->floatValue);
            }
            
            strcpy(t3.name, num2);
            t4 = search(this_scope, t3);
        }
        else {
            strcpy(t3.name, $3->child->id);
            t4 = search(this_scope, t3);
        }
        // print_mynode(*t2);
        // print_mynode(*t4);
        if(strcmp(t2->type, t4->type)) {
            errors++;
            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
            // char msg[100];
            // sprintf(msg, "Error %d at line %d : Type mismatched for operands", TYPE_MISMATCH_OPERAND, last_row);
            // myerror(msg);
        }

        // $$->isAssignable = 0;
        // // if(!strcmp($1->name, $3->name)) $$->name = $1->name;
        // if(strcmp($1->name, $3->name)) {
        // 	char msg[100];
        //     sprintf(msg, "Error %d at line %d : Type mismatched for operands", TYPE_MISMATCH_OPERAND, last_row);
        //     myerror(msg);
        // }
    }
    | Exp DIV Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        
        if(strcmp($1->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp($1->child->name, "INT")) {
                sprintf(num1, "%d", $1->child->intValue);
            }
            else if(!strcmp($1->child->name, "FLOAT")) {
                sprintf(num1, "%f", $1->child->floatValue);
            }
            
            strcpy(t1.name, num1);
            t2 = search(this_scope, t1);
        }
        else {
            strcpy(t1.name, $1->child->id);
            t2 = search(this_scope, t1);
        }
        
        char num2[20] = {0};
        MyType t3 = MyType_default;
        MyType* t4;
        if(strcmp($3->child->name, "ID")) {
            if(!strcmp($3->child->name, "INT")) {
                sprintf(num2, "%d", $3->child->intValue);
            }
            else if(!strcmp($3->child->name, "FLOAT")) {
                sprintf(num2, "%f", $3->child->floatValue);
            }
            
            strcpy(t3.name, num2);
            t4 = search(this_scope, t3);
        }
        else {
            strcpy(t3.name, $3->child->id);
            t4 = search(this_scope, t3);
        }
        // print_mynode(*t2);
        // print_mynode(*t4);
        if(strcmp(t2->type, t4->type)) {
            errors++;
            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
            // char msg[100];
            // sprintf(msg, "Error %d at line %d : Type mismatched for operands", TYPE_MISMATCH_OPERAND, last_row);
            // myerror(msg);
        }

        // $$->isAssignable = 0;
        // // if(!strcmp($1->name, $3->name)) $$->name = $1->name;
        // if(strcmp($1->name, $3->name)) {
        // 	char msg[100];
        //     sprintf(msg, "Error %d at line %d : Type mismatched for operands", TYPE_MISMATCH_OPERAND, last_row);
        //     myerror(msg);
        // }
    }
    | LP Exp RP {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        // $$->name = $2->name;
        $$->isAssignable = $2->isAssignable;
    }
    | MINUS Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;

        // $$->name = $2->name;
        $$->isAssignable = 0;
    }
    | NOT Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;

        // $$->name = $2->name;
        $$->isAssignable = 0;
    }
    | ID LP Args RP {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        $3->bro = $4;

        MyType tmp = MyType_default;
        // tmp.name = (char*)malloc(sizeof($1->id));
        strcpy(tmp.name, $1->id);
        $$->isAssignable = 0;
        MyType* mt = search(this_scope, tmp);
        if(mt != NULL) { 
            // tmp.def = 1;
            
            if(mt->isfunc) {
                // this_scope = insert(this_scope, tmp);
                // dxr to do
                struct node* newnode = $3;
                // printf("%s\n", newnode->child->child->id);
                char varifunc[12] = {"00_varifunc"};
                char Parameter[10][10];
                char Arguments[10][10];
                int right = 1, vari_num = 0, para_num = 0;
                MyType parameter = MyType_default; // 形参
                do { // 函数的参数列表 实参

                    
                    strcpy(parameter.name, varifunc);
                    // printf("%s\n", parameter.name);
                    struct my_node* ttp = my_search(&(mt->varilist), parameter);
                    // print_mynode(ttp->info);
                    // my_print(&(mt->varilist));
                    if(ttp != NULL) {
                        parameter = ttp->info;
                        // printf("%s : %s\n", mt->name, parameter.type);
                    }  // 后面做了
                    
                    if(strcmp(newnode->child->child->name, "ID")){  // 不是变量
                        // printf("%s\n", newnode->child->child->name);
                        char argu[20];
                        // printf("%d\n", newnode->child->child->type);
                        if(strcmp(newnode->child->child->name, "INT") == 0){
                            strcpy(argu, "int");
                        }
                        else if(strcmp(newnode->child->child->name, "FLOAT") == 0){
                            strcpy(argu, "float");
                        }
                        else {
                            printf("你说你妈呢\n");
                            exit(0);
                        }
                        // printf("%s\n", argu);
                        // Arguments[vari_num] = (char*)malloc(sizeof(argu));
                        strcpy(Arguments[vari_num++], argu);
                        if(ttp == NULL || strcmp(parameter.type, argu)){
                            right = 0;
                            // printf("%s %s %s\n", mt->name, parameter.type, argu);
                        }
                        if(ttp != NULL){
                            // Parameter[para_num] = (char*)malloc(sizeof(parameter.type));
                            strcpy(Parameter[para_num++], parameter.type);
                        }
                    }
                    else{
                        MyType argu = MyType_default;
                        strcpy(argu.name, newnode->child->child->id);
                        Mylink tttp = search(this_scope, argu); // 据卢爹说一定能搜到，在此就直接拿了用
                        assert(tttp != NULL);
                        argu = *tttp;
                        // print_mynode(argu);
                        // Arguments[vari_num] = (char*)malloc(sizeof(argu.type));
                        strcpy(Arguments[vari_num++], argu.type);
                        if(ttp==NULL || strcmp(parameter.type, argu.type)){
                            right = 0;
                        }
                        if(ttp != NULL){
                            // Parameter[para_num] = (char*)malloc(sizeof(parameter.type));
                            strcpy(Parameter[para_num++], parameter.type);
                        }
                    }
                    // parameter.def = 0;
                    // parameter.isvariable = 1;
                    // printf("Variable type: %s\n", newnode->child->child->name);
                    // temp.type = (char*)malloc(sizeof(newnode->child->child->child->id));
                    // strcpy(temp.type, newnode->child->child->id);

                    // printf("Variable name: %s\n", newnode->child->bro->child->name);
                    // // temp.name = (char*)malloc(sizeof(newnode->child->child->bro->child->id));
                    // strcpy(temp.name, newnode->child->bro->child->id);
                    // printf("Variable %s is type %s\n", temp.name, temp.type);

                    // tmp.varilist = (struct rb_root*)malloc(sizeof(struct rb_root*));
                    // int result = my_insert(&tmp.varilist, temp);
                    // printf("Whether successful: %d\n", result);

                    // temp.def = 0;
                    // temp.isvariable = 0;
                    // free(temp.type);
                    // free(temp.name);
                    // temp = MyType_default;
                    // temp.isvariable = 1;
                    // strcpy(temp.type, newnode->child->child->child->id);
                    // strcpy(temp.name, varifunc);
                    varifunc[1] += 1;
                    if(varifunc[1] > '9'){
                        varifunc[0] += 1;
                        varifunc[1] = 0;
                    }
                    // result = my_insert(&tmp.varilist, temp);
                    if(newnode->child->bro != NULL) {
                        newnode = newnode->child->bro->bro;
                    }
                    else break;
                } while(newnode != NULL);
                strcpy(parameter.name, varifunc);
                struct my_node* tpp = my_search(&(mt->varilist), parameter);
                while(tpp){
                    parameter = tpp->info;
                    strcpy(Parameter[para_num++], parameter.type);
                    varifunc[1] += 1;
                    if(varifunc[1] > '9'){
                        varifunc[0] += 1;
                        varifunc[1] = 0;
                    }
                    strcpy(parameter.name, varifunc);
                    tpp = my_search(&(mt->varilist), parameter);
                    right = 0;
                }
                if(right == 0) {
                    // char msg[1000];
                    printf("Error %d at line %d : Function \'%s(", FUNCTION_MISMATCH, last_row, mt->name);
                    for(int i = 0; i < vari_num; i ++){
                        if(i != vari_num - 1)
                            printf("%s,", Arguments[i]);
                        else
                            printf("%s", Arguments[i]);
                    }
                    printf(")\' is not applicable for arguments \'%s(", mt->name);
                    for(int i = 0; i < para_num; i ++){
                        if(i != para_num - 1)
                            printf("%s,", Parameter[i]);
                        else
                            printf("%s", Parameter[i]);
                    }
                    printf(")\'");
                    printf("\n");
                    errors ++;
                }
            }
            else {
                //	\begin{jcy 11}
                errors++;
                printf("Error %d at line %d : \'%s\' is not a function\n", NOT_FUNCTION, last_row, tmp.name);
		        // char msg[100];
            	// sprintf(msg, "Error %d at line %d : \'%s\' is not a function", NOT_FUNCTION, last_row, tmp.name);
            	// myerror(msg);
                // 	\end{jcy 11}
            }
        }
        else { // 函数未定义
            errors++;
            printf("Error %d at line %d : Undefined function \'%s\'\n", UNDEFINED_FUNCTION, last_row, tmp.name);
            // char msg[100];
            // sprintf(msg, "Error %d at line %d : Undefined function \'%s\'", UNDEFINED_FUNCTION, last_row, tmp.name);
            // myerror(msg);
        }
    }
    | ID LP RP {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        MyType tmp = MyType_default;
        // tmp.name = (char*)malloc(sizeof($1->id));
        strcpy(tmp.name, $1->id);
        $$->isAssignable = 0;
        MyType* mt = search(this_scope, tmp);
        if(mt != NULL) { 
            // tmp.def = 1;
            if(mt->isfunc) {
                // tmp.type = $1->type;
                // my_insert(&mytree, tmp);
                // this_scope = insert(this_scope, tmp);
                char varifunc[12] = {"00_varifunc"};
                char Parameter[10][10];
                char Arguments[10][10];
                int right = 1, vari_num = 0, para_num = 0;
                MyType parameter = MyType_default; // 形参
                strcpy(parameter.name, varifunc);
                struct my_node* tpp = my_search(&(mt->varilist), parameter);
                while(tpp){
                    parameter = tpp->info;
                    strcpy(Parameter[para_num++], parameter.type);
                    varifunc[1] += 1;
                    if(varifunc[1] > '9'){
                        varifunc[0] += 1;
                        varifunc[1] = 0;
                    }
                    strcpy(parameter.name, varifunc);
                    tpp = my_search(&(mt->varilist), parameter);
                    right = 0;
                }
                if(right == 0) {
                    // char msg[1000];
                    printf("Error %d at line %d : Function \'%s(", FUNCTION_MISMATCH, last_row, mt->name);
                    for(int i = 0; i < vari_num; i ++){
                        if(i != vari_num - 1)
                            printf("%s,", Arguments[i]);
                        else
                            printf("%s", Arguments[i]);
                    }
                    printf(")\' is not applicable for arguments \'%s(", mt->name);
                    for(int i = 0; i < para_num; i ++){
                        if(i != para_num - 1)
                            printf("%s,", Parameter[i]);
                        else
                            printf("%s", Parameter[i]);
                    }
                    printf(")\'");
                    printf("\n");
                    errors ++;
                }
            }
            else {
                //	\begin{jcy 11}
                errors++;
                printf("Error %d at line %d : \'%s\' is not a function\n", NOT_FUNCTION, last_row, tmp.name);
		        // char msg[100];
            	// sprintf(msg, "Error %d at line %d : \'%s\' is not a function", NOT_FUNCTION, last_row, tmp.name);
            	// myerror(msg);
                // 	\end{jcy 11}
            }
        }
        else { // 函数未定义
            errors++;
            printf("Error %d at line %d : Undefined function \'%s\'\n", UNDEFINED_FUNCTION, last_row, tmp.name);
            // char msg[100];
            // sprintf(msg, "Error %d at line %d : Undefined function \'%s\'", UNDEFINED_FUNCTION, last_row, tmp.name);
            // myerror(msg);
        }
    }
    | Exp LB Exp RB {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        $3->bro = $4;
        // \begin{jcy 10}
        MyType tmp = MyType_default;
        if($1->child->type == STRING_TYPE) {			//主要是因为直接是数值的话，它没有RBT上的name
		    // tmp.name = (char*)malloc(sizeof($1->child->id));
            
		    strcpy(tmp.name, $1->child->id);
		    MyType* ml = search(this_scope, tmp);
            
		    if(search(this_scope, tmp)) {
		    	if(ml->isarr) {
		    		// \begin{jcy 12}
                    // printf("%s\n", $3->child->name);
		    		if(strcmp($3->child->name, "INT")) {
		    			// char msg[100];
                        if(!strcmp($3->child->name, "FLOAT")) {
                            errors++;
                            printf("Error %d at line %d : \'%f\' is not an integer\n", ARRAY_ACCESS_OPERATEOR_NOT_INTEGER, last_row, $3->child->floatValue);
                        }
		        		//     sprintf(msg, "Error %d at line %d : \'%f\' is not an integer", ARRAY_ACCESS_OPERATEOR_NOT_INTEGER, last_row, $3->child->floatValue);
		        		// myerror(msg);
		    		}
		    		// \end{jcy 12}
		    	}
		    	else {
                    errors++;
                    printf("Error %d at line %d : \'%s\' is not an array\n", NOT_ARRAY, last_row, tmp.name);
		    		// char msg[100];
		        	// sprintf(msg, "Error %d at line %d : \'%s\' is not an array", NOT_ARRAY, last_row, tmp.name);
		        	// myerror(msg);
		    	}
		    }
		    else {
                errors++;
                printf("Error %d at line %d : Undefined variable \'%s\'\n", UNDEFINED_VARIABLE, last_row, tmp.name);
		        // char msg[100];
		        // sprintf(msg, "Error %d at line %d : Undefined variable \'%s\'", UNDEFINED_VARIABLE, last_row, tmp.name);
		        // myerror(msg);
		    }
        
        }
        else {
            errors++;
            printf("Error %d at line %d : \'%s\' is not an array\n", NOT_ARRAY, last_row, tmp.name);
		    // char msg[100];
		    // sprintf(msg, "Error %d at line %d : \'%s\' is not an array", NOT_ARRAY, last_row, tmp.name);
	        // myerror(msg);        
		}
        //一个$1是否为数组变量的检查，一个$3是否为整数的检查（忽略段错误）
        // 类型传递
        // \end{jcy 10}
    }
	| Exp DOT ID { // 结构体
		$$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
		$1->bro = $2;
		$2->bro = $3;

        MyType tmp = MyType_default;
        if($1->child->type == STRING_TYPE) {
		    // tmp.name = (char*)malloc(sizeof($1->child->id));
		    strcpy(tmp.name, $1->child->id);
            MyType* ml = search(this_scope, tmp);
            // print(this_scope);
		    if(ml != NULL) { //先获取这个名字的东西，然后看看它是不是结构体：如果不是结构体，则判为错误13；若是结构体，开始看ID是否存在：如果ID存在，将其属性赋给规约后的结果；若ID不存在，则判为错误14
		        // Mylink ml = search(this_scope, tmp);
		        if(ml->isstruct) {
		        	// error 14 	to be continued...
                    MyType t1 = MyType_default;
                    strcpy(t1.name, ml->type);
                    MyType* t2 = search(this_scope, t1); // 找到该结构体类型的定义
                    // print(this_scope);

                    MyType t3 = MyType_default;
                    strcpy(t3.name, $3->id);

                    if(my_search(&t2->varilist, t3)) {
                        // printf("Yes!!\n");
                    }
                    else {
                        errors++;
                        printf("Error %d at line %d : Non-existing field \'%s\'\n", NOT_EXISTENT_FIELD, last_row, $3->id);
                        // char msg[100];
                        // sprintf(msg, "Error %d at line %d : Non-existing field \'%s\'", NOT_EXISTENT_FIELD, last_row, $3->id);
                        // myerror(msg);
                    }
		        	// this_scope = insert(this_scope, tmp); // 不能insert，只能查
		        }
		        // tmp.type = $1->type;
		        // my_insert(&mytree, tmp);
		        else {
                    errors++;
                    printf("Error %d at line %d : Illegal use of \'.\'\n", DOT_ILLEGAL_USE, last_row);
		        	// char msg[100];
	        		// sprintf(msg, "Error %d at line %d : Illegal use of \'.\'", DOT_ILLEGAL_USE, last_row);
	        		// myerror(msg);
		        }
		    }/*
		    else { // 结构体未定义
		    	$$->varDef = 0;
		    	// \begin{jcy 17}
		        char msg[100];
		        sprintf(msg, "Error %d at line %d : Undefined struct \'%s\'", UNDEFINED_STRUCT, last_row, tmp.name);
		        myerror(msg);
		        // \end{jcy 17}
		    }*/
		}
		else {
            errors++;
            printf("Error %d at line %d : Illegal use of \'.\'\n", DOT_ILLEGAL_USE, last_row);
			// char msg[100];
	        // sprintf(msg, "Error %d at line %d : Illegal use of \'.\'", DOT_ILLEGAL_USE, last_row);
	        // myerror(msg);
		}
        //	\end{jcy 13}
	}
	| ID {
		$$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);

        MyType tmp = MyType_default;
        // tmp.name = (char*)malloc(sizeof($1->id));
        strcpy(tmp.name, $1->id);
        // $$->type = STRING_TYPE;
        MyType* mt = search(this_scope, tmp); // 寻找该变量的声明结点
        if(mt != NULL) { 
            // $$->name = mt->type;
            tmp.def = 1;
            // this_scope = insert(this_scope, tmp); // Exp中的ID不能插入符号表，只能查
            // free(tmp.type);
        }
        else { // 变量未定义
            errors++;
            printf("Error %d at line %d : Undefined variable \'%s\'\n", UNDEFINED_VARIABLE, last_row, tmp.name);
            // char msg[100];
            // sprintf(msg, "Error %d at line %d : Undefined variable \'%s\'", UNDEFINED_VARIABLE, last_row, tmp.name);
            // myerror(msg);
        }
        // free(tmp.name);
	}
	| INT {
		$$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);

        // $$->name = "int";
        char num[20] = {0};
        sprintf(num, "%d", $1->intValue);

        MyType tmp = MyType_default;
        strcpy(tmp.name, num);
        strcpy(tmp.type, "int");
        this_scope = insert(this_scope, tmp);

        $$->isAssignable = 0;
	}
	| FLOAT {
		$$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);

        // $$->name = "float";
        char num[20] = {0};
        sprintf(num, "%f", $1->floatValue);

        MyType tmp = MyType_default;
        strcpy(tmp.name, num);
        strcpy(tmp.type, "float");
        this_scope = insert(this_scope, tmp);
        $$->isAssignable = 0;
	}
	| LP error RP {
		char msg[100];
        sprintf(msg, "Syntax error.");
        // fprintf(stderr, "Error type B at line %d: %s\n", yylineno, msg);
		// errors++;
		myerror(msg);
	}
	| ID LP error RP {
		char msg[100];
        sprintf(msg, "Syntax error.");
        // fprintf(stderr, "Error type B at line %d: %s\n", yylineno, msg);
		// errors++;
		myerror(msg);
	}
	| Exp LB error RB{
		char msg[100];
        sprintf(msg, "Syntax error.");
        // fprintf(stderr, "Error type B at line %d: %s\n", yylineno, msg);
		// errors++;
		myerror(msg);
	}
    ;

Args : Exp COMMA Args {
        $$ = insNode($1, "CompSt", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
    }
    | Exp {
        $$ = insNode($1, "CompSt", @1.first_line, NON_TERMINAL);
    }
    ;
	
%%
// #include "lex.yy.c"

int main(int argc, char** argv) {
    this_scope = init(this_scope);

	if(argc <= 1) return 1;
	FILE* f = fopen(argv[1], "r");
	if(!f) {
		perror(argv[1]);
		return 1;
	}
	yylineno = 1;
	yyrestart(f);
	yyparse();

    /*----检查Error 18和19----*/

	FILE *f1 = fopen("output.txt", "w");
	if(!f1) {
		perror(argv[1]);
		return 1;
	}
	if(!errors) {
        printf("None!!!\n");
		f1 = fopen("output.txt", "w");
        
		printTree(head, 0, f1);
	}
	return 0;
}


void yyerror(char *msg) {
    // errors++;
    // fprintf(stderr, "Error type B at Line %d: %s because %s\n", yylineno, msg, yytext);
}

void myerror(char *msg) {
    fprintf(stderr, "Error type B at Line %d: %s\n", last_row, msg); // B
	errors++;
}
