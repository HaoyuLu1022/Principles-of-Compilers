flex yf.l
bison -d syntax.y
gcc syntax.tab.c SyntaxTree.c rbtree.c ir.c asm.c -lfl -o compiler
./compiler test1.cmm out.s
