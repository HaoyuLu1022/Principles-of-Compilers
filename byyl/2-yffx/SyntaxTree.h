#include <string.h>
#include <stdio.h>
typedef int NODE_TYPE;
#define NON_TERMINAL 0
#define INT_TYPE 1
#define FLOAT_TYPE 2
#define STRING_TYPE 3

struct node {
    struct node *child;
    struct node *bro;
    int lines;
    char *name;
    NODE_TYPE type;
    union {
        char *id;
        int intValue;
        float floatValue;
    };
};

struct node *head;
struct node *iniNode(char *name, int lines, NODE_TYPE t);
struct node *insNode(struct node *n, char *name, int lines, NODE_TYPE t);
void printNode(struct node *n, FILE *f);
void printTree(struct node *head, int depth, FILE *f);
