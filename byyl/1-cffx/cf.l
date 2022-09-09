%option yylineno
DIGIT [0-9]
INT [0-9]{DIGIT}*
INTT ("+"|"-")?{INT}
FLOAT {INT}(.{INTT})
LETTER [a-zA-Z]
PLUS \+
MULTI \*
ASSIGNOP =
RELOP "=="|"<"|">"
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
\n {++yylineno;}
({INT}|{INTT}) {printf("INT at line %d: %s\n", yylineno, yytext);}
{PLUS} {printf("PLUS at line %d: %s\n", yylineno, yytext);}
{ASSIGNOP} {printf("ASSIGNOP at line %d: %s\n", yylineno, yytext);}
{TYPE} {printf("TYPE at line %d: %s\n", yylineno, yytext);}
{KEYWORD} {printf("KEYWORD at line %d: %s\n", yylineno, yytext);}
{AND} {printf("AND at line %d: %s\n", yylineno, yytext);}
{MULTI} {printf("START at line %d: %s\n", yylineno, yytext);}
{DIV} {printf("DIV at line %d: %s\n", yylineno, yytext);}
{NOTE} {printf("NOTE at line %d: %s\n", yylineno, yytext);}
{BRACKET} {printf("BRACKET at line %d: %s\n", yylineno, yytext);}
{SEMT} {printf("SEMT at line %d: %s\n", yylineno, yytext);}
{FLOAT} {printf("FLOAT at line %d: %s\n", yylineno, yytext);}
{ID} {printf("ID at line %d: %s\n", yylineno, yytext);}
{WHITESPACE} {}
. {printf("ERROR Type A at line %d: %s\n", yylineno, yytext);}
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
