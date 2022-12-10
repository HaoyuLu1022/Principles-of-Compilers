#include "ir.h"

int t[100];		//存储临时变量，仅用于在程序中的立即数，其余变量直接用其原名
//int top = 1;	//用来指示变量名用到哪个位置了
int r = 1, BACK, flagif = 1;		//用来指示label的标签
int tcnt = 0;
char* tmp = "null";
int flagArr = 0, flagStruct = 0;
struct node* root;

char allStruct[20][20][20];    //20个不同的结构体，每个结构体最多包含19个不同名字，名字长度为20的变量
int cntStruct = 0;
int idxPara = 0;
int flagStructAssigned = 0;

extern int arr[100], cnt, st, ed;

int findNum(int n, FILE *f) {
	for(int i = 0; i <= 99; i ++ ) {
		if(t[i] == n) return i;
		else if(t[i] == 0 && i > 0) {
			fprintf(f, "t%d := #%d\n", i, n);
			t[i] = n;
			return i;
		}
	}
}

void translate_Program(struct node *head, FILE *f) {
	root = (struct node*)malloc(sizeof(head));
	root = head;
	translate_ExtDefList(head->child, f);
}

void translate_ExtDefList(struct node *head, FILE *f) {
	if(head->child == NULL) return;
	translate_ExtDef(head->child, f);
	translate_ExtDefList(head->child->bro, f);
}

void translate_ExtDef(struct node *head, FILE *f) {
	translate_Specifier(head->child, f);
	if(head->child->bro->bro != NULL) {
		if(!strcmp(head->child->bro->name, "ExtDecList")) {
			translate_ExtDecList(head->child->bro, f);
		}
		else if(!strcmp(head->child->bro->name, "FunDec")) {
			translate_FunDec(head->child->bro, f);				
			translate_CompSt(head->child->bro->bro, f);		
			fprintf(f, "\n");
		}
	}
}

void translate_Specifier(struct node *head, FILE *f) {
	if(!strcmp(head->child->name, "TYPE")) 
		translate_TYPE(head->child, f);		
	if(!strcmp(head->child->name, "StructSpecifier"))
		translate_StructSpecifier(head->child, f);
}

void translate_ExtDecList(struct node *head, FILE *f) {
	translate_VarDec(head->child, f);		//to be continued	考虑增加一个参数给此函数表示来源（变量声明是否为函数的参数）
	if(head->child->bro != NULL)
		translate_ExtDecList(head->child->bro->bro, f);
}

void translate_FunDec(struct node *head, FILE *f) { // FunDec: ID LP VarList RP
	fprintf(f, "FUNCTION %s :\n", head->child->id);
	if(!strcmp(head->child->bro->bro->name, "VarList")) 
		translate_VarList(head->child->bro->bro, f);	//to be continued	考虑增加一个参数表示来源（变量声明是否为函数的参数）
}

void translate_CompSt(struct node *head, FILE *f) {
	translate_Mid(head->child->bro, f);
}

void translate_TYPE(struct node *head, FILE *f) {
	//pass
}

void translate_StructSpecifier(struct node *head, FILE *f) {
	sprintf(allStruct[cntStruct][idxPara], "%s", head->child->bro->child->id); idxPara ++;
	//printf("tag1\n");
	struct node* newMid = head->child->bro->bro->bro;		// newMid始终指向Mid
	do {
		if(newMid->child) {
			if(!strcmp(newMid->child->name, "Def")) {
				struct node* newDecList = newMid->child->child->bro;		// newDecList始终指向DecList
				do {
					sprintf(allStruct[cntStruct][idxPara], "%s", newDecList->child->child->child->id); idxPara ++;
					if(newDecList->child->bro) {
						newDecList = newDecList->child->bro->bro;
					}
					else break;
				} while(newDecList->child);
			}
			newMid = newMid->child->bro;
		}
	} while(newMid->child);

	cntStruct += 1; idxPara = 0;
}

