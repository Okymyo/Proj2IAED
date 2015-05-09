/*
 * Created by andre on 5/5/15.
 */

#ifndef C_CLIENT_TREE_H
#define C_CLIENT_TREE_H

#include "client.h"

typedef struct treenode {
    Client *client;
    struct treenode *left, *right;
} TreeNode;

typedef struct {
    TreeNode *root;
} ClientTree;

/* TreeNode methods */
TreeNode *treenode_init(Client *, TreeNode *, TreeNode *);

void treenode_destroy(TreeNode *);

/* Client tree type methods */
void client_tree_init(ClientTree *);

int client_tree_empty(ClientTree *);

void client_tree_insert(ClientTree *, Client *);

int client_tree_count(ClientTree *);

int client_tree_height(ClientTree *);

int client_tree_balanced(ClientTree *);

Client *client_tree_search(ClientTree *, ClientKey);

void client_tree_print(ClientTree *);

void client_tree_destroy(ClientTree *);

/* Client tree recursive methods */
void _client_tree_insert(TreeNode **, Client *);

int _client_tree_count(TreeNode **);

int _client_tree_height(TreeNode **);

int _client_tree_balance_factor(TreeNode **);

int _client_tree_balanced(TreeNode **);

void _client_tree_balance(TreeNode **);

void _client_tree_rotate_right(TreeNode **);

void _client_tree_rotate_left(TreeNode **);

void _client_tree_rotate_left_right(TreeNode **);

void _client_tree_rotate_right_left(TreeNode **);

Client *_client_tree_search(TreeNode **, ClientKey);

void _client_tree_print(TreeNode **);

void _client_tree_destroy(TreeNode **);

#endif
