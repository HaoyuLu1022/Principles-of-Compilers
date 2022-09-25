%option noyywrap c++ yylineno debug
%{
    #include <stack>
    std::stack<char*> st;
    int chars = 1;
%}
DIGIT [0-9]
INT 0|[1-9]{DIGIT}*
PLUS \+
MINUS -
STAR \*
ASSIGNOP = 
RELOP ==|<|>|>=|<=|!=
LETTER [a-zA-Z]
ERRORDIGITSTR {DIGIT}*{LETTER}[0-9a-zA-Z]*
INTT ({PLUS}|{MINUS})?{INT}
INT8 ({PLUS}|{MINUS})?0[0-7]+
ERRORINT8 ({PLUS}|{MINUS})?0([89a-wyzA-WYZ][0-9a-zA-Z]*|[0-7]+[89a-zA-Z][0-9a-zA-Z]*)
INT16 ({PLUS}|{MINUS})?0(x|X)[0-9a-fA-F]+
ERRORINT16 ({PLUS}|{MINUS})?0(x|X)[0-9a-fA-F]*[g-zG-Z][0-9a-zA-Z]*
FLOAT ({PLUS}|{MINUS})?({DIGIT}+\.{DIGIT}*|{DIGIT}*\.{DIGIT}+)
FLOATT ({PLUS}|{MINUS})?({DIGIT}+|{FLOAT})(e|E)({MINUS}|{PLUS})?{DIGIT}+
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
    printf("COMMA at line %d, char %d: %s\n", yylineno, chars, yytext);
    chars += yyleng;
    while(!st.empty())
        st.pop();}
{DOT} {
    printf("DOT at line %d, char %d: %s\n", yylineno, chars, yytext);
    chars += yyleng;}
{NOT} {
    printf("NOT at line %d, char %d: %s\n", yylineno, chars, yytext);
    chars += yyleng;}
({FLOAT}|{FLOATT}) {
    if(st.empty()) {
        printf("FLOAT at line %d, char %d: %s\n", yylineno, chars, yytext);
        st.push(yytext);
    }
    else {
        if(yytext[0] == '+' || yytext[0] == '-') {
            st.pop();
            yytext[0] == '+' ? printf("PLUS") : printf("MINUS");
            st.push(yytext);
            printf(" at line %d, char %d: %c\n", yylineno, chars, yytext[0]);
            printf("FLOAT at line %d, char %d: %s\n", yylineno, chars+1, yytext+1);
        }
        else {
            while(!st.empty()) st.pop();
			st.push(yytext);
			printf("FLOAT at line %d, char %d: %s\n", yylineno, chars, yytext);
        }
    }
    chars += yyleng;}
{ERRORFLOAT} {
    printf("Error Type A at line %d, char %d: Illegal float number: '%s'\n", yylineno, chars, yytext);
    chars += yyleng;}
{INT8} {
    if(st.empty()) {
        printf("INT8 at line %d, char %d: %s\n", yylineno, chars, yytext);
        st.push(yytext);
    }
    else {
        if(yytext[0] == '+' || yytext[0] == '-') {
            st.pop();
            yytext[0] == '+' ? printf("PLUS") : printf("MINUS");
            st.push(yytext);
            printf(" at line %d, char %d: %c\n", yylineno, chars, yytext[0]);
            printf("INT8 at line %d, char %d: %s\n", yylineno, chars+1, yytext+1);
        }
        else {
            while(!st.empty()) st.pop();
			st.push(yytext);
			printf("INT8 at line %d, char %d: %s\n", yylineno, chars, yytext);
        }
    }
    chars += yyleng;}
{ERRORINT8} {
    printf("Error Type A at line %d, char %d: Illegal octal number: '%s'\n", yylineno, chars, yytext);
    chars += yyleng;}
{INT16} {
    if(st.empty()) {
        printf("INT16 at line %d, char %d: %s\n", yylineno, chars, yytext);
        st.push(yytext);
    }
    else {
        if(yytext[0] == '+' || yytext[0] == '-') {
            st.pop();
            yytext[0] == '+' ? printf("PLUS") : printf("MINUS");
            st.push(yytext);
            printf(" at line %d, char %d: %c\n", yylineno, chars, yytext[0]);
            printf("INT16 at line %d, char %d: %s\n", yylineno, chars+1, yytext+1);
        }
        else {
            while(!st.empty()) st.pop();
			st.push(yytext);
			printf("INT16 at line %d, char %d: %s\n", yylineno, chars, yytext);
        }
    }
    chars += yyleng;}
{ERRORINT16} {
    printf("Error Type A at line %d, char %d: Illegal hexadecimal number: '%s'\n", yylineno, chars, yytext);
    chars += yyleng;}
