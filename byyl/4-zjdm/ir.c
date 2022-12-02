#include "SyntaxTree.h"
#include "RBTtest.c"
#include "ir.h"

InterCodes *heading = NULL;
InterCodes *tail = NULL;
extern VariLink this_scope;

void parsing(struct node* root) {
    //printf("root->name:%s\n", root->name);
    if(root == NULL) return;
    if(!strcmp(root->name, "ExtDef")){
        /*
        ExtDef : Specifier ExtDecList SEMI
               | Specifier SEMI
               | Specifier FunDec CompSt
               | Specifier FunDec SEMI
        */
        struct node* spec = root->child;
        /*
        Specifier : TYPE | StructSpcifier
        */
        struct node* t = spec->child;
        struct node *p = spec->bro; 
        // p == 'ExtDecList'/ 'SEMI' / 'FunDec'
        if (!strcmp(p->name, "SEMI")) {//Specifier SEMI

        }
        else if (!strcmp(p->name, "FunDec")){//Specifier FunDec CompSt
            translate_FuncDec(p);
            struct node *compst = p->bro;
            if(!strcmp(compst->name, "CompSt")){
                translate_CompSt(compst);
            }
            if(compst->comp_tail==NULL && compst->comp_head==NULL){
                log("skipping empty CompSt\n");
                return;
            }
            Assert(compst->comp_tail!=NULL && compst->comp_head!=NULL);
            compst->comp_head->prev = tail;
            tail->next = compst->comp_head;
            tail = compst->comp_tail;
            Assert(tail->next==NULL);
        }
        
    }
    if(root->child!=NULL)
        parsing(root->child);
    if(root->bro!=NULL)
        parsing(root->bro);
}


void insert_ir(InterCode *ir){
    InterCodes *entry = (InterCodes *)malloc(sizeof(InterCodes));
    entry->next = NULL;
    entry->prev = NULL;
    entry->code = ir;
    if(heading == NULL){
        Assert(tail == NULL);
        heading = entry;
        tail = entry;
    }
    else{
        Assert(tail != NULL);
        tail->next = entry;
        entry->prev = tail;
        tail = entry;
    }
}

/*
    LABEL, FUNCTION, GOTO, RETURN, ARG, PARAM, READ, WRITE 单操作数
*/
void gen_ir_1(Operand *op, int ir_kind){
    InterCode *ir = (InterCode *)malloc(sizeof(InterCode));
    ir->ir_kind = ir_kind;
    ir->unop.op = op;
    insert_ir(ir);
}

/*
    ASSIGN, GET_ADDR, GET_ADDR_VAL, TO_ADDR, DEC, CALL
*/
void gen_ir_2(Operand *op1, Operand *op2, int ir_kind){
    InterCode *ir = (InterCode *)malloc(sizeof(InterCode));
    ir->ir_kind = ir_kind;
    ir->lr.op1 = op1;
    ir->lr.op2 = op2;
    insert_ir(ir);
}

void gen_ir_3(Operand *op1, Operand *op2, Operand *result, int ir_kind){
    InterCode *ir = (InterCode *)malloc(sizeof(InterCode));
    ir->ir_kind = ir_kind;
    ir->binop.result = result;
    ir->binop.op1 = op1;
    ir->binop.op2 = op2;
    insert_ir(ir);
}

void gen_if_goto(Operand *op1, Operand *relop, Operand *op2, Operand *op3){
    InterCode *ir = (InterCode *)malloc(sizeof(InterCode));
    ir->ir_kind = IR_IF;
    ir->cond.op1 = op1;
    ir->cond.relop = relop;
    ir->cond.op2 = op2;
    ir->cond.op3 = op3;
    insert_ir(ir);
}

Operand *gen_im(int im){
    Operand *ret = (Operand *)malloc(sizeof(Operand));
    ret->op_kind = OP_CONSTANT;
    ret->const_value = im;
    //("im%d\n",im);
    return ret;
}

Operand *get_var(char *var_name){
    MyType* tmp;
    strcpy(tmp->name, var_name);
    tmp = search(this_scope, *tmp); // 断言search结果一定非空
    if(tmp->ir_var_no == NULL){
        Operand *ret = (Operand *)malloc(sizeof(Operand));
        ret->op_kind = OP_VARIABLE;
        ret->var_no = ++new_var_cnt;
        ret->is_param = 0;
        ret->addr_pos_kind = -1;
        tmp->ir_var_no = ret;
    }
    return tmp->ir_var_no;
}
Operand *new_temp(){
    new_temp_cnt ++;
    Operand *ret = (Operand *) malloc(sizeof(Operand));
    //log("new temp: %d\n", new_temp_cnt);
    ret->op_kind = OP_TEMP;
    ret->tmp_no = new_temp_cnt;
    ret->addr_pos_kind = -1;
    return ret;
}

Operand *new_label(){
    new_label_cnt++;
    Operand *ret = (Operand *) malloc(sizeof(Operand));
    ret->op_kind = OP_LABEL;
    ret->label_no = new_label_cnt;
    return ret;
}
