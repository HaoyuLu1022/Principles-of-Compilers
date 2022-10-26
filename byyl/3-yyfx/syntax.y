%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "SyntaxTree.h"
    #include "RBTtest.c"

	#define YYSTYPE struct node*

	void yyerror(char*);
	void myerror(char*);
	int yylex();
	extern int yylineno;
	extern int last_row;
	int errors = 0;
    int yydebug = 1;
    struct rb_root mytree = RB_ROOT;
    MyType tmp;
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
        tmp.name = (char*)malloc(sizeof($2->child->child->id));
        strcpy(tmp.name, $2->child->child->id);
        if(my_search(&mytree, tmp)){
            char msg[100];
            sprintf(msg, "Redeined variable : %s, line: %d", tmp.name, last_row);
            myerror(msg);
        }
        else{
            tmp.def = 1;
            tmp.type = $2->child->child->type;
            my_insert(&mytree, tmp);
        }
        // my_insert(&mytree, tmp);
    }
    | Specifier SEMI {
        $$ = insNode($1, "ExtDef", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
    }
    | Specifier FunDec CompSt {
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
    }
    | STRUCT Tag {
        $$ = insNode($1, "StructSpecifier", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
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
    }
    | ID LP RP {
        $$ = insNode($1, "FunDec", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
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
	| Stmt Mid{
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
	}/*
	| {
	
	}*/
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
	}/*
	Stmt Stmt {
	
	}
	Def {
	
	}*/
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
    }/*
    | {
    
    }*/
    /*
    | DefList {
    
    } */
    
    /*
	| error Stmt {
        char msg[100];
		sprintf(msg, "Syntax error."); // Missing IF in front.
		myerror(msg);
    } */
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
    }
	| Exp ASSIGNOP error{ 
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
    }
    | Exp OR Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
    }
    | Exp RELOP Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
    }
    | Exp PLUS Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
    }
    | Exp MINUS Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
    }
    | Exp STAR Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
    }
    | Exp DIV Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
    }
    | LP Exp RP {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
    }
    | MINUS Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
    }
    | NOT Exp {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
    }
    | ID LP Args RP {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        $3->bro = $4;
    }
    | ID LP RP {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
    }
    | Exp LB Exp RB {
        $$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
        $1->bro = $2;
        $2->bro = $3;
        $3->bro = $4;
    }
	// | Exp LB Exp error{
	// 	char msg[100];
    //     sprintf(msg, "Missing \"]\".");
    //     // fprintf(stderr, "Error type B at line %d: %s\n", yylineno, msg);
	// 	// errors++;
	// 	myerror(msg);
	// }
	| Exp DOT ID {
		$$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
		$1->bro = $2;
		$2->bro = $3;
	}
	| ID {
		$$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
	}
	| INT {
		$$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
	}
	| FLOAT {
		$$ = insNode($1, "Exp", @1.first_line, NON_TERMINAL);
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
#include "lex.yy.c"

int main(int argc, char** argv) {
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
