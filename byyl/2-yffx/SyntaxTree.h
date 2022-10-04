#pragma once

typedef int NODE_TYPE;

#define NONTERMINAL 0
#define INT_TYPE 1
#define FLOAT_TYPE 2
#define 

typedef union 
{
    char *_id;
    int *_int;
    float *_float;
}type;

typedef struct node {
    type data;
    long long line;
    struct node *l, *r;
}node;

node* Insert(struct node *nd, char *data, int line, )