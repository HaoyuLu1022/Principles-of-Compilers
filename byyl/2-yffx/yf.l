%{
	#include "syntax.tab.h"
	extern int errors;
	int chars = 1;
	int cols = 1;

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
	struct node *newnode = iniNode("COMMA", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return COMMA;
}
{DOT} {
	struct node *newnode = iniNode("DOT", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return DOT;
}
{NOT} {
	struct node *newnode = iniNode("NOT", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return NOT;
}
{FLOAT} {
	struct node *newnode = iniNode("FLOAT", 0, FLOAT_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return FLOAT;
}
{ERRORFLOAT} {printf("Error Type A at line %d, char %d: Illegal float number: '%s'\n", yylineno, chars, yytext); chars += yyleng;}
{INT8} {printf("INT8 data at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{ERRORINT8} {printf("Error Type A at line %d, char %d: Illegal octal number: '%s'\n", yylineno, chars, yytext); chars += yyleng;}
{INT16} {printf("INT16 data at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{ERRORINT16} {printf("Error Type A at line %d, char %d: Illegal hexadecimal number: '%s'\n", yylineno, chars, yytext); chars += yyleng;}
{INT} {
	struct node *newnode = iniNode("INT", 0, INT_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return INT;
}
{PLUS} {
	struct node *newnode = iniNode("PLUS", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return PLUS;
}
{ASSIGNOP} {
	struct node *newnode = iniNode("ASSIGNOP", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return ASSIGNOP;
}
{RELOP} {
	struct node *newnode = iniNode("RELOP", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return RELOP;
}
{TYPE} {
	struct node *newnode = iniNode("TYPE", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return TYPE;
}
{RETURN} {
	struct node *newnode = iniNode("RETURN", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return RETURN;
}
{IF} {
	struct node *newnode = iniNode("IF", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return IF;
}
{ELSE} {
	struct node *newnode = iniNode("ELSE", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return ELSE;
}
{WHILE} {
	struct node *newnode = iniNode("WHILE", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return WHILE;
}
{STRUCT} {
	struct node *newnode = iniNode("STRUCT", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return STRUCT;
}
{AND} {
	struct node *newnode = iniNode("AND", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return AND;
}
{OR} {
	struct node *newnode = iniNode("OR", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return OR;
}
{STAR} {
	struct node *newnode = iniNode("STAR", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return STAR;
}
{MINUS} {
	struct node *newnode = iniNode("MINUS", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return MINUS;
}
{DIV} {
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
	struct node *newnode = iniNode("LP", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return LP;
}
{RP} {
	struct node *newnode = iniNode("RP", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return RP;
}
{LB} {
	struct node *newnode = iniNode("LB", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return LB;
}
{RB} {
	struct node *newnode = iniNode("RB", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return RB;
}
{LC} {
	struct node *newnode = iniNode("LC", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return LC;
}
{RC} {
	struct node *newnode = iniNode("RC", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return RC;
}
{SEMI} {
	struct node *newnode = iniNode("SEMI", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return SEMI;
}
{ID} {
	struct node *newnode = iniNode("ID", 0, STRING_TYPE);
	yylval = newnode;
	newnode->id = strdup(yytext);
	return ID;
} 
{WHITESPACE} {chars += 1;}
{TAB} {chars += 4;}
. {
	errors++;
	printf("ERROR Type A at line %d, char %d: Mysterious character: '%s'\n", yylineno, chars, yytext);
	chars += yyleng;
	}

