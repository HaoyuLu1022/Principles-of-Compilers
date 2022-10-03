flex yf.l
bison -d syntax.y
gcc syntax.tab.c -lfl -ly -o parser
