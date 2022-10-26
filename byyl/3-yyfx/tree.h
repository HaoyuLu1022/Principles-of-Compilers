#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define RED 0
#define BLACK 1

typedef union {
    bool def;  // 是否被定义
    char* name;   // 变量名
    char* type;  // 类型
    int dimension;   // 数组维度
    int scope;   // 作用域
} VariType;

typedef struct VariableRBTreeNode {
    unsigned char color;
    VariType key;
    struct VariableRBTreeNode *left;
    struct VariableRBTreeNode *right;
    struct VariableRBTreeNode *parent;
}VariNode, *VariRBTree;

typedef struct rb_root {
    VariNode *node;
}VariRBRoot;

#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)
// 参考strcmp设计，name，scope依次排序
int varicmp(VariType a, VariType b) {
    if(strcmp(a.name, b.name) != 0) return strcmp(a.name, b.name);
    return a.scope - b.scope;
}

static void preorder(VariRBTree tree)
{
    if(tree != NULL)
    {
        printf("%d ", tree->key);
        preorder(tree->left);
        preorder(tree->right);
    }
}
void preorder_rbtree(VariRBRoot *root) 
{
    if (root)
        preorder(root->node);
}

VariNode* search(VariRBTree x, VariType key)
{
    int tmp = varicmp(x->key, key);
    if (x==NULL || (tmp == 0))
        return x;

    if (tmp < 0)
        return search(x->left, key);
    else
        return search(x->right, key);
}
int rbtree_search(VariRBRoot *root, VariType key)
{
    if (root)
        return search(root->node, key)? 0 : -1;
}


VariNode* iterative_search(VariRBTree x, VariType key)
{
    int tmp = varicmp(x->key, key);
    while ((x!=NULL) && tmp == 0)
    {
        if (tmp < 0)
            x = x->left;
        else
            x = x->right;
    }

    return x;
}
int iterative_rbtree_search(VariRBRoot *root, VariType key)
{
    if (root)
        return iterative_search(root->node, key) ? 0 : -1;
}

// left rotate

void rbtree_left_rotate(VariRBRoot*root, VariNode *x) {
    VariNode *tmp = x->right;

    x->right = tmp->left;

    if(tmp->left != NULL)
        tmp->left->parent = x;
    
    tmp->parent = x->parent;

    if(x->parent == NULL){
        root->node = tmp;
    }
    else{
        if(x->parent->left == x)
            x->parent->left = tmp;
        else
            x->parent->right = tmp;
    }

    tmp->left = x;
    x->parent = tmp;
}

/*
      p                   p
     /                   /
    x                   tmp
   / \       -->       /   \
 tmp  rx              lt    x
 / \                       / \
lt rt                     rt  rx
*/

void rbtree_right_rotate(VariRBRoot *root, VariNode *x){
    
    VariNode *tmp = x->left;

    x->left = tmp->right;
    if(tmp->right != NULL)
        tmp->right->parent = x;
    
    tmp->parent = x->parent;

    if(x->parent == NULL){
        root->node = tmp;
    }
    else{
        if(x == x->parent->left)
            x->parent->left = tmp;
        else
            x->parent->right = tmp;
    }

    tmp->right = x;
    x->parent = tmp;
}

void rbtree_insert(VariRBRoot *root, VariNode *node){
    VariNode *y = NULL;
    VariNode *x = root->node;

    while(x != NULL){
        y = x;
        if(varicmp(node->key,x->key)<0)
            x = x->left;
        else
            x = x->right;
    }
    rb_parent(node) = y;
    if(y != NULL){
        if(varicmp(node->key,y->key)<0)
            y->left = node;
        else
            y->right = node;
    }
    else{
        root->node = node;
    }

    node->color = RED;

    rbtree_insert_fixup(root, node);
}

