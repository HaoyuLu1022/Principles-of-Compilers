flex yf.l
bison -d syntax.y
gcc syntax.tab.c SyntaxTree.c -lfl -ly -o parser
