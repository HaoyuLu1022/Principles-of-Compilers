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
%{
	#include "syntax.tab.h"
	
	int chars = 1;
	
%}
%%
{NEWLINE} {chars = 1;}
{COMMA} {
	return COMMA;
}
{DOT} {
	return DOT;
}
{NOT} {
	return NOT;
}
({FLOAT}|{FLOATT}) {
	return FLOAT;
}
{ERRORFLOAT} {printf("Error Type A at line %d, char %d: Illegal float number: '%s'\n", yylineno, chars, yytext); chars += yyleng;}
{INT8} {printf("INT8 data at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{ERRORINT8} {printf("Error Type A at line %d, char %d: Illegal octal number: '%s'\n", yylineno, chars, yytext); chars += yyleng;}
{INT16} {printf("INT16 data at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{ERRORINT16} {printf("Error Type A at line %d, char %d: Illegal hexadecimal number: '%s'\n", yylineno, chars, yytext); chars += yyleng;}
{INT} {
	return INT;
}
{PLUS} {
	return PLUS;
}
{ASSIGNOP} {
	return ASSIGNOP;
}
{RELOP} {
	return RELOP;
}
{TYPE} {
	return TYPE;
}
{RETURN} {
	return RETURN;
}
{IF} {
	return IF;
}
{ELSE} {
	return ELSE;
}
{WHILE} {
	return WHILE;
}

{STRUCT} {
	return STRUCT;
}
{AND} {
	return AND;
}
{OR} {
	return OR;
}
{STAR} {
	return STAR;
}
{MINUS} {
	return MINUS;
}
{DIV} {
	return DIV;
}
{NOTE} {
	// pass
} 
{NOTEE} {
	// pass
} 

{LP} {
	return LP;
}
{RP} {
	return RP;
}
{LB} {
	return LB;
}
{RB} {
	return RB;
}
{LC} {
	return LC;
}
{RC} {
	return RC;
}
{SEMI} {
	return SEMI;
}
{ID} {
	return ID;
} 
{WHITESPACE} {chars += 1;}
{TAB} {chars += 4;}
. {printf("ERROR Type A at line %d, char %d: Mysterious character: '%s'\n", yylineno, chars, yytext); chars += yyleng;}