void translate_Mid(struct node *head, FILE *f) {
	if(head->child == NULL) return;
	else if(!strcmp(head->child->name, "Def")) {
		translate_Def(head->child, f);			
		translate_Mid(head->child->bro, f);
	}
	else if(!strcmp(head->child->name, "Stmt")) {
		translate_Stmt(head->child, f);				
		translate_Mid(head->child->bro, f);
	}
}

void translate_Def(struct node *head, FILE *f) {
	if(!strcmp(head->child->child->name, "StructSpecifier")) {
		int space = 0;		//用于准备给结构体分配空间
		int i, j;

		for(i = 0; i < cntStruct; i++) {
			if(!strcmp(allStruct[i][0], head->child->child->child->bro->child->id))
				break;
		}
		for(j = 1; j < 20; j++) {
			if(!strcmp(allStruct[i][j], ""))
				break;
		}
		space = (j-1) * 4;

		struct node* newDecList = head->child->bro;
		do {
			fprintf(f, "DEC %sobj %d\n", newDecList->child->child->child->id, space);
			fprintf(f, "%s := &%sobj\n", newDecList->child->child->child->id, newDecList->child->child->child->id);
			if(newDecList->child->bro) {
				newDecList = newDecList->child->bro->bro;
			}
			else break;
		} while(newDecList->child);
	}
	else {
		struct node* newnode = head->child->bro; // newnode始终指向DecList
		do {
			if(newnode->child->child->child->bro) {
				if(!strcmp(newnode->child->child->child->bro->name, "LB")) { // 说明是数组
					struct node* n = newnode->child->child->child; // n始终指向VarDec
					int space = 1;
					do {
						space *= n->bro->bro->intValue;
						// printf("%s\n", n->child->name);
						if(strcmp(n->name, "ID")) {
							n = n->child;
						}
						else {
							break;
						}
					} while(strcmp(n->name, "ID"));
					// printf("%s[%d]\n", n->id, space);
					fprintf(f, "DEC %s %d\n", n->id, space*4);
				}
			}
			else if(newnode->child->child->bro) {
				if(!strcmp(newnode->child->child->bro->name, "ASSIGNOP")) { // 声明变量且赋初值
					// printf("%s = %d\n", newnode->child->child->child->id, newnode->child->child->bro->bro->child->intValue);
					if(!strcmp(newnode->child->child->bro->bro->child->name, "INT")) {
						fprintf(f, "%s := #%d\n", newnode->child->child->child->id, newnode->child->child->bro->bro->child->intValue);
					}
					else if(!strcmp(newnode->child->child->bro->bro->child->name, "FLOAT")) {
						fprintf(f, "%s := #%f\n", newnode->child->child->child->id, newnode->child->child->bro->bro->child->floatValue);
					}
					else {
						fprintf(f, "%s := %s\n", newnode->child->child->child->id, newnode->child->child->bro->bro->child->id);
					}
				}
			}
			if(newnode->child->bro) {
				newnode = newnode->child->bro->bro;	
			}
			else {
				break;
			}
		} while(newnode); // 说明还有声明
	}
}

