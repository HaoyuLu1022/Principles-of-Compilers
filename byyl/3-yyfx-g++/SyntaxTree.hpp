#pragma once

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <iostream> 

typedef int NODE_TYPE;
#define NON_TERMINAL 0
#define INT_TYPE 1
#define FLOAT_TYPE 2
#define STRING_TYPE 3
extern char *yytext;
extern int yylineno;

struct node {
    struct node *child;
    struct node *bro;
    int lines;
    std::string name;
    NODE_TYPE type;
    std::string id;
    int intValue;
    float floatValue;
};

extern struct node *head;
struct node *iniNode(std::string name, int lines, NODE_TYPE t);
struct node *insNode(struct node *n, std::string name, int lines, NODE_TYPE t);
void printNode(struct node *n, FILE *f, int depth);
void printTree(struct node *head, int depth, FILE *f);

