#include <assert.h>
#include <stdio.h>
#include "SyntaxTree.h"
extern struct node* head;
int new_temp_cnt = 0;//?
int new_label_cnt = 0;
int new_var_cnt = 0;
int debug_cnt = 0;

typedef struct _intercode InterCode;
typedef struct _operand Operand;
typedef struct _intercodes InterCodes;
typedef struct _argList ArgList;

struct _intercode {
    enum { 
      IR_LABEL, 
      IR_FUNCTION, 
      IR_ASSIGN, 
      IR_ADD, IR_SUB, IR_MUL, IR_DIV, 
      IR_GET_ADDR,
      IR_GET_ADDR_VAL,
      IR_TO_ADDR,
      IR_GOTO,
      IR_IF,
      IR_RETURN,
      IR_DEC,
      IR_ARG,
      IR_CALL_FUNC,
      IR_PARAM,
      IR_READ, IR_WRITE
    } ir_kind;
    union {
      struct {Operand *op1, *op2; } lr; 
      struct {Operand *op; } unop; // unary
      struct {Operand *result, *op1, *op2; } binop;
      struct {Operand *op1, *relop, *op2, *op3; } cond;//条件
    };
};

struct _operand {
    enum {
        OP_VARIABLE,
        OP_TEMP,
        OP_CONSTANT,
        OP_ADDRESS,
        OP_FUNCTION,
        OP_LABEL,
        OP_RELOP
    }op_kind;
    union {
        int var_no;
        int tmp_no;
        int const_value;
        char* func_name;
        int label_no;
        char* relop;
    };
    enum {
        ISVALUE=199,
        ISADDRESS
    }addr_pos_kind;
    int is_param;
};

struct _intercodes {
    InterCode* code;
    InterCodes* prev;
    InterCodes* next;
};

struct _arglist {
    Operand* arg;
    ArgList* next;
};

void insert_ir(InterCode *ir);
void gen_ir_1(Operand *op, int ir_kind);
void gen_ir_2(Operand *op1, Operand *op2, int ir_kind);
void gen_ir_3(Operand *op1, Operand *op2, Operand *result, int ir_kind);
void gen_if_goto(Operand *op1, Operand *relop, Operand *op2, Operand *op3);
Operand *gen_im(int im);
Operand *get_var(char *var_name);
Operand *new_temp();
Operand *new_label();
void add_arg_list(Operand *new_arg, ArgList *arg_head);
void translate_Args(struct node *Args, ArgList *arg_head);
Operand *get_addr_value(Operand *place);
struct Variable *get_array_type(struct node *Exp);
void translate_Exp(struct node *Exp, Operand *place);
void translate_Cond(struct node *Exp, Operand *label_true, Operand *label_false);
void translate_VarList(struct node *VarList);
void translate_FuncDec(struct node *FuncDec);
void translate_Stmt(struct node *Stmt);
void translate_VarDec(struct node *VarDec, Operand *place);
void translate_Def(struct node *Def);
void translate_CompSt(struct node *CompSt);
void print_op(FILE *fp, Operand *op);
void print_binop(FILE *fp, InterCode *ir);
void print_ir(FILE *fp, InterCodes *start);

// assert.h
#define NDEBUG

#ifdef NDEBUG
  #define Assert(cond) 1
#else
  #define Assert(cond) \
    do { \
      if (!(cond)) { \
        printk("Assertion fail at %s:%d\n", __FILE__, __LINE__); \
        exit(0); \
      } \
    } while (0)
#endif

#ifdef NDEBUG
  #define log(...) ;
#else
  #define log(...) printf(__VA_ARGS__)
#endif