void translate_Stmt(struct node *head, FILE *f) {		//flag用来标记结尾是否需要再加一个跳转, 若有else则为1
	// printf("Stmt\n");
	int back1, back2, back3;
	if(!strcmp(head->child->name, "CompSt"))
		translate_CompSt(head->child, f);
	else if(!strcmp(head->child->name, "Exp")) {
		//printf("tag1\n");
		translate_Exp(head->child, f);
		//printf("tag2\n");
		fprintf(f, "\n");
	}
	else if(!strcmp(head->child->name, "RETURN")) {
		// fprintf(f, "RETURN ");
		char* res = translate_Exp(head->child->bro, f);
		fprintf(f, "RETURN %s\n", res);
		// fprintf(f, "\n");
	}
	else if(!strcmp(head->child->name, "IF")) {
		sprintf(head->id, "label%d", r);

		fprintf(f, "IF ");
		translate_Exp(head->child->bro->bro, f);
		fprintf(f, " GOTO label%d\n", r);
		back1 = r; r += 1;
		if(head->child->bro->bro->bro->bro->bro && !strcmp(head->child->bro->bro->bro->bro->bro->bro->child->name, "IF")) { // else if 优化
			// translate_Exp(head->child->bro->bro->bro->bro->bro->bro->child->bro->bro, f);
			int tmp = flagif;
			flagif = 0;
			translate_Stmt(head->child->bro->bro->bro->bro->bro->bro, f);
			fprintf(f, "GOTO label%d\n", BACK);
			flagif = tmp;
		}
		else if(head->child->bro->bro->bro->bro->bro != NULL) {
			translate_Stmt(head->child->bro->bro->bro->bro->bro->bro, f);
			fprintf(f, "GOTO label%d\n", r);
			BACK = r; r += 1;
		}
		else {
			fprintf(f, "GOTO label%d\n", r);
			BACK = r; r += 1;
		}
		fprintf(f, "LABEL label%d :\n", back1);
		translate_Stmt(head->child->bro->bro->bro->bro, f);
		if(flagif)
		fprintf(f, "LABEL label%d :\n", BACK);
		
	}
	else if(!strcmp(head->child->name, "WHILE")) {
		// 对应产生式: Stmt : WHILE LP Exp RP Stmt
		sprintf(head->id, "label%d", r);
		fprintf(f, "LABEL label%d : \n", r);
		back1 = r;
		r++;

		fprintf(f, "IF ");
		translate_Exp(head->child->bro->bro, f);
		fprintf(f, " GOTO label%d\n", r);
		back2 = r;
		r++;
		fprintf(f, " GOTO label%d\n", r);
		back3 = r;
		r++;

		fprintf(f, "LABEL label%d : \n", back2);
		translate_Stmt(head->child->bro->bro->bro->bro, f);
		fprintf(f, " GOTO label%d\n", back1);
		fprintf(f, "LABEL label%d : \n", back3);
	}
}

