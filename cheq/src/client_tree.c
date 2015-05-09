/*
 * Created by andre on 5/5/15.
 */

#include <stdlib.h>
#include <stdio.h>
#include "client_tree.h"
#include "client.h"

/* TreeNode methods */
TreeNode *treenode_init(Client *client, TreeNode *left, TreeNode *right) {
    TreeNode *new = (TreeNode *) malloc(sizeof(TreeNode));
    new->client = client;
    new->left = left;
    new->right = right;
    return new;
}

void treenode_destroy(TreeNode *node) {
    client_destroy(node->client);
    free(node);
}

/* Client tree type methods */
void client_tree_init(ClientTree *tree) {
    tree->root = NULL;
}

int client_tree_empty(ClientTree *tree) {
    return tree->root == NULL;
}

void client_tree_insert(ClientTree *tree, Client *client) {
    if (client_tree_search(tree, client_key(client)) == client_nil())
        _client_tree_insert(&tree->root, client);
}

int client_tree_count(ClientTree *tree) {
    return _client_tree_count(&tree->root);
}

int client_tree_height(ClientTree *tree) {
    return _client_tree_height(&tree->root);
}

int client_tree_balanced(ClientTree *tree) {
    return _client_tree_balanced(&tree->root);
}

Client *client_tree_search(ClientTree *tree, ClientKey key) {
    return _client_tree_search(&(tree->root), key);
}

void client_tree_print(ClientTree *tree) {
    _client_tree_print(&tree->root);
}

void client_tree_destroy(ClientTree *tree) {
    _client_tree_destroy(&tree->root);
}

/* Client tree recursive methods */
void _client_tree_insert(TreeNode **node, Client *client) {
    if (*node == NULL) {
        *node = treenode_init(client, NULL, NULL);
        return;
    }
    if (client_compare(client_key(client), client_key((*node)->client)) < 0) {
        _client_tree_insert(&((*node)->left), client);
    } else {
        _client_tree_insert(&((*node)->right), client);
    }
    _client_tree_balance(node);
}

int _client_tree_count(TreeNode **node) {
    if (*node != NULL) {
        return 1 + _client_tree_count(&((*node)->left)) + _client_tree_count(&((*node)->right));
    }
    return 0;
}

int _client_tree_height(TreeNode **node) {
    int heightLeft, heightRight;
    if (*node != NULL) {
        heightLeft = _client_tree_height(&((*node)->left));
        heightRight = _client_tree_height(&((*node)->right));
        if (heightLeft > heightRight) return heightLeft + 1;
        return heightRight + 1;
    }
    return -1;
}

int _client_tree_balance_factor(TreeNode **pNode) {
    if (*pNode != NULL) {
        return _client_tree_height((&(*pNode)->left)) - _client_tree_height((&(*pNode)->right));
    }
    return 0;
}

void _client_tree_rotate_left(TreeNode **pNode) {
    TreeNode *nodeRight = (*pNode)->right;
    (*pNode)->right = nodeRight->left;
    nodeRight->left = *pNode;
    *pNode = nodeRight;
}

void _client_tree_rotate_left_right(TreeNode **pNode) {
    if (*pNode != NULL) {
        _client_tree_rotate_left(&((*pNode)->left));
        _client_tree_rotate_right(pNode);
    }
}

void _client_tree_rotate_right(TreeNode **pNode) {
    TreeNode *nodeLeft = (*pNode)->left;
    (*pNode)->left = nodeLeft->right;
    nodeLeft->right = *pNode;
    *pNode = nodeLeft;
}

void _client_tree_rotate_right_left(TreeNode **pNode) {
    if (*pNode != NULL) {
        _client_tree_rotate_right(&((*pNode)->right));
        _client_tree_rotate_left(pNode);
    }
}

void _client_tree_balance(TreeNode **pNode) {
    int balanceFactor;
    if(*pNode == NULL) return;
    balanceFactor = _client_tree_balance_factor(pNode);
    if(balanceFactor > 1){
        if(_client_tree_balance_factor(&((*pNode)->left)) > 0){
            _client_tree_rotate_right(pNode);
        }else{
            _client_tree_rotate_left_right(pNode);
        }
    }else if(balanceFactor < -1){
        if(_client_tree_balance_factor(&((*pNode)->right)) < 0){
            _client_tree_rotate_left(pNode);
        }else{
            _client_tree_rotate_right_left(pNode);
        }
    }
}

int _client_tree_balanced(TreeNode **pNode) {
    if (*pNode != NULL) {
        int factor = _client_tree_balance_factor(pNode);
        if (factor <= 1 && factor >= -1) {
            return _client_tree_balanced(&((*pNode)->left)) && _client_tree_balanced(&((*pNode)->right));
        }
        return 0;
    }
    return 1;
}

Client *_client_tree_search(TreeNode **node, ClientKey key) {
    if (*node != NULL) {
        long comparison = client_compare(key, client_key((*node)->client));
        if (comparison == 0) {
            return (*node)->client;
        }
        if (comparison < 0) {
            return _client_tree_search(&((*node)->left), key);
        }
        return _client_tree_search(&((*node)->right), key);
    }
    return client_nil();
}

void _client_tree_print(TreeNode **leaf) {
    if (*leaf != NULL) {
        _client_tree_print(&((*leaf)->left));
        client_print((*leaf)->client);
        _client_tree_print(&((*leaf)->right));
    }
}

void _client_tree_destroy(TreeNode **leaf) {
    if (*leaf != NULL) {
        _client_tree_destroy(&((*leaf)->left));
        _client_tree_destroy(&((*leaf)->right));
        treenode_destroy(*leaf);
    }
}
