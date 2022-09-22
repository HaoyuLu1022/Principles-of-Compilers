%option yylineno
DIGIT [0-9]
INT 0|[1-9]{DIGIT}*
INTT ("+"|-)?{INT}
ERRORDIGITSTR [0-9]*[a-zA-Z][0-9a-zA-Z]*
INT8 ("+"|-)?0[0-7]+
ERRORINT8 ("+"|-)?0([89a-df-wyzA-DF-WYZ][0-9a-zA-Z]*|[0-7]+[89a-df-zA-DF-Z][0-9a-zA-Z]*)
INT16 ("+"|-)?0(x|X)[0-9a-fA-F]+
ERRORINT16 ("+"|-)?0(x|X)[0-9a-fA-F]*[g-zG-Z][0-9a-zA-Z]*
FLOAT ("+"|-)?([0-9]+\.[0-9]*|[0-9]*\.[0-9]+)
FLOATE ([0-9]+|{FLOAT})(e|E)(\+|-)?[0-9]+
ERRORFLOATE ([0-9]+|{FLOAT})(e|E)({FLOAT}|{ERRORDIGITSTR})?
LETTER [a-zA-Z]
PLUS \+
MINUS -
STAR \*
ASSIGNOP = 
RELOP ==|<|>|>=|<=|!=
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
DIV \/
NOTE \/\/.*
NOTEE \/\*(.|\n)*\*\/
LP "("
RP ")"
LB "["
RB "]"
LC "{"
RC "}"
SEMI ";"
ID ({LETTER}|_)({LETTER}|_|{DIGIT})*
WHITESPACE (" "+)
TAB \t
NEWLINE \n
COMMA ","
%{
int chars = 1;
%}
%%
{NEWLINE} {chars = 1;}
{COMMA} {printf("COMMA at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{DOT} {printf("DOT at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{NOT} {printf("NOT at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{INTT} {printf("INT data at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{INT8} {printf("INT8 data at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
({FLOAT}|{FLOATE}) {printf("FLOAT at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{ERRORFLOATE} {printf("Error Type A at line %d, char %d: Illgal float number: '%s'\n", yylineno, chars, yytext); chars += yyleng;}
{ERRORINT8} {printf("Error Type A at line %d, char %d: Illgal octal number: '%s'\n", yylineno, chars, yytext); chars += yyleng;}
{INT16} {printf("INT16 data at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{ERRORINT16} {printf("Error Type A at line %d, char %d: Illgal hexadecimal number: '%s'\n", yylineno, chars, yytext); chars += yyleng;}
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
{NOTEE} {printf("NOTE at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
({LP}|{RP}|{LB}|{RB}|{LC}|{RC}) {printf("BRACKET at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
{SEMI} {printf("SEMI at line %d, char %d: %s\n", yylineno, chars, yytext); chars += yyleng;}
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
