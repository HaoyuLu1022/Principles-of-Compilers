#include <malloc.h>
#include "SyntaxTree.h"


struct node *iniNode(char *name, int lines, NODE_TYPE t) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->bro = NULL;
    newNode->child = NULL;
    newNode->lines = lines;
    newNode->type = t;
    newNode->name = name;
    newNode->isStruct = 0;
	newNode->isArr = 0;
    if(!strcmp(newNode->name, "INT") || newNode->type == INT_TYPE) {
        newNode->intValue = atoi(yytext);
        strcpy(newNode->property, "int");
    }
        
    else if(!strcmp(newNode->name, "FLOAT") || newNode->type == FLOAT_TYPE) {
        newNode->type = atof(yytext);
        strcpy(newNode->property, "float");
    }
        
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
    parent->id = (char*)malloc(sizeof(parent->name));
    head = parent;
    return parent;
}

void printNode(struct node *n, FILE *f, int depth) {
    if(n->type == STRING_TYPE) {
        fprintf(f, "%s : %s\n", n->name, n->id);
    }
    else if(!strcmp(n->name, "INT")) { // n->type == INT_TYPE
        fprintf(f, "INT : %d\n", n->intValue);
    }
    else if(!strcmp(n->name, "FLOAT")) { // n->type == FLOAT_TYPE
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
int arr[100], cnt = 0, st = 0, ed = 0;

int searchTree(struct node* head, char* varName) {
	if(ed) return 0;
	int res = 0;
	// printf("yes%s %d\n", head->name, st);
	if(st && !strcmp(head->name, "LB")){
		// printf("here\n");
		arr[cnt++] = head->bro->intValue;
	}
	if(st && !strcmp(head->name, "SEMI")){
		// printf("there\n");
		st = 0;ed = 1;
		return res;
	}
	if(!head->child){
		if(head->bro)
			res |= searchTree(head->bro, varName);
			return res;
	}
	if(head->child->type == STRING_TYPE) {
		// printf("dxr %s %s\n", head->child->id, varName);
		if(!strcmp(head->child->id, varName)) {
			if(head->bro) {
				if(!strcmp(head->bro->name, "LB")){
					st = 1;
					if(head->bro)
						res |= searchTree(head->bro, varName);
					return 1; // 是数组
				}
				else{
					res |= searchTree(head->child, varName);
					if(head->bro)
						res |= searchTree(head->bro, varName);
					return res;
				}
			}
			else{
				// if(st && )
				
				res |= searchTree(head->child, varName);
				// printf("here\n");
				if(head->bro){
					// printf("%s\n", head->bro->name);
					res |= searchTree(head->bro, varName);
				}
				
				return res;
			}
		}
		else{
			res |= searchTree(head->child, varName);
			if(head->bro){
					// printf("%s\n", head->bro->name);
				res |= searchTree(head->bro, varName);
			}
			return res;
		}
	}
	else {
		res |= searchTree(head->child, varName);
		if(head->bro)
			res |= searchTree(head->bro, varName);
	}
	// printf("yes%s\n", head->child->name);
	return res;
}


