flex yf.l
bison -d syntax.y
gcc syntax.tab.c SyntaxTree.c rbtree.c ir.c -lfl -o compiler
./compiler test2.cmm out.ir
