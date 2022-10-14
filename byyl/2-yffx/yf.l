%{
	#include "syntax.tab.h"
	extern int errors;
	int chars = 1;
	int cols = 1;
	int last_row = 1;
	int this_row = 1;
	#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
        yylloc.first_column = cols; \
        yylloc.last_column = cols + yyleng - 1; \
        cols += yyleng;
%}
%option yylineno
DIGIT [0-9]
INT 0|[1-9]{DIGIT}*
PLUS \+
MINUS -
STAR \*
ASSIGNOP = 
RELOP ==|<|>|>=|<=|!=
LETTER [a-zA-Z]
ERRORDIGITSTR {DIGIT}*{LETTER}[0-9a-zA-Z]*
INT8 0[0-7]+
ERRORINT8 0([89a-wyzA-WYZ][0-9a-zA-Z]*|[0-7]+[89a-zA-Z][0-9a-zA-Z]*)
INT16 0(x|X)[0-9a-fA-F]+
ERRORINT16 0(x|X)[0-9a-fA-F]*[g-zG-Z][0-9a-zA-Z]*
FLOAT ({DIGIT}+\.{DIGIT}*|{DIGIT}*\.{DIGIT}+)
FLOATT ({DIGIT}+|{FLOAT})(e|E)({MINUS}|{PLUS})?{DIGIT}+
ERRORFLOAT ({DIGIT}+|{FLOAT})(e|E)({FLOAT}|{ERRORDIGITSTR})?
TYPE void|int|float|double|char
IF if
ELSE else
WHILE while
RETURN return
STRUCT struct
AND &&
OR "||"
DOT \.
NOT !
DIV "/"
NOTE "//".*
NOTEE "/*"([^"*/"]*)"*/"
LP "("
RP ")"
LB "["
RB "]"
LC "{"
RC "}"
SEMI ;
ID ({LETTER}|_)({LETTER}|_|{DIGIT})*
WHITESPACE (" "+)
TAB \t
NEWLINE \n
COMMA ,
%%
{NEWLINE} {chars = 1;}
{COMMA} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("COMMA", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return COMMA;
}
{DOT} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("DOT", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return DOT;
}
{NOT} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("NOT", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return NOT;
}
{FLOAT} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("FLOAT", 0, FLOAT_TYPE);
	yylval = newnode;
	// newnode->id = strdup(yytext);
	return FLOAT;
}
{ERRORFLOAT} {
	errors ++ ;
	last_row = this_row;
	this_row = yylineno;
	printf("Error Type A at line %d, char %d: Illegal float number: '%s'\n", yylineno, chars, yytext); chars += yyleng; 
	struct node *newnode = iniNode("FLOAT", 0, FLOAT_TYPE);
	yylval = newnode;
	// newnode->id = strdup(yytext);
	return FLOAT;
}
{ERRORINT8} {
	errors ++ ;
	last_row = this_row;
	this_row = yylineno;
	printf("Error Type A at line %d, char %d: Illegal octal number: '%s'\n", yylineno, chars, yytext); chars += yyleng;
	struct node *newnode = iniNode("INT", 0, INT_TYPE);
	yylval = newnode;
	// newnode->id = strdup(yytext);
	return INT;
}
{ERRORINT16} {
	errors ++ ;
	last_row = this_row;
	this_row = yylineno;
	printf("Error Type A at line %d, char %d: Illegal hexadecimal number: '%s'\n", yylineno, chars, yytext); chars += yyleng;
	struct node *newnode = iniNode("INT", 0, INT_TYPE);
	yylval = newnode;
	// newnode->id = strdup(yytext);
	return INT;
}
({INT}|{INT8}|{INT16}) {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("INT", 0, INT_TYPE);
	yylval = newnode;
	// newnode->id = strdup(yytext);
	return INT;
}
{PLUS} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("PLUS", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return PLUS;
}
{ASSIGNOP} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("ASSIGNOP", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return ASSIGNOP;
}
{RELOP} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("RELOP", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return RELOP;
}
{TYPE} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("TYPE", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return TYPE;
}
{RETURN} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("RETURN", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return RETURN;
}
{IF} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("IF", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return IF;
}
{ELSE} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("ELSE", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return ELSE;
}
{WHILE} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("WHILE", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return WHILE;
}
{STRUCT} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("STRUCT", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return STRUCT;
}
{AND} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("AND", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return AND;
}
{OR} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("OR", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return OR;
}
{STAR} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("STAR", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return STAR;
}
{MINUS} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("MINUS", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return MINUS;
}
{DIV} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("DIV", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return DIV;
}
{NOTE} {
	// pass
} 
{NOTEE} {
	// pass
} 

{LP} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("LP", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return LP;
}
{RP} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("RP", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return RP;
}
{LB} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("LB", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return LB;
}
{RB} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("RB", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return RB;
}
{LC} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("LC", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return LC;
}
{RC} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("RC", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return RC;
}
{SEMI} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("SEMI", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return SEMI;
}
{ID} {
	last_row = this_row;
	this_row = yylineno;
	struct node *newnode = iniNode("ID", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return ID;
} 
{WHITESPACE} {chars += 1;}
{TAB} {chars += 4;}
. {
	errors++;
	printf("Error Type A at line %d, char %d: Mysterious character: '%s'\n", yylineno, chars, yytext);
	chars += yyleng;
	}

