/*
 * Created by andre on 5/5/15.
 */

#include <stdlib.h>
#include "client_tree.h"

/* TreeNode methods */
TreeNode treenode_init(Client client, TreeNode left, TreeNode right) {
    TreeNode new = (TreeNode) malloc(sizeof(struct treenode));
    new->client = client;
    new->left = left;
    new->right = right;
    return new;
}

void treenode_destroy(TreeNode node) {
    client_destroy(node->client);
    free(node);
}

/* Client tree methods */
void client_tree_init(TreeNode *root) {
    *root = NULL;
}

void client_tree_insert(TreeNode *leaf, Client client) {
    if (*leaf == NULL) {
        *leaf = treenode_init(client, NULL, NULL);
        return;
    }
    if (client_compare(client_key(client), client_key((*leaf)->client)) < 0) {
        client_tree_insert(&((*leaf)->left), client);
        return;
    }
    client_tree_insert(&((*leaf)->right), client);
}

int client_tree_count(TreeNode *leaf) {
    if(*leaf != NULL){
        return 1+client_tree_count(&((*leaf)->left))+client_tree_count(&((*leaf)->right));
    }
    return 0;
}

int client_tree_height(TreeNode *leaf) {
    int heightLeft, heightRight;
    if(*leaf != NULL){
        heightLeft = client_tree_height(&((*leaf)->left));
        heightRight = client_tree_height(&((*leaf)->right));
        if(heightLeft > heightRight) return heightLeft+1;
        return heightRight+1;
    }
    return -1;
}

Client client_tree_search(TreeNode *leaf, Key key) {
    if (*leaf != NULL) {
        long comparison = client_compare(key, client_key((*leaf)->client));
        if (comparison == 0) {
            return (*leaf)->client;
        }
        if (comparison < 0) {
            return client_tree_search(&((*leaf)->left), key);
        }
        return client_tree_search(&((*leaf)->right), key);
    }
    return client_nil();
}

void client_tree_print(TreeNode *leaf) {
    if (*leaf != NULL) {
        client_tree_print(&((*leaf)->left));
        client_print((*leaf)->client);
        client_tree_print(&((*leaf)->right));
    }
}

void client_tree_destroy(TreeNode *leaf) {
    if (*leaf != NULL) {
        client_tree_destroy(&((*leaf)->left));
        client_tree_destroy(&((*leaf)->right));
        treenode_destroy(*leaf);
    }
}
