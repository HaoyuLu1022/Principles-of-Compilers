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
    #define AMBIGUOUS_FUNCTION_DECLARATION 19

    #define MIN(i, j) (((i) < (j)) ? (i) : (j))
    #define MAX(i, j) (((i) > (j)) ? (i) : (j))


	void yyerror(char*);
	void myerror(char*);
	int yylex();
	extern int yylineno;
	extern int last_row;
    extern int CompstCNT;
	int errors = 0;
    int yydebug = 1;
    int flgStruct = 0, flgArr = 0, func_cnt = 0;
    char Compst_return_type[20] = "null";
    char func_list[20][20];
    struct rb_root mytree = RB_ROOT;
    // MyType tmp; // 从全局变量改用局部变量
    VariLink this_scope;
    VariLink variList;

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

            strcpy(Compst_return_type, "null");

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
        strcpy(tmp.return_type, Compst_return_type);
        
        // if(strcmp(Compst_return_type, "null")) {
        //     if(strcmp(tmp.return_type, Compst_return_type)) {
        //     // if(tmp.return_type != Compst_return_type) {
        //         errors++;
        //         printf("Error %d at line %d : Type mismatched for return\n", TYPE_MISMATCH_RETURN, last_row);
        //         // char msg[100];
        //         // sprintf(msg, "Error %d at line %d : Type mismatched for return", TYPE_MISMATCH_RETURN, last_row);
        //         // myerror(msg);
        //     }
        // }
		strcpy(Compst_return_type, "null");
		// printf("return type: %s\n", tmp.return_type);
        MyType* t = search(this_scope, tmp);
        strcpy(t->return_type, tmp.return_type); // 给上级作用域中的函数声明赋返回值类型

        struct my_node* mt = my_search(&this_scope->my_root, tmp); // 确认当前的新作用域没有声明
        if(mt) {
            // printf("def %d\n", mt->info.def);
            if(mt->info.def) {
                errors++;
                printf("Error %d at line %d : Redefined function \'%s\'\n", REDEFINED_FUNCTION, last_row, tmp.name);
            }
            else {
                mt->info.def = 1;
                // printf("没啥\n");
            }
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
                    
                    if(!flgStruct)
                        strcpy(t.type, n->child->child->child->id);
                    else
                        strcpy(t.type, n->child->child->child->child->bro->child->id);
                    
                    if(flgArr) {
                        struct node* newnode = n->child->child->bro;
                        // printf("%s\n", newnode->name);
                        while(!strcmp(newnode->name, "VarDec")) {
                            newnode = newnode->child;
                            // printf("name: %s\n", newnode->name);
                        }
                        strcpy(t.name, newnode->id);
                        t.isarr = 1;
                        t.dimension = n->child->child->bro->child->bro->bro->intValue;
                        // printf("array: %s[%d]\n", t.name, t.dimension);
                    }
                    else 
                        strcpy(t.name, n->child->child->bro->child->id);
                    int result = my_insert(&tmp.varilist, t);
                    

                    t = MyType_default;
                    if(!flgStruct)
                        strcpy(t.type, n->child->child->child->id);
                    else
                        strcpy(t.type, n->child->child->child->child->bro->child->id);
                    strcpy(t.name, varifunc);
                    varifunc[1] += 1;
                    if(varifunc[1] > '9'){
                        varifunc[0] += 1;
                        varifunc[1] = '0';
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
            // my_insert(&this_scope->last->my_root, tmp);
            // print(this_scope);
        }
		// jcy 8
        flgStruct = 0;
        free(variList);
        variList = (VariLink)malloc(sizeof(VariLink));
        this_scope = pop_scope(this_scope);
    }
    | Specifier FunDec SEMI {
        $$ = insNode($1, "ExtDef", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        MyType tmp = MyType_default;
        tmp.def = 0; // 只是声明，尚未定义
        strcpy(tmp.name, $2->child->id);
        tmp.isfunc = 1;
        strcpy(tmp.return_type, $1->child->id);
        if(search(this_scope, tmp)) {
            errors++;
            printf("Error %d at line %d : Incompleted definition of function \'%s\'\n", AMBIGUOUS_FUNCTION_DECLARATION, last_row, tmp.name);
        }
		else {
            tmp.isfunc = 1;
            tmp.dimension = last_row; // 借用存一下函数所在行数
            // tmp.def = 1;
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
                        varifunc[1] = '0';
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
            this_scope = insert(this_scope, tmp);
            // my_insert(&this_scope->last->my_root, tmp);
            // printf("%s\n", tmp.name);
            strcpy(func_list[func_cnt], tmp.name);
            func_cnt++;
        }
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

        // printf("return_type: %s\n", $1->id);
        if(!CompstCNT) {
            if(!strcmp($1->id, "int")) { // $2->child->type == INT_TYPE
                strcpy(Compst_return_type, "int");
            }
            else if(!strcmp($1->id, "float")) { // $2->child->type == FLOAT_TYPE
                strcpy(Compst_return_type, "float");
            }
            else if($1->type == STRING_TYPE) {
                strcpy(Compst_return_type, $1->id);
            }
        }
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
        }
        else {
            tmp.def = 1;
            tmp.isstruct = 1;
            // printf("%s\n", tmp.name);
            struct node* newnode = $4; // newnode保持指向Mid
            
            // char* mid = "Mid";
            // tmp.varilist = (struct rb_root*)malloc(sizeof(struct rb_root*));
            char VariStruct[12] = {"00_varistct"};
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
                    strcpy(temp.name, VariStruct);
                    result = my_insert(&tmp.varilist, temp);
                    VariStruct[1] += 1;
                    if(VariStruct[1] > '9'){
                        VariStruct[0] += 1;
                        VariStruct[1] = '0';
                    }

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

            tmp.def = 0;
            tmp.isstruct = 0;
            // flgStruct = 1;
        }

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
       
        MyType temp = MyType_default;
        variList = (VariLink)malloc(sizeof(VariLink));
        struct node* newnode = $3; // newnode始终指向VarList
        char varifunc[12] = {"00_varifunc"};
        do {
            MyType tmp = MyType_default;
            tmp.def = 1;
            tmp.isvariable = 1;

            if(flgArr) {
                strcpy(tmp.name, $3->child->child->bro->child->child->id);
                tmp.isarr = 1;
                tmp.dimension = $3->child->child->bro->child->bro->bro->intValue;
            }
            else {
                strcpy(tmp.name, $3->child->child->bro->child->id);
            }

            if(flgStruct) {
                strcpy(tmp.type, $3->child->child->child->child->bro->child->id);
            }
            else {
                strcpy(tmp.type, $3->child->child->child->id);
            }

            int result = my_insert(&variList->my_root, tmp);
            my_insert(&temp.varilist, tmp);

            tmp = MyType_default;
            if(flgStruct) {
                strcpy(tmp.type, $3->child->child->child->child->bro->child->id);
            }
            else {
                strcpy(tmp.type, $3->child->child->child->id);
            }
            strcpy(tmp.name, varifunc);
            varifunc[1] += 1;
            if(varifunc[1] > '9') {
                varifunc[0] += 1;
                varifunc[1] = '0';
            }
            my_insert(&temp.varilist, tmp);

            if(newnode->child->bro) {
                newnode = newnode->child->bro->bro;
            }
            else break;
        } while(newnode);
        temp.isfunc = 1;
        strcpy(temp.name, $1->id);
        MyType* mt = search(this_scope, temp);
        if(mt) {
            if(mt->def) { // 被实现过
                errors++;
                printf("Error %d at line %d : Redefined function \'%s\'\n", REDEFINED_FUNCTION, last_row, temp.name);
            }
            else { // 未被实现过
                mt->def = 1;
                // printf("没啥\n");
            }
        } // waiting
        this_scope = insert(this_scope, temp);
    }
    | ID LP RP {
        $$ = insNode($1, "FunDec", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        MyType temp = MyType_default;
        temp.isfunc = 1;
        strcpy(temp.name, $1->id);
        MyType* mt = search(this_scope, temp);
        if(mt) {
            if(mt->def) { // 被实现过
                errors++;
                printf("Error %d at line %d : Redefined function \'%s\'\n", REDEFINED_FUNCTION, last_row, temp.name);
            }
            else { // 未被实现过
                mt->def = 1;
                // printf("没啥\n");
            }
        } // waiting
        this_scope = insert(this_scope, temp);
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
            
            if(!flgArr) { // 不是数组
            // printf("name: %s\n", newnode->child->child->child->name);
                strcpy(tmp.name, newnode->child->child->child->id);
            }
            else { // 是数组
                struct node* n = newnode->child->child->child->child;
                while(!strcmp(n->name, "VarDec")) {
                    n = n->child;
                    // printf("name: %s\n", n->name);
                }
                strcpy(tmp.name, n->id);
            }

            if(my_search(&this_scope->my_root, tmp) || my_search(&variList->my_root, tmp)) { // 两种可能：struct xx {...} yy; 或 int a;
                char msg[100];
                if(!flgStruct)  {// 普通变量声明
                    errors++;
                    printf("Error %d at line %d : Redefined variable \'%s\'\n", REDEFINED_VARIABLE, last_row, tmp.name);
                }
                else {// 结构体变量声明
                    errors++;
                    printf("Error %d at line %d : Redefined field \'%s\'\n", REDEFINED_FIELD, last_row, tmp.name);
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
                            }
                        }
                        else if(!strcmp(newnode->child->child->bro->bro->child->name, "INT")) {
                            if(strcmp("int", $1->child->id)) {
                                errors++;
                                printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                            }
                        }
                        else if(!strcmp(newnode->child->child->bro->bro->child->name, "FLOAT")) {
                            if(strcmp("float", $1->child->id)) {
                                errors++;
                                printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                            }
                        }
                    }
                }
                tmp.isvariable = 1;
                this_scope = insert(this_scope, tmp);
                // print(this_scope);
            }
        
            // tmp.isvariable = 1;
            // this_scope = insert(this_scope, tmp);
                
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

        if($2->type == 1) {
            if(strcmp(Compst_return_type, "int")) {
                errors++;
                printf("Error %d at line %d : Type mismatched for return\n", TYPE_MISMATCH_RETURN, last_row);
            }
        }
        else if($2->type == 2) {
            if(strcmp(Compst_return_type, "float")) {
                errors++;
                printf("Error %d at line %d : Type mismatched for return\n", TYPE_MISMATCH_RETURN, last_row);
            }
        }
        else if($2->type == STRING_TYPE) {
            if(strcmp(Compst_return_type, $2->id)) {
                errors++;
                printf("Error %d at line %d : Type mismatched for return\n", TYPE_MISMATCH_RETURN, last_row);
            }
        }
        // printf("return_type: %d\n", $2->type);
        // if(!strcmp($2->child->name, "int") || $2->type == 1) { // $2->child->type == INT_TYPE
        //     strcpy(Compst_return_type, "int");
        // }
        // else if(!strcmp($2->child->name, "float") || $2->type == 2) { // $2->child->type == FLOAT_TYPE
        //     strcpy(Compst_return_type, "float");
        // }
        // else if($2->child->type == STRING_TYPE) {
        //     strcpy(Compst_return_type, $2->child->name);
        // }
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

        // printf("%s vs %s\n", $1->property, $3->property);
        if($1->child->type != STRING_TYPE && $1->child->type != NON_TERMINAL) {
            errors++;
            printf("Error %d at line %d : The left-hand side of assignment must be a variable\n", NEED_VARIABLE, last_row); 
        }
        else if(!strcmp($1->property, $3->property)) {
            strcpy($$->property, $1->property);
        }
        else if($1->child->type == NON_TERMINAL) { // 说明可能是数组
            // printf("yes\n");
            MyType t1 = MyType_default;
            struct node* n = $1->child->child;
            while(!strcmp(n->name, "Exp")) {
                n = n->child;
                // printf("name: %s\n", n->id);
            }
            strcpy(t1.name, n->id);

            MyType *t2 = search(this_scope, t1);
            if(t2) {
                // printf("name: %s\n", $3->child->name);
                if(!strcmp($3->child->name, "ID")) { // $3->child->type == STRING_TYPE
                    MyType t3 = MyType_default;
                    // printf("%s\n", $3->child->id);
                    strcpy(t3.name, $3->child->id);
                    MyType* t4 = search(this_scope, t3);
                    if(t4) {
                        if(t4->isfunc) {
                            if(strcmp(t2->type, t4->return_type)) {
                                errors++;
                                printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row);
                            }
                        }
                        else {
                            if(strcmp(t2->type, t4->type)) {
                                errors++;
                                printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                            }
                        }
                    }
                }
                else if(!strcmp($3->child->name, "FLOAT")) {
                    if(strcmp(t2->type, "float")) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    }
                }
                else if(!strcmp($3->child->name, "INT")) {
                    if(strcmp(t2->type, "int")) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    }
                }
            }
        }
        else {
            // printf("%s\n", $1->child->id);
            MyType t1 = MyType_default;
            strcpy(t1.name, $1->child->id);
            MyType *t2 = search(this_scope, t1);
            if(!t2) {
                t2 = &(my_search(&variList->my_root, t1))->info;
            }
            if(t2) {
                // printf("%s\n", $3->child->id);
                if(!strcmp($3->child->name, "ID")) { // $3->child->type == STRING_TYPE
                    MyType t3 = MyType_default;
                    // printf("%s\n", $3->child->child->id);
                    strcpy(t3.name, $3->child->id);
                    MyType* t4 = search(this_scope, t3);
                    // printf("%s %s\n", t2->type, t4->type);
                    if(t4) {
                        int right = 1;
                        MyType tmp = MyType_default;
                        strcpy(tmp.name, t2->type);
                        Mylink s1 = search(this_scope, tmp);

                        strcpy(tmp.name, t4->type);
                        Mylink s2 = search(this_scope, tmp);
                        if(s1 && s2 && s1->def && s2->def){   // 先判断这俩结构体是否定义过
                            char VariStruct[12] = {"00_varistct"};
                            strcpy(tmp.name, VariStruct);
                            struct my_node* Varis1 = my_search(&(s1->varilist), tmp);
                            struct my_node* Varis2 = my_search(&(s2->varilist), tmp);

                            while(Varis1 || Varis2) {
                                // printf("%s %s\n", Varis1->info.type, Varis2->info.type);
                                if(Varis1 == NULL||Varis2==NULL){
                                    right = 0;
                                }
                                else if(strcmp(Varis1->info.type, Varis2->info.type)){
                                    right = 0;
                                }
                                VariStruct[1] += 1;
                                if(VariStruct[1] > '9'){
                                    VariStruct[0] += 1;
                                    VariStruct[1] = '0';
                                }
                                strcpy(tmp.name, VariStruct);
                                Varis1 = my_search(&(s1->varilist), tmp);
                                Varis2 = my_search(&(s2->varilist), tmp);
                            }
                            // printf("\n");
                        }
                        else right = 0;  // 还是感觉应该写未定义
                        if(right == 0){
                            printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row);
                            errors ++;
                        }
                    }
                }
                else if(!strcmp($3->child->name, "FLOAT")) {
                    if(strcmp(t2->type, "float")) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    }
                }
                else if(!strcmp($3->child->name, "INT")) {
                    if(strcmp(t2->type, "int")) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for assignment\n", TYPE_MISMATCH_ASSIGNMENT, last_row); 
                    }
                }
            }
        }
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
        // printf("%s vs %s\n", $1->property, $3->property);
        
        if(strcmp($1->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp($1->child->name, "INT")) {
                sprintf(num1, "%d", $1->child->intValue);
            }
            else if(!strcmp($1->child->name, "FLOAT")) {
                sprintf(num1, "%f", $1->child->floatValue);
            }
            
            strcpy(t1.name, num1);
        }
        else if(!strcmp($1->child->name, "ID")) {
            strcpy(t1.name, $1->child->id);
        }

        if(!strcmp($1->property, $3->property)) {
            strcpy($$->property, $1->property);
        }
        else if(strcmp(t1.name, "") && strcmp($1->property, $3->property)) {
            t2 = search(this_scope, t1);
            if(!t2) {
                t2 = &my_search(&variList->my_root, t1)->info;
            }

            if(t2) {
                char num2[20] = {0};
                MyType t3 = MyType_default;
                MyType* t4;
                
                if(strcmp($3->child->name, "ID")) {
                    if(!strcmp($3->child->name, "INT")) {
                        sprintf(num2, "%d", $3->child->intValue);
                        if(strcmp(t2->type, "int")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 1;
                            strcpy($$->property, "int");
                        }
                    }
                    else if(!strcmp($3->child->name, "FLOAT")) {
                        sprintf(num2, "%f", $3->child->floatValue);
                        if(strcmp(t2->type, "float")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 2;
                            strcpy($$->property, "float");
                        }
                    }
                }
                else {
                    // printf("id: %s\n" $3->child->id);
                    // print(this_scope);,
                    strcpy(t3.name, $3->child->id);
                    t4 = search(this_scope, t3);
                    if(t4) {
                        if(strcmp(t2->type, t4->type)) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = $1->type;
                            strcpy($$->property, $1->property);
                        }
                    }
                    else if($1->type != $3->type) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                    }
                    else {
                        // $$->type = $1->type;
                        strcpy($$->property, $1->property);
                    }
                }
            }
            
        }
    }
    | Exp OR Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        // printf("%s vs %s\n", $1->property, $3->property);
        
        if(strcmp($1->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp($1->child->name, "INT")) {
                sprintf(num1, "%d", $1->child->intValue);
            }
            else if(!strcmp($1->child->name, "FLOAT")) {
                sprintf(num1, "%f", $1->child->floatValue);
            }
            
            strcpy(t1.name, num1);
        }
        else if(!strcmp($1->child->name, "ID")) {
            strcpy(t1.name, $1->child->id);
        }

        if(!strcmp($1->property, $3->property)) {
            strcpy($$->property, $1->property);
        }
        else if(strcmp(t1.name, "") && strcmp($1->property, $3->property)) {
            t2 = search(this_scope, t1);
            if(!t2) {
                t2 = &my_search(&variList->my_root, t1)->info;
            }

            if(t2) {
                char num2[20] = {0};
                MyType t3 = MyType_default;
                MyType* t4;
                
                if(strcmp($3->child->name, "ID")) {
                    if(!strcmp($3->child->name, "INT")) {
                        sprintf(num2, "%d", $3->child->intValue);
                        if(strcmp(t2->type, "int")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 1;
                            strcpy($$->property, "int");
                        }
                    }
                    else if(!strcmp($3->child->name, "FLOAT")) {
                        sprintf(num2, "%f", $3->child->floatValue);
                        if(strcmp(t2->type, "float")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 2;
                            strcpy($$->property, "float");
                        }
                    }
                }
                else {
                    // printf("id: %s\n" $3->child->id);
                    // print(this_scope);,
                    strcpy(t3.name, $3->child->id);
                    t4 = search(this_scope, t3);
                    if(t4) {
                        if(strcmp(t2->type, t4->type)) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = $1->type;
                            strcpy($$->property, $1->property);
                        }
                    }
                    else if($1->type != $3->type) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                    }
                    else {
                        // $$->type = $1->type;
                        strcpy($$->property, $1->property);
                    }
                }
            }
            
        }
    }
    | Exp RELOP Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
    
        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        // printf("%s vs %s\n", $1->property, $3->property);
        
        if(strcmp($1->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp($1->child->name, "INT")) {
                sprintf(num1, "%d", $1->child->intValue);
            }
            else if(!strcmp($1->child->name, "FLOAT")) {
                sprintf(num1, "%f", $1->child->floatValue);
            }
            
            strcpy(t1.name, num1);
        }
        else if(!strcmp($1->child->name, "ID")) {
            strcpy(t1.name, $1->child->id);
        }

        if(!strcmp($1->property, $3->property)) {
            strcpy($$->property, $1->property);
        }
        else if(strcmp(t1.name, "") && strcmp($1->property, $3->property)) {
            t2 = search(this_scope, t1);
            if(!t2) {
                t2 = &my_search(&variList->my_root, t1)->info;
            }

            if(t2) {
                char num2[20] = {0};
                MyType t3 = MyType_default;
                MyType* t4;
                
                if(strcmp($3->child->name, "ID")) {
                    if(!strcmp($3->child->name, "INT")) {
                        sprintf(num2, "%d", $3->child->intValue);
                        if(strcmp(t2->type, "int")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 1;
                            strcpy($$->property, "int");
                        }
                    }
                    else if(!strcmp($3->child->name, "FLOAT")) {
                        sprintf(num2, "%f", $3->child->floatValue);
                        if(strcmp(t2->type, "float")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 2;
                            strcpy($$->property, "float");
                        }
                    }
                }
                else {
                    // printf("id: %s\n" $3->child->id);
                    // print(this_scope);,
                    strcpy(t3.name, $3->child->id);
                    t4 = search(this_scope, t3);
                    if(t4) {
                        if(strcmp(t2->type, t4->type)) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = $1->type;
                            strcpy($$->property, $1->property);
                        }
                    }
                    else if($1->type != $3->type) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                    }
                    else {
                        // $$->type = $1->type;
                        strcpy($$->property, $1->property);
                    }
                }
            }
            
        }
    }
    | Exp PLUS Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        // printf("%s vs %s\n", $1->property, $3->property);
        
        if(strcmp($1->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp($1->child->name, "INT")) {
                sprintf(num1, "%d", $1->child->intValue);
            }
            else if(!strcmp($1->child->name, "FLOAT")) {
                sprintf(num1, "%f", $1->child->floatValue);
            }
            
            strcpy(t1.name, num1);
        }
        else if(!strcmp($1->child->name, "ID")) {
            strcpy(t1.name, $1->child->id);
        }

        if(!strcmp($1->property, $3->property)) {
            strcpy($$->property, $1->property);
        }
        else if(strcmp(t1.name, "") && strcmp($1->property, $3->property)) {
            t2 = search(this_scope, t1);
            if(!t2) {
                t2 = &my_search(&variList->my_root, t1)->info;
            }

            if(t2) {
                char num2[20] = {0};
                MyType t3 = MyType_default;
                MyType* t4;
                
                if(strcmp($3->child->name, "ID")) {
                    if(!strcmp($3->child->name, "INT")) {
                        sprintf(num2, "%d", $3->child->intValue);
                        if(strcmp(t2->type, "int")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 1;
                            strcpy($$->property, "int");
                        }
                    }
                    else if(!strcmp($3->child->name, "FLOAT")) {
                        sprintf(num2, "%f", $3->child->floatValue);
                        if(strcmp(t2->type, "float")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 2;
                            strcpy($$->property, "float");
                        }
                    }
                }
                else {
                    // printf("id: %s\n" $3->child->id);
                    // print(this_scope);,
                    strcpy(t3.name, $3->child->id);
                    t4 = search(this_scope, t3);
                    if(t4) {
                        if(strcmp(t2->type, t4->type)) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = $1->type;
                            strcpy($$->property, $1->property);
                        }
                    }
                    else if($1->type != $3->type) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                    }
                    else {
                        // $$->type = $1->type;
                        strcpy($$->property, $1->property);
                    }
                }
            }
            
        }
    }
    | Exp MINUS Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        // printf("%s vs %s\n", $1->property, $3->property);
        
        if(strcmp($1->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp($1->child->name, "INT")) {
                sprintf(num1, "%d", $1->child->intValue);
            }
            else if(!strcmp($1->child->name, "FLOAT")) {
                sprintf(num1, "%f", $1->child->floatValue);
            }
            
            strcpy(t1.name, num1);
        }
        else if(!strcmp($1->child->name, "ID")) {
            strcpy(t1.name, $1->child->id);
        }

        if(!strcmp($1->property, $3->property)) {
            strcpy($$->property, $1->property);
        }
        else if(strcmp(t1.name, "") && strcmp($1->property, $3->property)) {
            t2 = search(this_scope, t1);
            if(!t2) {
                t2 = &my_search(&variList->my_root, t1)->info;
            }

            if(t2) {
                char num2[20] = {0};
                MyType t3 = MyType_default;
                MyType* t4;
                
                if(strcmp($3->child->name, "ID")) {
                    if(!strcmp($3->child->name, "INT")) {
                        sprintf(num2, "%d", $3->child->intValue);
                        if(strcmp(t2->type, "int")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 1;
                            strcpy($$->property, "int");
                        }
                    }
                    else if(!strcmp($3->child->name, "FLOAT")) {
                        sprintf(num2, "%f", $3->child->floatValue);
                        if(strcmp(t2->type, "float")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 2;
                            strcpy($$->property, "float");
                        }
                    }
                }
                else {
                    // printf("id: %s\n" $3->child->id);
                    // print(this_scope);,
                    strcpy(t3.name, $3->child->id);
                    t4 = search(this_scope, t3);
                    if(t4) {
                        if(strcmp(t2->type, t4->type)) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = $1->type;
                            strcpy($$->property, $1->property);
                        }
                    }
                    else if($1->type != $3->type) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                    }
                    else {
                        // $$->type = $1->type;
                        strcpy($$->property, $1->property);
                    }
                }
            }
            
        }
    }
    | Exp STAR Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        // printf("%s vs %s\n", $1->property, $3->property);
        
        if(strcmp($1->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp($1->child->name, "INT")) {
                sprintf(num1, "%d", $1->child->intValue);
            }
            else if(!strcmp($1->child->name, "FLOAT")) {
                sprintf(num1, "%f", $1->child->floatValue);
            }
            
            strcpy(t1.name, num1);
        }
        else if(!strcmp($1->child->name, "ID")) {
            strcpy(t1.name, $1->child->id);
        }

        if(!strcmp($1->property, $3->property)) {
            strcpy($$->property, $1->property);
        }
        else if(strcmp(t1.name, "") && strcmp($1->property, $3->property)) {
            t2 = search(this_scope, t1);
            if(!t2) {
                t2 = &my_search(&variList->my_root, t1)->info;
            }

            if(t2) {
                char num2[20] = {0};
                MyType t3 = MyType_default;
                MyType* t4;
                
                if(strcmp($3->child->name, "ID")) {
                    if(!strcmp($3->child->name, "INT")) {
                        sprintf(num2, "%d", $3->child->intValue);
                        if(strcmp(t2->type, "int")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 1;
                            strcpy($$->property, "int");
                        }
                    }
                    else if(!strcmp($3->child->name, "FLOAT")) {
                        sprintf(num2, "%f", $3->child->floatValue);
                        if(strcmp(t2->type, "float")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 2;
                            strcpy($$->property, "float");
                        }
                    }
                }
                else {
                    // printf("id: %s\n" $3->child->id);
                    // print(this_scope);,
                    strcpy(t3.name, $3->child->id);
                    t4 = search(this_scope, t3);
                    if(t4) {
                        if(strcmp(t2->type, t4->type)) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = $1->type;
                            strcpy($$->property, $1->property);
                        }
                    }
                    else if($1->type != $3->type) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                    }
                    else {
                        // $$->type = $1->type;
                        strcpy($$->property, $1->property);
                    }
                }
            }
            
        }
    }
    | Exp DIV Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        char num1[20] = {0};
        MyType t1 = MyType_default;
        MyType* t2;
        // printf("%s vs %s\n", $1->property, $3->property);
        
        if(strcmp($1->child->name, "ID")) { // $1->child->type != STRING_TYPE
            if(!strcmp($1->child->name, "INT")) {
                sprintf(num1, "%d", $1->child->intValue);
            }
            else if(!strcmp($1->child->name, "FLOAT")) {
                sprintf(num1, "%f", $1->child->floatValue);
            }
            
            strcpy(t1.name, num1);
        }
        else if(!strcmp($1->child->name, "ID")) {
            strcpy(t1.name, $1->child->id);
        }

        if(!strcmp($1->property, $3->property)) {
            strcpy($$->property, $1->property);
        }
        else if(strcmp(t1.name, "") && strcmp($1->property, $3->property)) {
            t2 = search(this_scope, t1);
            if(!t2) {
                t2 = &my_search(&variList->my_root, t1)->info;
            }

            if(t2) {
                char num2[20] = {0};
                MyType t3 = MyType_default;
                MyType* t4;
                
                if(strcmp($3->child->name, "ID")) {
                    if(!strcmp($3->child->name, "INT")) {
                        sprintf(num2, "%d", $3->child->intValue);
                        if(strcmp(t2->type, "int")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 1;
                            strcpy($$->property, "int");
                        }
                    }
                    else if(!strcmp($3->child->name, "FLOAT")) {
                        sprintf(num2, "%f", $3->child->floatValue);
                        if(strcmp(t2->type, "float")) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = 2;
                            strcpy($$->property, "float");
                        }
                    }
                }
                else {
                    // printf("id: %s\n" $3->child->id);
                    // print(this_scope);,
                    strcpy(t3.name, $3->child->id);
                    t4 = search(this_scope, t3);
                    if(t4) {
                        if(strcmp(t2->type, t4->type)) {
                            errors++;
                            printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                        }
                        else {
                            // $$->type = $1->type;
                            strcpy($$->property, $1->property);
                        }
                    }
                    else if($1->type != $3->type) {
                        errors++;
                        printf("Error %d at line %d : Type mismatched for operands\n", TYPE_MISMATCH_OPERAND, last_row);
                    }
                    else {
                        // $$->type = $1->type;
                        strcpy($$->property, $1->property);
                    }
                }
            }
            
        }
    }
    | LP Exp RP {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        strcpy($$->property, $2->property);
    }
    | MINUS Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;

        strcpy($$->property, $2->property);
    }
    | NOT Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;

        strcpy($$->property, $2->property);
    }
    | ID LP Args RP {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        $3->bro = $4;

        MyType tmp = MyType_default;
        // tmp.name = (char*)malloc(sizeof($1->id));
        strcpy(tmp.name, $1->id);
        // $$->isAssignable = 0;
        MyType* mt = search(this_scope, tmp);
        if(mt != NULL) { 
            // tmp.def = 1;
            
            if(mt->isfunc) {
                if(!strcmp(Compst_return_type, "null")) {
                    // printf("return type: %s\n", mt->return_type);
                    strcpy($$->property, mt->return_type);
                }
                else {
                    strcpy($$->property, Compst_return_type);
                }
                // if(!strcmp(mt->return_type, "int")) {
                //     $$->type == 1;
                // }
                // else if(!strcmp(mt->return_type, "float")) {
                //     $$->type == 2;
                // }
                // this_scope = insert(this_scope, tmp);
                // dxr to do
                struct node* newnode = $3; // newnode始终指向Args
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
                    if(ttp != NULL) {
                        parameter = ttp->info;
                        // printf("%s : %s\n", mt->name, parameter.type);
                    }  // 后面做了
                    if(strcmp(newnode->child->child->name, "ID")){  // 不是变量
                        // printf("%s\n", newnode->child->child->name);
                        char argu[20];
                        // printf("%d\n", newnode->child->child->type);
                        if(strcmp(newnode->child->child->name, "INT") == 0 || newnode->child->type == 1){
                            strcpy(argu, "int");
                        }
                        else if(strcmp(newnode->child->child->name, "FLOAT") == 0 || newnode->child->type == 2){
                            strcpy(argu, "float");
                        }
                        else if(!strcmp(newnode->child->child->name, "Exp")) {
                            // printf("property: %s\n", newnode->child->child->property);
                            strcpy(argu, newnode->child->child->property);
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
                            printf("test1: %s test2: %s test3: %s\n", mt->name, parameter.type, argu);
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
                        // assert(tttp != NULL);
                        if(tttp != NULL) {
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
                    }
                    varifunc[1] += 1;
                    if(varifunc[1] > '9'){
                        varifunc[0] += 1;
                        varifunc[1] = '0';
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
                        varifunc[1] = '0';
                    }
                    strcpy(parameter.name, varifunc);
                    tpp = my_search(&(mt->varilist), parameter);
                    right = 0;
                }
                if(right == 0) {
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
                // 	\end{jcy 11}
            }
        }
        else if(!strcmp($1->id, "write")) {

        }
        else { // 函数未定义
            errors++;
            printf("Error %d at line %d : Undefined function \'%s\'\n", UNDEFINED_FUNCTION, last_row, tmp.name);
        }
    }
    | ID LP RP {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        MyType tmp = MyType_default;
        // tmp.name = (char*)malloc(sizeof($1->id));
        strcpy(tmp.name, $1->id);
        // $$->isAssignable = 0;
        MyType* mt = search(this_scope, tmp);
        if(mt != NULL) { 
            // tmp.def = 1;
            if(mt->isfunc) {
                // if(strcmp(mt->return_type, "int"))
                
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
                        varifunc[1] = '0';
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
                // 	\end{jcy 11}
            }
        }
        else if(!strcmp($1->id, "read")) {

        }
        else { // 函数未定义
            errors++;
            printf("Error %d at line %d : Undefined function \'%s\'\n", UNDEFINED_FUNCTION, last_row, tmp.name);
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
            // print(this_scope);
            // my_print(&variList->my_root);
            if(ml) {
                if(ml->isarr) {
		    		// \begin{jcy 12}
                    // printf("%s\n", $3->child->name);
		    		if(strcmp($3->child->name, "INT")) {
                        if(!strcmp($3->child->name, "FLOAT")) {
                            errors++;
                            printf("Error %d at line %d : \'%f\' is not an integer\n", ARRAY_ACCESS_OPERATEOR_NOT_INTEGER, last_row, $3->child->floatValue);
                        }
		    		}
		    		// \end{jcy 12}
		    	}
		    	else {
                    errors++;
                    printf("Error %d at line %d : \'%s\' is not an array\n", NOT_ARRAY, last_row, tmp.name);
		    	}
            }
            else {
                ml = &my_search(&variList->my_root, tmp)->info;
                if(ml) {
                    if(ml->isarr) {
		    		// \begin{jcy 12}
                    // printf("%s\n", $3->child->name);
		    		if(strcmp($3->child->name, "INT")) {
		    			// char msg[100];
                        if(!strcmp($3->child->name, "FLOAT")) {
                            errors++;
                            printf("Error %d at line %d : \'%f\' is not an integer\n", ARRAY_ACCESS_OPERATEOR_NOT_INTEGER, last_row, $3->child->floatValue);
                        }
		    		}
		    		// \end{jcy 12}
                    }
                    else {
                        errors++;
                        printf("Error %d at line %d : \'%s\' is not an array\n", NOT_ARRAY, last_row, tmp.name);
                    }
                }
                else {
                    errors++;
                    printf("Error %d at line %d : Undefined variable \'%s\'\n", UNDEFINED_VARIABLE, last_row, tmp.name);
                }
            }
      
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
		    if(ml != NULL) { //先获取这个名字的东西，然后看看它是不是结构体
                // 如果不是结构体，则判为错误13；若是结构体，开始看ID是否存在：如果ID存在，将其属性赋给规约后的结果；若ID不存在，则判为错误14
		        if(ml->isstruct) {
                    MyType t1 = MyType_default;
                    strcpy(t1.name, ml->type);
                    MyType* t2 = search(this_scope, t1); // 找到该结构体类型的定义
                    // print(this_scope);

                    MyType t3 = MyType_default;
                    strcpy(t3.name, $3->id);

                    struct my_node* tmp = my_search(&t2->varilist, t3);
                    if(tmp) {
                        strcpy($$->property, tmp->info.type);
                    }
                    else {
                        errors++;
                        printf("Error %d at line %d : Non-existing field \'%s\'\n", NOT_EXISTENT_FIELD, last_row, $3->id);
                    }
		        }
		        else {
                    errors++;
                    printf("Error %d at line %d : Illegal use of \'.\'\n", DOT_ILLEGAL_USE, last_row);
		        }
		    }
		}
		else {
            errors++;
            printf("Error %d at line %d : Illegal use of \'.\'\n", DOT_ILLEGAL_USE, last_row);
		}
        //	\end{jcy 13}
	}
	| ID {
		$$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);

        MyType tmp = MyType_default;
        // tmp.name = (char*)malloc(sizeof($1->id));
        strcpy(tmp.name, $1->id);
        MyType* mt = search(this_scope, tmp); // 寻找该变量的声明结点
        struct my_node* mn = my_search(&variList->my_root, tmp);
        if(mt) { 
            tmp.def = 1;
            strcpy($$->property, mt->type);
        }
        else if(mn) {
            tmp.def = 1;
            strcpy($$->property, mn->info.type);
        }
        else { // 变量未定义
            errors++;
            printf("Error %d at line %d : Undefined variable \'%s\'\n", UNDEFINED_VARIABLE, last_row, tmp.name);
        }
        // free(tmp.name);
	}
	| INT {
		$$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);

        strcpy($$->property, $1->property);
	}
	| FLOAT {
		$$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);

        strcpy($$->property, $1->property);
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
    variList = init(variList);

	if(argc <= 1) return 1;
	FILE* f = fopen(argv[1], "r");
	if(!f) {
		perror(argv[1]);
		return 1;
	}
	yylineno = 1;
	yyrestart(f);
	yyparse();

    /*----检查Error 18----*/
    MyType tmp = MyType_default;
    for(int i = 0; i < func_cnt; i++) {
        strcpy(tmp.name, func_list[i]);
        MyType* mt = search(this_scope, tmp);
        if(mt) {
            if(!mt->def) {
                errors++;
                printf("Error %d at line %d : Undefined function \'%s\'\n", DECLARED_BUT_NOT_DEFINED, mt->dimension, tmp.name);
            }
        } 
    }

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