char* translate_Exp(struct node *head, FILE *f) {
	// if(head->child)
	// 	printf("%s\n", head->child->name);
	if(head->child->bro == NULL) {
		if(!strcmp(head->child->name, "ID")) {
			// fprintf(f, "%s ", head->child->id);
			tmp = (char*)malloc(sizeof(head->child->id));
			sprintf(tmp, "%s", head->child->id);
			// return head->child->id;
		}
		else if(!strcmp(head->child->name, "INT")) {
			// fprintf(f, "#%d ", head->child->intValue);
			tmp = (char*)malloc(sizeof(head->child->intValue+3));
			sprintf(tmp, "#%d", head->child->intValue);
		}
	}
	else if(head->child->bro->bro == NULL) {
		//没有写NOT Exp
		if(!strcmp(head->child->name, "MINUS")) {
			if(!strcmp(head->child->bro->child->name, "INT")) {
				// fprintf(f, "#-%d ", head->child->bro->child->intValue);
				tmp = (char*)malloc(sizeof(head->child->bro->child->intValue+3));
				sprintf(tmp, "#-%d", head->child->bro->child->intValue);
			}
			//else	好像也没有这种情况？
		}
	}
	else if(head->child->bro->bro->bro == NULL) {
		//printf("tag3\n");

		if(!strcmp(head->child->name, "LP")) {		
			translate_Exp(head->child->bro, f);
		}
		
		else if(!strcmp(head->child->bro->name, "DOT")) { // 对应产生式Exp DOT ID
			//printf("tag4\n");
			for(int i = 0; i < cntStruct; i ++ ) {
				for(int j = 1; j < 20; j ++ ) {
					if(!strcmp(allStruct[i][j], head->child->bro->bro->id)) {
						// printf("tag5\n");
						if(j == 1) {
							if(flagStructAssigned == 0) {
								fprintf(f, "t%d := *%s\n", tcnt, head->child->child->id);
								//printf("tag8\n");
								tmp = (char*)malloc(sizeof(tcnt + 3));
								//printf("%d\n", tcnt);
								sprintf(tmp, "t%d", tcnt);
								tcnt ++;
							}
							else {
								tmp = (char*)malloc(sizeof(head->child->child->id + 1));
								sprintf(tmp, "*%s", head->child->child->id);
							}
						}
						else {
							fprintf(f, "t%d := %s + #%d\n", tcnt, head->child->child->id, 4 * (j - 1)); tcnt ++;
							if(flagStructAssigned == 0) {
								fprintf(f, "t%d := *t%d\n", tcnt, tcnt - 1);
								tmp = (char*)malloc(sizeof(tcnt + 3));
								sprintf(tmp, "t%d", tcnt);
								tcnt ++;
							}
							else {
								tmp = (char*)malloc(sizeof(tcnt + 3));
								sprintf(tmp, "*t%d", tcnt - 1);
							}
						}
						// printf("tag7\n");
						break;
					}
				}
			}
			//printf("tag6\n");
		}

		else if(!strcmp(head->child->name, "ID")) {
			if(strcmp(head->child->id, "read")) {		//调用对应的函数，写对应的语句
				//fprintf(f, "READ %s", );
			}

			else if(!strcmp(head->child->bro->name, "LP")) { // Exp: ID LP RP
				// fprintf(f, "ARG v%d\n", returnCNT);
			}
			// else 	Exp AssignOp Exp处有对应的操作
		}
		else if(!strcmp(head->child->bro->name, "DIV")) {
			char* tmp1 = translate_Exp(head->child, f);
			// fprintf(f, "/ ");
			char* tmp2 = translate_Exp(head->child->bro->bro, f);
			fprintf(f, "t%d := %s / %s\n", tcnt, tmp1, tmp2);
			tmp = (char*)malloc(sizeof(tcnt) + 3);
			sprintf(tmp, "t%d", tcnt);
			strcpy(head->id, tmp);
			tcnt++;
		}
		else if(!strcmp(head->child->bro->name, "STAR")) {
			char* tmp1 = translate_Exp(head->child, f);
			// fprintf(f, "* ");
			char* tmp2 = translate_Exp(head->child->bro->bro, f);
			fprintf(f, "t%d := %s * %s\n", tcnt, tmp1, tmp2);
			tmp = (char*)malloc(sizeof(tcnt) + 3);
			sprintf(tmp, "t%d", tcnt);
			strcpy(head->id, tmp);
			tcnt++;
		}
		else if(!strcmp(head->child->bro->name, "MINUS")) {
			char* tmp1 = translate_Exp(head->child, f);
			// fprintf(f, "- ");
			char* tmp2 = translate_Exp(head->child->bro->bro, f);
			fprintf(f, "t%d := %s - %s\n", tcnt, tmp1, tmp2);
			tmp = (char*)malloc(sizeof(tcnt) + 3);
			sprintf(tmp, "t%d", tcnt);
			strcpy(head->id, tmp);
			tcnt++;
		}
		else if(!strcmp(head->child->bro->name, "PLUS")) {
			char* tmp1 = translate_Exp(head->child, f);
			// fprintf(f, "+ ");
			char* tmp2 = translate_Exp(head->child->bro->bro, f);
			fprintf(f, "t%d := %s + %s\n", tcnt, tmp1, tmp2);
			tmp = (char*)malloc(sizeof(tcnt) + 3);
			sprintf(tmp, "t%d", tcnt);
			strcpy(head->id, tmp);
			tcnt++;
		}
		else if(!strcmp(head->child->bro->name, "RELOP")) {
			char* tmp1 = translate_Exp(head->child, f);
			// fprintf(f, "%s ", head->child->bro->id);
			char* tmp2 = translate_Exp(head->child->bro->bro, f);
			fprintf(f, "%s %s %s", tmp1, head->child->bro->id, tmp2); // 感觉这个是特例。。。
			tmp = (char*)malloc(sizeof(tcnt) + 3);
			sprintf(tmp, "t%d", tcnt);
			strcpy(head->id, "null");
		}
		else if(!strcmp(head->child->bro->name, "OR")) {
			char* tmp1 = translate_Exp(head->child, f);
			// fprintf(f, "|| ");
			char* tmp2 = translate_Exp(head->child->bro->bro, f);
			fprintf(f, "t%d := %s || %s\n", tcnt, tmp1, tmp2);
			tmp = (char*)malloc(sizeof(tcnt) + 3);
			sprintf(tmp, "t%d", tcnt);
			strcpy(head->id, "null");
			// tcnt++;
		}
		else if(!strcmp(head->child->bro->name, "AND")) {
			char* tmp1 = translate_Exp(head->child, f);
			// fprintf(f, "&& ");
			char* tmp2 = translate_Exp(head->child->bro->bro, f);
			fprintf(f, "t%d := %s && %s\n", tcnt, tmp1, tmp2);
			tmp = (char*)malloc(sizeof(tcnt) + 3);
			sprintf(tmp, "t%d", tcnt);
			strcpy(head->id, "null");
			// tcnt++;
		}
		else if(!strcmp(head->child->bro->name, "ASSIGNOP")) {
			// printf("tag4\n");
			if(!strcmp(head->child->bro->bro->child->name, "ID") && !strcmp(head->child->bro->bro->child->id, "read")) {
				// printf("tag6\n");
				fprintf(f, "READ %s", head->child->child->id);
				// printf("tag9\n");
			}
			else if(head->child->child->bro) {
				if(!strcmp(head->child->child->bro->name, "DOT")) {
					flagStructAssigned = 1;
					char* tmp1 = translate_Exp(head->child, f);
					// printf("tag6\n");
					// fprintf(f, ":= ");
					flagStructAssigned = 0;
					char* tmp2 = translate_Exp(head->child->bro->bro, f);
					fprintf(f, "%s := %s", tmp1, tmp2);
					sprintf(tmp, "%s", tmp1);
				}
				else {
					// printf("tag5\n");
					char* tmp1 = translate_Exp(head->child, f);
					// printf("tag6\n");
					// fprintf(f, ":= ");
					char* tmp2 = translate_Exp(head->child->bro->bro, f);
					if(flagArr) {
						fprintf(f, "*");
						flagArr = 0;
					}
					fprintf(f, "%s := %s\n", tmp1, tmp2);
					tmp = (char*)malloc(sizeof(tmp1));
					sprintf(tmp, "%s", tmp1);
				}
			}
			else {
				// printf("tag5\n");
				char* tmp1 = translate_Exp(head->child, f);
				// printf("tag6\n");
				// fprintf(f, ":= ");
				char* tmp2 = translate_Exp(head->child->bro->bro, f);
				if(flagArr) {
					fprintf(f, "*");
					flagArr = 0;
				}
				fprintf(f, "%s := %s\n", tmp1, tmp2);
				tmp = (char*)malloc(sizeof(tmp1));
				sprintf(tmp, "%s", tmp1);
			}
		}
	}
	else if(head->child->bro->bro->bro->bro == NULL) {
		if(!strcmp(head->child->name, "ID")) {
			// printf("tag8\n");
			//调用对应的有参函数
			if(!strcmp(head->child->id, "write")) {
				if(!strcmp(head->child->bro->bro->child->child->name, "ID")) {
					fprintf(f, "WRITE %s", head->child->bro->bro->child->child->id);	//ext2还需要改
				}
				else if(!strcmp(head->child->bro->bro->child->child->name, "INT")) {
					if(head->child->bro->bro->child->child->intValue == 0) {
						fprintf(f, "WRITE #0");
					}
					else {
						fprintf(f, "WRITE t%d", findNum(head->child->bro->bro->child->child->intValue, f));
					}
					
				}
				else if(!strcmp(head->child->bro->bro->child->child->name, "MINUS")) {
					fprintf(f, "WRITE t%d", findNum(-head->child->bro->bro->child->child->bro->child->intValue, f));
				}
				else {
					// printf("%s\n", head->child->bro->bro->child->name);
					char* res = translate_Exp(head->child->bro->bro->child, f);
					fprintf(f, "t%d := *%s\n", tcnt, res);
					fprintf(f, "WRITE t%d", tcnt);
					sprintf(tmp, "t%d", tcnt);
					tcnt++;
					flagArr = 0;
				}
			}
			else if(head->child->bro) { // Exp: ID LP Args RP
				translate_Args(head->child->bro->bro, f);

				fprintf(f, "t%d := CALL %s\n", tcnt, head->child->id);
				tmp = (char*)malloc(sizeof(tcnt) + 3);
				sprintf(tmp, "t%d", tcnt);
				tcnt++;
			}
		}
		// 数组 Exp: Exp LB Exp RB
		// 这个部分暂时没有考虑3维及以上情况
		else if(!strcmp(head->child->bro->name, "LB")) { // 是数组
			flagArr = 1;
			struct node* newnode = head->child; // newnode始终指向Exp
			if(!strcmp(newnode->bro->bro->child->name, "INT")) {
				int t = 1;
				do {
					t *= newnode->bro->bro->child->intValue;
					// printf("name: %s\n", newnode->bro->bro->child->name);
					if(newnode->child->bro) {
						newnode = newnode->child;
					}
					else {
						break;
					}
				} while(newnode->child->bro); // 还存在Exp: Exp LB Exp RB
				
				if(!t) {
					fprintf(f, "t%d := *%s\n", tcnt, newnode->child->id);
					// printf("%s\n", tmp);
					tmp = (char*)malloc(sizeof(tcnt) + 3);
					sprintf(tmp, "t%d", tcnt);
					tcnt++;
				}
				else {
					fprintf(f, "t%d := %s + #%d\n", tcnt, newnode->child->id, t*4);
					tmp = (char*)malloc(sizeof(tcnt) + 3);
					sprintf(tmp, "t%d", tcnt);
					tcnt++;
					fprintf(f, "t%d := *%s\n", tcnt, tmp);
					tmp = (char*)malloc(sizeof(tcnt) + 3);
					sprintf(tmp, "t%d", tcnt);
					tcnt++;
				}	
			}
			else if(!strcmp(newnode->bro->bro->child->name, "ID")) {
				do {
					fprintf(f, "t%d := %s * #4\n", tcnt, newnode->bro->bro->child->id);
					tcnt++;

					if(newnode->child->bro) {
						newnode = newnode->child;
						// printf("%s\n", newnode->name);
					}
					else {
						break;
					}
				} while(newnode->child->bro); // 还存在Exp: Exp LB Exp RB
				fprintf(f, "t%d := &%s + t%d\n", tcnt, newnode->child->id, tcnt-1);
				tmp = (char*)malloc(sizeof(tcnt) + 3);
				sprintf(tmp, "t%d", tcnt);
				tcnt++;
			}
		}
	}
	return tmp;
}

