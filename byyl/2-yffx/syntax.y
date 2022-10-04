%{
	#include<stdio.h>
	#include <stdlib.h>
	void yyerror(char*);
	int yylex();
%}

%token INT
%token FLOAT
%token TYPE
%token LF
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

%right ASSIGNOP
%left OR
%left AND
%nonassoc RELOP
%left PLUS MINUS
%left STAR DIV
%right NAGATE NOT
%right DOT LP LB RP RB
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
Calc : /* empty */
	| Exp {printf("= %d\n", $1); }
	;
Exp : Factor
	| Exp PLUS Factor {$$ = $1 + $3; }
	| Exp MINUS Factor {$$ = $1 - $3; }
	;
Factor : Term
	| Factor STAR Term {$$ = $1 * $3; }
	| Factor DIV Term {$$ = $1 / $3; }
	;
Term : INT
	;
%%
#include "lex.yy.c"
int main(int argc, char** argv)
{
	if(argc <= 1) return 1;
	FILE* f = fopen(argv[1], "r");
	if(!f){
		perror(argv[1]);
		return 1;
	}
	yyrestart(f);
	yyparse();
	return 0;
}
void yyerror(char *msg)
{
    fprintf(stderr, "Error type B at Line %d: %s\n", yylineno,  msg);
}


