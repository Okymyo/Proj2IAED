#pragma once
#include "includes.h"
#include "tree_item.h"

typedef struct treenode {
    TreeItem item;
    struct treenode *left, *right;
} TreeNode;

typedef struct {
    TreeNode *root;
} Tree;

/* TreeNode methods */
TreeNode *treenode_init(TreeItem, TreeNode *, TreeNode *);

void treenode_destroy(TreeNode *);

/* Tree type methods */
void tree_init(Tree *);

int tree_empty(Tree *);

void tree_insert(Tree *, TreeItem);

int tree_count(Tree *);

int tree_height(Tree *);

int tree_balanced(Tree *);

TreeItem *tree_search(Tree *, TreeItemKey);

void tree_print(Tree *);

void tree_destroy(Tree *);

/* tree recursive methods */
void _tree_insert(TreeNode **, TreeItem);

int _tree_count(TreeNode **);

int _tree_height(TreeNode **);

int _tree_balance_factor(TreeNode **);

int _tree_balanced(TreeNode **);

void _tree_balance(TreeNode **);

void _tree_rotate_right(TreeNode **);

void _tree_rotate_left(TreeNode **);

void _tree_rotate_left_right(TreeNode **);

void _tree_rotate_right_left(TreeNode **);

TreeItem *_tree_search(TreeNode **, TreeItemKey);

void _tree_print(TreeNode **);

void _tree_destroy(TreeNode **);