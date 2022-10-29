#include <malloc.h>
#include "SyntaxTree.hpp"
// #include "lex.yy.cc"

struct node *head;

struct node *iniNode(std::string name, int lines, NODE_TYPE t) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->bro = NULL;
    newNode->child = NULL;
    newNode->lines = lines;
    newNode->type = t;
    newNode->name = name;
    // if((!strcmp(newNode->name, "ID"))||(!strcmp(newNode->name, "TYPE"))) {
    //     char *tmp;
    //     tmp = (char *)malloc(sizeof(char *)*10);
    //     strcpy(tmp, yytext);
    //     newNode->type = tmp;
    // }
    if(newNode->name == "INT" || newNode->type == INT_TYPE)
        newNode->intValue = atoi(yytext);
    else if(newNode->name == "FLOAT" || newNode->type == FLOAT_TYPE)
        newNode->type = atof(yytext);
    else newNode->intValue = 1;
    return newNode;
}

struct node *insNode(struct node *n, std::string name, int lines, NODE_TYPE t) {
    struct node *parent = (struct node *)malloc(sizeof(struct node));
    parent->bro = NULL;
    parent->child = n;
    parent->lines = lines;
    parent->type = t;
    parent->name = name;
    parent->intValue = 1;
    head = parent;
    return parent;
}

void printNode(struct node *n, FILE *f, int depth) {
    if(n->type == STRING_TYPE) {
        fprintf(f, "%s : %s\n", n->name.c_str(), n->id.c_str());
    }
    else if(n->type == INT_TYPE) {
        fprintf(f, "INT : %d\n", n->intValue);
    }
    else if(n->type == FLOAT_TYPE) {
        fprintf(f, "FLOAT : %f\n", n->floatValue);
    }
    else {
        // printf("%d\n", strcmp(n->name, "Mid"));
        if(n->name == "Mid"){
            // printf("Yes!!");
            fprintf(f, "Empty : Empty\n");
            if (n->child != NULL && n->child->name == "Stmt") {
                for(int i = 0; i < depth; i++) {
                    fprintf(f, "\t");
                }
                fprintf(f, "StmtList (%d)\n", n->lines);
            }
            else if(n->child != NULL){
                for(int i = 0; i < depth; i++) {
                    fprintf(f, "\t");
                }
                fprintf(f, "DefList (%d)\n", n->lines);
            }
        }
        else
            fprintf(f, "%s (%d)\n", n->name.c_str(), n->lines);
    }
}

void printTree(struct node *head, int depth, FILE *f) {
    if(head == NULL) return;
    for(int i = 0; i < depth; i++) {
        fprintf(f, "\t");
    }
    printNode(head, f, depth);
    printTree(head->child, depth+1, f);
    printTree(head->bro, depth, f);
}
