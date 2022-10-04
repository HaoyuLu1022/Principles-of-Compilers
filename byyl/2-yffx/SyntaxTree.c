#include <malloc.h>
#include <stdio.h>
#include "SyntaxTree.h"

struct node *iniNode(char *name, int lines, NODE_TYPE t) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->bro = NULL;
    newNode->child = NULL;
    newNode->lines = lines;
    newNode->type = t;
    newNode->name = strdup(name);
    newNode->intValue = 1;
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

void printNode(struct node *n, FILE *f) {
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
        fprintf(f, "%s (%d)\n", n->name, n->lines);
    }
}

void printTree(struct node *head, int depth, FILE *f) {
    if(head == NULL) return;
    for(int i = 0; i < depth; i++) {
        fprintf(f, "\t");
    }
    printNode(head, f);
    printTree(head->child, depth+1, f);
    printTree(head->bro, depth, f);
}