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
NOTE "//note"
BRACKET "("|")"|"{"|"}"
SEMT ;
ID ({LETTER}|_)({LETTER}|_|{DIGIT})*
WHITESPACE [[:space:]]+
%%
%{
int chars = 1;
%}
\n {chars = 1; ++yylineno;}
({INT}|{INTT}) {printf("INT at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{PLUS} {printf("PLUS at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{ASSIGNOP} {printf("ASSIGNOP at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{RELOP} {printf("RELOP at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{TYPE} {printf("TYPE at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{KEYWORD} {printf("KEYWORD at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{AND} {printf("AND at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{MULTI} {printf("START at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{DIV} {printf("DIV at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{NOTE} {printf("NOTE at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{BRACKET} {printf("BRACKET at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{SEMT} {printf("SEMT at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{FLOAT} {printf("FLOAT at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{ID} {printf("ID at line %d, char %d: %s\n", yylineno, chars, yytext); chars += strlen(yytext);}
{WHITESPACE} {chars += strlen(yytext);}
. {printf("ERROR Type A at line %d, char %d: Myterious character: '%s'\n", yylineno, chars, yytext); chars += strlen(yytext);}
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