void rbtree_insert_fixup(VariRBRoot *root, VariNode *node)
{
    VariNode *parent, *gparent;

    // 若“父节点存在，并且父节点的颜色是红色”
    while ((parent = rb_parent(node)) && rb_is_red(parent))
    {
        gparent = rb_parent(parent);

        //若“父节点”是“祖父节点的左孩子”
        if (parent == gparent->left)
        {
            // Case 1条件：叔叔节点是红色
            {
                VariNode *uncle = gparent->right;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            // Case 2条件：叔叔是黑色，且当前节点是右孩子
            if (parent->right == node)
            {
                VariNode *tmp;
                rbtree_left_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3条件：叔叔是黑色，且当前节点是左孩子。
            rb_set_black(parent);
            rb_set_red(gparent);
            rbtree_right_rotate(root, gparent);
        } 
        else//若“z的父节点”是“z的祖父节点的右孩子”
        {
            // Case 1条件：叔叔节点是红色
            {
                VariNode *uncle = gparent->left;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            // Case 2条件：叔叔是黑色，且当前节点是左孩子
            if (parent->left == node)
            {
                VariNode *tmp;
                rbtree_right_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3条件：叔叔是黑色，且当前节点是右孩子。
            rb_set_black(parent);
            rb_set_red(gparent);
            rbtree_left_rotate(root, gparent);
        }
    }

    // 将根节点设为黑色
    rb_set_black(root->node);
}

void rbtree_delete(VariRBRoot *root, VariNode *node)
{
    VariNode *child, *parent;
    int color;

    // 被删除节点的"左右孩子都不为空"的情况。
    if ( (node->left!=NULL) && (node->right!=NULL) ) 
    {
        // 被删节点的后继节点。(称为"取代节点")
        // 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
        VariNode *replace = node;

        // 获取后继节点
        replace = replace->right;
        while (replace->left != NULL)
            replace = replace->left;

        // "node节点"不是根节点(只有根节点不存在父节点)
        if (rb_parent(node))
        {
            if (rb_parent(node)->left == node)
                rb_parent(node)->left = replace;
            else
                rb_parent(node)->right = replace;
        } 
        else 
            // "node节点"是根节点，更新根节点。
            root->node = replace;

        // child是"取代节点"的右孩子，也是需要"调整的节点"。
        // "取代节点"肯定不存在左孩子！因为它是一个后继节点。
        child = replace->right;
        parent = rb_parent(replace);
        // 保存"取代节点"的颜色
        color = rb_color(replace);

        // "被删除节点"是"它的后继节点的父节点"
        if (parent == node)
        {
            parent = replace;
        } 
        else
        {
            // child不为空
            if (child)
                rb_set_parent(child, parent);
            parent->left = child;

            replace->right = node->right;
            rb_set_parent(node->right, replace);
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if (color == BLACK)
            rbtree_delete_fixup(root, child, parent);
        free(node);

        return ;
    }

    if (node->left !=NULL)
        child = node->left;
    else 
        child = node->right;

    parent = node->parent;
    // 保存"取代节点"的颜色
    color = node->color;

    if (child)
        child->parent = parent;

    // "node节点"不是根节点
    if (parent)
    {
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
        root->node = child;

    if (color == BLACK)
        rbtree_delete_fixup(root, child, parent);
    free(node);
}

void rbtree_delete_fixup(VariRBRoot *root, VariNode *node, VariNode *parent)
{
    VariNode *other;

    while ((!node || rb_is_black(node)) && node != root->node)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (rb_is_red(other))
            {
                // Case 1: x的兄弟w是红色的  
                rb_set_black(other);
                rb_set_red(parent);
                rbtree_left_rotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->right || rb_is_black(other->right))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
                    rb_set_black(other->left);
                    rb_set_red(other);
                    rbtree_right_rotate(root, other);
                    other = parent->right;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->right);
                rbtree_left_rotate(root, parent);
                node = root->node;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (rb_is_red(other))
            {
                // Case 1: x的兄弟w是红色的  
                rb_set_black(other);
                rb_set_red(parent);
                rbtree_right_rotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->left || rb_is_black(other->left))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
                    rb_set_black(other->right);
                    rb_set_red(other);
                    rbtree_left_rotate(root, other);
                    other = parent->left;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->left);
                rbtree_right_rotate(root, parent);
                node = root->node;
                break;
            }
        }
    }
    if (node)
        rb_set_black(node);
}