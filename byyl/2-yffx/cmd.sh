flex yf.l
bison -d syntax.y --debug
gcc syntax.tab.c SyntaxTree.c -lfl -ly -o parser
