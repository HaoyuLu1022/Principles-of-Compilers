flex -+ yf.ll
bison -d syntax.yy
g++ -std=c++14 SyntaxTree.cpp syntax.tab.cc -lfl -ly -o test