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

/* TreeNode methods */
TreeNode *treenode_init(Client*, TreeNode*, TreeNode*);

void treenode_destroy(TreeNode*);

/* Client tree methods */
void client_tree_init(TreeNode **);

void client_tree_insert(TreeNode **, Client*);

int client_tree_count(TreeNode **);

int client_tree_height(TreeNode **);

Client *client_tree_search(TreeNode **, Key);

void client_tree_print(TreeNode **);

void client_tree_destroy(TreeNode **);

#endif
