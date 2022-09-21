%option yylineno
DIGIT [0-9]
INT [0-9]{DIGIT}*
PLUS \+
MINUS -
STAR \*
ASSIGNOP = 
RELOP ==|<|>|>=|<=|!=
INTT ({PLUS}|{MINUS})?{INT}
FLOAT {INT}(\.{INTT})
LETTER [a-zA-Z]
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
int chars = 1;
%}
%%
{NEWLINE} {chars = 1;}
{COMMA} {printf("COMMA at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{DOT} {printf("DOT at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{NOT} {printf("NOT at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
({INT}|{INTT}) {printf("INT data at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{PLUS} {printf("PLUS at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{ASSIGNOP} {printf("ASSIGNOP at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{RELOP} {printf("RELOP at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{TYPE} {printf("TYPE at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
({IF}|{ELSE}|{WHILE}|{RETURN}) {printf("KEYWORD at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{STRUCT} {printf("STRUCT at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{AND} {printf("AND at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{OR} {printf("OR at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{STAR} {printf("START at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{MINUS} {printf("MINUS at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{DIV} {printf("DIV at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{NOTE} {printf("NOTE at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
({LP}|{RP}|{LB}|{RB}|{LC}|{RC}) {printf("BRACKET at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{SEMI} {printf("SEMI at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{FLOAT} {printf("FLOAT at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{ID} {printf("ID at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;} 
{WHITESPACE} {chars += yyleng;}
{TAB} {chars += 4;}
. {printf("ERROR Type A at line %d, char %d: Mysterious character: '%s'\n", yylineno, chars, yytext); chars += yyleng;}
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