void translate_VarDec(struct node *head, FILE *f) {
	// to be continued
}

void translate_VarList(struct node *head, FILE *f) {
	if(head->child->child->bro->child->type != NON_TERMINAL) { // 普通变量与结构体
		fprintf(f, "PARAM %s\n", head->child->child->bro->child->id);
	}
	else { // 数组：VarList -> ParamDec -> Specifier -> VarDec -> VarDec -> ID
		// printf("%s\n", head->child->child->bro->child->child->id);
		fprintf(f, "PARAM %s\n", head->child->child->bro->child->child->id);
	}

	if(head->child->bro) {
		translate_VarList(head->child->bro->bro, f);
	}
}

void translate_Args(struct node* head, FILE *f) {
	if(head->child->bro) { // Args : Exp COMMA Args
		translate_Args(head->child->bro->bro, f);
	}
	char* tmp1 = translate_Exp(head->child, f);
	// fprintf(f, "yes%s\n", tmp1);
	if(searchTree(root, tmp1)) {
		printf("%d\n", cnt);
		for(int i = 0; i < cnt ; i++) {
			printf("%d\n", arr[i]);
		}
		cnt = 0, ed = 0;  // 下次使用search前需要做
		fprintf(f, "ARG &%s\n", tmp1);
	}
	else {
		fprintf(f, "ARG %s\n", tmp1);
	}
}
