%{
	#include <stdio.h>
	#include <stdlib.h>
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
    
	void yyerror(char*);
	void myerror(char*);
	int yylex();
	extern int yylineno;
	extern int last_row;
	int errors = 0;
    int yydebug = 1;
    int flgStruct = 0, flgArr = 0;
    struct rb_root mytree = RB_ROOT;
    MyType tmp;
    VariLink this_scope;
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
        // printf("%s\n", $2->child->child->id);
        // printf("%s\n", $2->name);
        // tmp.isvariable = 1;
        tmp.name = (char*)malloc(sizeof($2->child->child->id));
        strcpy(tmp.name, $2->child->child->id); // 不要怀疑这个就是变量名
        if(!flgStruct) { // 不是结构体，是普通的变量声明 
            if(search(this_scope, tmp)) {
                char msg[100];
                sprintf(msg, "Error %d at line %d : Redefined variable \'%s\'", REDEFINED_VARIABLE, last_row, tmp.name);
                myerror(msg);
            }
            else {
                // printf("insert variable \'%s\'\n", tmp.name);
                tmp.def = 1;
                // printf("%s\n", $1->child->child->id);
                tmp.type = (char*)malloc(sizeof($1->child->child->id));
                strcpy(tmp.type, $1->child->child->id);
                tmp.isvariable = 1;
                this_scope = insert(this_scope, tmp);

                free(tmp.type);
                tmp.def = 0;
                tmp.isvariable = 0;
            }
        }
        else { // 是结构体，且有变量 tmp.name
            if(search(this_scope, tmp)) {
                char msg[100];
                sprintf(msg, "Error %d at line %d : Redefined variable \'%s\'", REDEFINED_VARIABLE, last_row, tmp.name);
                myerror(msg);
            }
            else {
                // printf("insert variable \'%s\'\n", tmp.name);
                tmp.def = 1;
                tmp.type = (char*)malloc(sizeof($1->child->child->id));
                strcpy(tmp.type, $1->child->child->id);
                tmp.isstruct = 1;
                this_scope = insert(this_scope, tmp);

                free(tmp.type);
                tmp.def = 0;
                tmp.isstruct = 0;
            }
        }
        free(tmp.name);
    }
    | Specifier SEMI {
        $$ = insNode($1, "ExtDef", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
    }
    | Specifier FunDec CompSt {
        $$ = insNode($1, "ExtDef", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        tmp.name = (char*)malloc(sizeof($2->child->id));
        strcpy(tmp.name, $2->child->id);
        Mylink ml = search(this_scope, tmp); // 查找前面的作用域里该函数声明对应的结点
        ml->return_type = (char*)malloc(sizeof($1->child->id));
        strcpy(ml->return_type, $1->child->id); // 赋给它return type
       /* //jcy 8
		if(ml->return_type != $) {				应该有一个从CompSt传下来的return_type
		    char msg[100];
            sprintf(msg, "Error %d at line %d : Type mismatched for return", TYPE_MISMATCH_RETURN, last_row);
            myerror(msg);
		}
		//jcy 8	*/
        MyType newnode = *ml;
        this_scope = insert(this_scope, newnode); // 拷贝前面作用域中函数声明对应的结点，并插入当前作用域

        /*------ To-do: 如何插入参数表 ------*/
        

        this_scope = pop_scope(this_scope);
    }
    | Specifier FunDec SEMI {
    	/*------ TO-do: insert Varlist  */
    	/* if search(this_scope, fun_name)		// jcy 19
    	
    	conflict in Varlist or Specifier
    	
    	// jcy 19
    	else */
    	// 前面没声明过
    	// \begin{jcy 18}
    	
    	/*---- To-do: insert Specifier and Varlist   */
    	tmp.name = (char*)malloc(sizeof($2->child->id));
        strcpy(tmp.name, $2->child->id);
    	char msg[100];
        sprintf(msg, "Error %d at line %d : Incomplete definition of function \'%s\'", DECLARED_BUT_NOT_DEFINED, last_row, tmp.name);
        myerror(msg);
        
        // \end{jcy 18}				to be continued ... 
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

StructSpecifier : STRUCT OptTag LC Mid RC {
        $$ = insNode($1, "StructSpecifier", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        $3->bro = $4;
        $4->bro = $5;

        tmp.name = (char*)malloc(sizeof($2->child->id));
        strcpy(tmp.name, $2->child->id);
        if(search(this_scope, tmp)) { // 结构体名字重复
            char msg[100];
            sprintf(msg, "Error %d at line %d : Duplicate name \'%s\'", REDEFINED_STRUCT, last_row, tmp.name);
            myerror(msg);
        }
        else {
            // printf("insert struct \'%s\'\n", tmp.name);
            tmp.def = 1;
            tmp.isstruct = 1;
            this_scope = insert(this_scope, tmp);

            tmp.def = 0;
            tmp.isstruct = 0;
        }
        free(tmp.name);
    }
    | STRUCT Tag {
        $$ = insNode($1, "StructSpecifier", @1.first_line, NON_TERMINAL);
        $1->bro = $2;

        tmp.name = (char*)malloc(sizeof($2->child->id));
        strcpy(tmp.name, $2->child->id);
        if(!search(this_scope, tmp)) {
            char msg[100];
            sprintf(msg, "Error %d at line %d : Undefined struct \'%s\'", UNDEFINED_STRUCT, last_row, tmp.name);
            myerror(msg);
        }
        else {
            // printf("insert struct \'%s\'\n", tmp.name);
            tmp.def = 1;
            tmp.isstruct = 1;
            this_scope = insert(this_scope, tmp);
            
            tmp.def = 0;
            tmp.isstruct = 0;
        }
        free(tmp.name);
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
    
/*
TypeList : TYPE COMMA TypeList {	// 因为函数声明的时候可以没有形参的符号	for error 18 and 19, but to be continued...

	}
	| TYPE {
	
	}
*/
FunDec : ID LP VarList RP {
        $$ = insNode($1, "FunDec", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        $3->bro = $4;

        tmp.name = (char*)malloc(sizeof($1->id));
        strcpy(tmp.name, $1->id);
        if(search(this_scope, tmp)) { // 函数重定义
            char msg[100];
            sprintf(msg, "Error %d at line %d : Redefined function \'%s\'", REDEFINED_FUNCTION, last_row, tmp.name);
            myerror(msg);
        }
        else {
            // printf("insert function \'%s\'\n", tmp.name);
            tmp.def = 1;
            // printf("%s\n", $1->child->id);
            // tmp.return_type = (char*)malloc(sizeof($1->child->id));
            // strcpy(tmp.return_type, $1->child->id);
            tmp.isfunc = 1;
            this_scope = insert(this_scope, tmp);

            free(tmp.type);
            tmp.def = 0;
            tmp.isfunc = 0;
        }
        // printf("%s\n", tmp.name);
        free(tmp.name);
    }
    | ID LP RP {
        $$ = insNode($1, "FunDec", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;

        tmp.name = (char*)malloc(sizeof($1->id));
        strcpy(tmp.name, $1->id);
        if(search(this_scope, tmp)) { // 函数重定义
            char msg[100];
            sprintf(msg, "Error %d at line %d : Redefined function \'%s\'", REDEFINED_FUNCTION, last_row, tmp.name);
            myerror(msg);
        }
        else {
            // printf("insert function \'%s\'\n", tmp.name);
            tmp.def = 1;
            // printf("%s\n", $1->child->id);
            // tmp.return_type = (char*)malloc(sizeof($1->child->id));
            // strcpy(tmp.return_type, $1->child->id);
            tmp.isfunc = 1;
            this_scope = insert(this_scope, tmp);

            free(tmp.type);
            tmp.def = 0;
            tmp.isfunc = 0;
        }
        // printf("%s\n", tmp.name);
        free(tmp.name);
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

        // printf("variable name: %s\n", $2->child->child->child->id);
        if(!flgArr) { // 不是数组
            tmp.name = (char*)malloc(sizeof($2->child->child->child->id));
            strcpy(tmp.name, $2->child->child->child->id);
        }
        else { // 是数组
            tmp.name = (char*)malloc(sizeof($2->child->child->child->child->id));
            strcpy(tmp.name, $2->child->child->child->child->id);
        }
        // tmp.name = (char*)malloc(sizeof($2->child->child->child->id));
        // strcpy(tmp.name, $2->child->child->child->id);
        // printf("insert variable \'%s\'\n", tmp.name);
        if(search(this_scope, tmp)) { // 两种可能：struct xx {...} yy; 或 int a;
            char msg[100];
            if(!flgStruct) // 普通变量声明
                sprintf(msg, "Error %d at line %d : Redefined variable \'%s\'", REDEFINED_VARIABLE, last_row, tmp.name);
            else // 结构体变量声明
                sprintf(msg, "Error %d at line %d : Redefined field \'%s\'", REDEFINED_FIELD, last_row, tmp.name);
            myerror(msg);
        }
        else {
            tmp.def = 1;
            if(flgStruct == 2) { // 是struct tag的情况，如struct sa nn;
                tmp.type = (char*)malloc(sizeof($1->child->child->id));
                // printf("%s\n", $1->child->child->id); // 应该是struct
                strcpy(tmp.type, $1->child->child->id);
            }
            else if(flgStruct == 1) { // 一般变量，如int a;
                tmp.type = (char*)malloc(sizeof($1->child->id));
                // printf("%s\n", $1->child->name);
                strcpy(tmp.type, $1->child->id);
                if(flgArr) { // 是数组
                    tmp.isarr = 1;
                    tmp.dimension = $2->child->child->bro->bro->intValue;
                    flgArr = 0;
                }
            }
            tmp.isvariable = 1;
            this_scope = insert(this_scope, tmp);
            
            free(tmp.type);
            tmp.def = 0;
            tmp.isvariable = 0;
            tmp.isarr = 0;
            tmp.dimension = 0;
        }
        free(tmp.name);
        flgStruct = 0;
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
        // \begin{jcy 5} record the type of Exp and assign to Dec 用于与后面Specifier进行比较
        
        // \end{jcy 5}
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
		// why noted ?  -- by jcy
        // tmp.name = (char*)malloc(sizeof($1->child->id));
        // strcpy(tmp.name, $1->child->id);
        // if(search(this_scope, tmp)) {
        //     char msg[100];
        //     sprintf(msg, "Error %d at line %d : Redefined variable \'%s\'", REDEFINED_VARIABLE, last_row, tmp.name);
        //     myerror(msg);
        // }
        // else {
        //     printf("insert array \'%s\'\n", tmp.name);
        //     tmp.def = 1;
        //     // tmp.type = (char*)malloc(sizeof($1->child->id));
        //     // strcpy(tmp.type, $1->child->id);
        //     tmp.isarr = 1;
        //     tmp.dimension = $1->bro->bro->intValue;
        //     this_scope = insert(this_scope, tmp);

        //     free(tmp.type);
        //     tmp.def = 0;
        //     tmp.isarr = 0;
        //     tmp.dimension = 0;
        // }
        // free(tmp.name);
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
        //	\begin{jcy 5}
        //获取两个Exp的类型，进行一致性的判断即可，需要完成变量属性的传递（注意别的Exp产生式中这一步的维护）并完成这里类别的获取
        
        //	\end{jcy 5}
    }
	| Exp ASSIGNOP error { 
		char msg[100];
        sprintf(msg, "Syntax error."); // ASSIGNOP not in front of Exp
        // fprintf(stderr, "Error type B at line %d: %s\n", yylineno, msg);
		// errors++;
		myerror(msg);
	}
	// jcy 6 priority order ? (INT or FLOAT -> Exp)    **be good for use** but conflict
    | INT ASSIGNOP Exp {
    	char msg[100];
        sprintf(msg, "Error %d at line %d : The left-hand side of assignment must be a variable", NEED_VARIABLE, last_row); 
		myerror(msg);
    }
    | FLOAT ASSIGNOP Exp {
		char msg[100];
        sprintf(msg, "Error %d at line %d : The left-hand side of assignment must be a variable", NEED_VARIABLE, last_row); 
		myerror(msg);
	}
    // jcy 6
    // \beign{jcy 7}
    | Exp AND Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        if($1->name == $3->name) $$->name = $1->name;
        else{
        	char msg[100];
            sprintf(msg, "Error %d at line %d : Type mismatched for oprands", TYPE_MISMATCH_OPERAND, last_row);
            myerror(msg);
        }
    }
    | Exp OR Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        if($1->name == $3->name) $$->name = $1->name;
        else{
        	char msg[100];
            sprintf(msg, "Error %d at line %d : Type mismatched for oprands", TYPE_MISMATCH_OPERAND, last_row);
            myerror(msg);
        }
    }
    | Exp RELOP Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        if($1->name == $3->name) $$->name = $1->name;
        else{
        	char msg[100];
            sprintf(msg, "Error %d at line %d : Type mismatched for oprands", TYPE_MISMATCH_OPERAND, last_row);
            myerror(msg);
        }
    }
    | Exp PLUS Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        if($1->name == $3->name) $$->name = $1->name;
        else{
        	char msg[100];
            sprintf(msg, "Error %d at line %d : Type mismatched for oprands", TYPE_MISMATCH_OPERAND, last_row);
            myerror(msg);
        }
    }
    | Exp MINUS Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        if($1->name == $3->name) $$->name = $1->name;
        else{
        	char msg[100];
            sprintf(msg, "Error %d at line %d : Type mismatched for oprands", TYPE_MISMATCH_OPERAND, last_row);
            myerror(msg);
        }
    }
    | Exp STAR Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        if($1->name == $3->name) $$->name = $1->name;
        else{
        	char msg[100];
            sprintf(msg, "Error %d at line %d : Type mismatched for oprands", TYPE_MISMATCH_OPERAND, last_row);
            myerror(msg);
        }
    }
    | Exp DIV Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        if($1->name == $3->name) $$->name = $1->name;
        else{
        	char msg[100];
            sprintf(msg, "Error %d at line %d : Type mismatched for oprands", TYPE_MISMATCH_OPERAND, last_row);
            myerror(msg);
        }
    }
    // \end{jcy 7}
    | LP Exp RP {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        $$->name = $2->name;
        //加一步Exp类型的传递
    }
    | MINUS Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $$->name = $2->name;
    }
    | NOT Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $$->name = $2->name;
    }
    | ID LP Args RP {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        $3->bro = $4;
		// to be continued...
        tmp.name = (char*)malloc(sizeof($1->id));
        strcpy(tmp.name, $1->id);
        if(search(this_scope, tmp)) { 
            tmp.def = 1;
            // tmp.type = $1->type;	这些地方是否还需要加一个函数参数是否符合的判定，并且把函数返回类型赋给Exp	// to be continued
            // my_insert(&mytree, tmp);
            this_scope = insert(this_scope, tmp);
        }
        else { // 函数未定义
            char msg[100];
            sprintf(msg, "Error %d at line %d : Undefined function \'%s\'", UNDEFINED_FUNCTION, last_row, tmp.name);
            myerror(msg);
        }
    }
    | ID LP RP {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
		// to be continued ...
        tmp.name = (char*)malloc(sizeof($1->id));
        strcpy(tmp.name, $1->id);
        if(search(this_scope, tmp)) { 
            tmp.def = 1;
            // tmp.type = $1->type;	这些地方是否还需要加一个函数参数是否符合的判定，并且把函数返回类型赋给Exp	// to be continued
            // my_insert(&mytree, tmp);
            this_scope = insert(this_scope, tmp);
        }
        else { // 函数未定义
            char msg[100];
            sprintf(msg, "Error %d at line %d : Undefined function \'%s\'", UNDEFINED_FUNCTION, last_row, tmp.name);
            myerror(msg);
        }
    }
    | Exp LB Exp RB {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        $3->bro = $4;
        // \begin{jcy 10}
        //一个$1是否为数组变量的检查，一个$3是否为整数的检查（忽略段错误）
        // 类型传递
        // \end{jcy 10}
    }
	| Exp DOT ID { // 结构体
		$$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
		$1->bro = $2;
		$2->bro = $3;
		//	\begin{jcy 13}
        tmp.name = (char*)malloc(sizeof($1->id));	//不一定对，我搞不清楚往下走几层能获取到我想要的正确信息
        strcpy(tmp.name, $1->id);
        if(search(this_scope, tmp)) { //先获取这个名字的东西，然后看看它是不是结构体：如果不是结构体，则判为错误13；若是结构体，开始看ID是否存在：如果ID存在，将其属性赋给规约后的结果；若ID不存在，则判为错误14
            tmp.def = 1;
            // tmp.type = $1->type;
            // my_insert(&mytree, tmp);
            this_scope = insert(this_scope, tmp);
        }
        else { // 函数未定义
            char msg[100];
            sprintf(msg, "Error %d at line %d : Undefined function \'%s\'", UNDEFINED_FUNCTION, last_row, tmp.name);
            myerror(msg);
        }
        //	\end{jcy 13}
	}
	| ID {
		$$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        tmp.name = (char*)malloc(sizeof($1->id));
        strcpy(tmp.name, $1->id);
        if(search(this_scope, tmp)) { 
        	
            tmp.def = 1;
            // tmp.type = $1->type;
            // my_insert(&mytree, tmp);
            this_scope = insert(this_scope, tmp);
        }
        else { // 变量未定义
            char msg[100];
            sprintf(msg, "Error %d at line %d : Undefined variable \'%s\'", UNDEFINED_VARIABLE, last_row, tmp.name);
            myerror(msg);
        }
	}
	| INT {
		$$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
		//tmp.type = (char*)malloc(sizeof($1->name));
        //strcpy(tmp.type, $1->name);
        $$->name = "INT";
		//printf("int value = %d\n", $1->intValue);
		//this_scope = insert(this_scope, tmp);
		//free(tmp.type);
	}
	| FLOAT {
		$$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
		$$->name = "FLOAT";
		//printf("float value = %f\n", $1->floatValue);			似乎不起作用
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
