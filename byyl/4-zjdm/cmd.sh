flex yf.l
bison -d syntax.y --debug
gcc syntax.tab.c SyntaxTree.c rbtree.c -lfl -ly -o parser
