#include <malloc.h>
#include "SyntaxTree.h"

struct node *iniNode(char *name, int lines, NODE_TYPE t) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->bro = NULL;
    newNode->child = NULL;
    newNode->lines = lines;
    newNode->type = t;
    newNode->name = name;
    if(!strcmp(newNode->name, "INT") || newNode->type == INT_TYPE)
        newNode->intValue = atoi(yytext);
    else if(!strcmp(newNode->name, "FLOAT")|| newNode->type == FLOAT_TYPE)
        newNode->type = atof(yytext);
    else newNode->intValue = 1;
    return newNode;
}

struct node *insNode(struct node *n, char *name, int lines, NODE_TYPE t) {
    struct node *parent = (struct node *)malloc(sizeof(struct node));
    parent->bro = NULL;
    parent->child = n;
    parent->lines = lines;
    parent->type = t;
    parent->name = strdup(name);
    parent->intValue = 1;
    head = parent;
    return parent;
}

void printNode(struct node *n, FILE *f, int depth) {
    if(n->type == STRING_TYPE) {
        fprintf(f, "%s : %s\n", n->name, n->id);
    }
    else if(n->type == INT_TYPE) {
        fprintf(f, "INT : %d\n", n->intValue);
    }
    else if(n->type == FLOAT_TYPE) {
        fprintf(f, "FLOAT : %f\n", n->floatValue);
    }
    else {
        // printf("%d\n", strcmp(n->name, "Mid"));
        if(strcmp(n->name, "Mid") == 0){
            // printf("Yes!!");
            fprintf(f, "Empty : Empty\n");
            if (n->child != NULL && strcmp(n->child->name, "Stmt") == 0){
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
            fprintf(f, "%s (%d)\n", n->name, n->lines);
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
