%option yylineno
DIGIT [0-9]
INT [0-9]{DIGIT}*
INTT ("+"|"-")?{INT}
FLOAT {INT}(.{INTT})
LETTER [a-zA-Z]
PLUS \+
MULTI \*
ASSIGNOP = 
RELOP "=="|"<"|">"|">="|"<="
TYPE void|int|float|double|char
KEYWORD if|else|while|do|for|return
AND &&
DIV "/"
NOTE "//".*
BRACKET "("|")"|"{"|"}"
SEMT ;
ID ({LETTER}|_)({LETTER}|_|{DIGIT})*
WHITESPACE [[:space:]]+
%{
#define T_WORD 1
int chars = 1, tmp = 1;
%}
%%
({INT}|{INTT}) {if(tmp != yylineno) {chars = 0; tmp = yylineno;} printf("INT at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{PLUS} {if(tmp != yylineno) {chars = 0; tmp = yylineno;} printf("PLUS at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{ASSIGNOP} {if(tmp != yylineno) {chars = 0; tmp = yylineno;} printf("ASSIGNOP at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{RELOP} {if(tmp != yylineno) {chars = 0; tmp = yylineno;} printf("RELOP at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{TYPE} {if(tmp != yylineno) {chars = 0; tmp = yylineno;} printf("TYPE at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{KEYWORD} {if(tmp != yylineno) {chars = 0; tmp = yylineno;} printf("KEYWORD at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{AND} {if(tmp != yylineno) {chars = 0; tmp = yylineno;} printf("AND at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{MULTI} {if(tmp != yylineno) {chars = 0; tmp = yylineno;} printf("START at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{DIV} {if(tmp != yylineno) {chars = 0; tmp = yylineno;} printf("DIV at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{NOTE} {if(tmp != yylineno) {chars = 0; tmp = yylineno;} printf("NOTE at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{BRACKET} {if(tmp != yylineno) {chars = 0; tmp = yylineno;} printf("BRACKET at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{SEMT} {if(tmp != yylineno) {chars = 0; tmp = yylineno;} printf("SEMT at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{FLOAT} {if(tmp != yylineno) {chars = 0; tmp = yylineno;} printf("FLOAT at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{ID} {if(tmp != yylineno) {chars = 0; tmp = yylineno;} printf("ID at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{WHITESPACE} {if(tmp != yylineno) {chars = 0; tmp = yylineno;} chars += strlen(yytext);}
. {if(tmp != yylineno) {chars = 0; tmp = yylineno;} printf("ERROR Type A at line %d, char %d: Myterious character: '%s'\n", yylineno, chars, yytext); chars += strlen(yytext);}
%%
int main(int argc, char* argv[]) {
    if (argc > 1) {
	if(!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
	    return 1;
	}
	while(yylex() != 0);
    }
    return 0;
}