({INT}|{INTT}) {
    if(st.empty()) {
        printf("INT at line %d, char %d: %s\n", yylineno, chars, yytext);
        st.push(yytext);
    }
    else {
        if(yytext[0] == '+' || yytext[0] == '-') {
            st.pop();
            yytext[0] == '+' ? printf("PLUS") : printf("MINUS");
            st.push(yytext);
            printf(" at line %d, char %d: %c\n", yylineno, chars, yytext[0]);
            printf("INT at line %d, char %d: %s\n", yylineno, chars+1, yytext+1);
        }
        else {
            while(!st.empty()) st.pop();
			st.push(yytext);
			printf("INT at line %d, char %d: %s\n", yylineno, chars, yytext);
        }
    }
    chars += yyleng;}
{PLUS} {
    printf("PLUS at line %d, char %d: %s\n", yylineno, chars, yytext);
    chars += yyleng;}
{ASSIGNOP} {
    printf("ASSIGNOP at line %d, char %d: %s\n", yylineno, chars, yytext);
    chars += yyleng;}
{RELOP} {
    printf("RELOP at line %d, char %d: %s\n", yylineno, chars, yytext);
    chars += yyleng;}
{TYPE} {
    printf("TYPE at line %d, char %d: %s\n", yylineno, chars, yytext);
    chars += yyleng;}
({IF}|{ELSE}|{WHILE}|{RETURN}) {
    printf("KEYWORD at line %d, char %d: %s\n", yylineno, chars, yytext);
    chars += yyleng;}
{STRUCT} {
    printf("STRUCT at line %d, char %d: %s\n", yylineno, chars, yytext);
    chars += yyleng;}
{AND} {
    printf("AND at line %d, char %d: %s\n", yylineno, chars, yytext);
    chars += yyleng;}
{OR} {
    printf("OR at line %d, char %d: %s\n", yylineno, chars, yytext);
    chars += yyleng;}
{STAR} {
    printf("START at line %d, char %d: %s\n", yylineno, chars, yytext);
    chars += yyleng;}
{MINUS} {
    printf("MINUS at line %d, char %d: %s\n", yylineno, chars, yytext);
    chars += yyleng;}
{DIV} {
    printf("DIV at line %d, char %d: %s\n", yylineno, chars, yytext);
    chars += yyleng;}
{NOTE} {
    printf("NOTE at line %d, char %d: %s\n", yylineno, chars, yytext);
    chars += yyleng;} 
{NOTEE} {printf("NOTE at line %d, char %d: %s\n", yylineno, chars, yytext); 
    int idx = yyleng - 1; 
    for(; (idx >= 0) && (yytext[idx] != '\n');) 
        idx--; 
    if(idx >= 0) 
        chars = 1; 
    chars += (yyleng - idx - 1); } 
({LP}|{RP}|{LB}|{RB}|{LC}|{RC}) {
    printf("BRACKET at line %d, char %d: %s\n", yylineno, chars, yytext); 
    chars += yyleng;}
{SEMI} {
    printf("SEMI at line %d, char %d: %s\n", yylineno, chars, yytext);
    chars += yyleng;}
{ID} {
    printf("ID at line %d, char %d: %s\n", yylineno, chars, yytext);
    chars += yyleng;} 
{WHITESPACE} {chars += yyleng;}
{TAB} {chars += 4;}
. {
    printf("ERROR Type A at line %d, char %d: Mysterious character: '%s'\n", yylineno, chars, yytext);
    chars += yyleng;}
%%
// This include is required if main() is an another source file.
//#include <FlexLexer.h>
#include <fstream>
using namespace std;
int main(int argc, char* argv[]) {
    if(argc > 1) {
        string filename = argv[1];
        ifstream ifs(filename);
        FlexLexer* lexer = new yyFlexLexer(&ifs);
        while(lexer->yylex() != 0);
    }
    return 0;
}