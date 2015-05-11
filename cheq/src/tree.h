#pragma once
#include "includes.h"
#include "tree_item.h"

/*
* TreeNode type is a structure treenode that has three fields:
*  -> A TreeItem, that is the item that the node will hold.
*  -> A pointer to a treenode structure that will hold where the left child of the node is.
*  -> A pointer to a treenode structure that will hold where the right child of the node is.
* Size: sizeof(TreeItem) + 16 bytes.
*/
typedef struct treenode {
    TreeItem item;
    struct treenode *left, *right;
} TreeNode;

/*
* Tree type is a structure that only has one field:
*  -> A pointer to the tree root.
* Only keeps track of the pointer to where the root of the tree is.
* Size: 8 bytes.
*/
typedef struct {
    TreeNode *root;
} Tree;

/* ================================================================== */
/* TreeNode methods */
/* ================================================================== */

/*
* Creates a new tree node.
* @param treeItem  Item that the new node will hold.
* @param leftNode  Pointer of the left child of the new node.
* @param rightNode Pointer of the right child of the new node.\
* @return          Pointer to the newly created tree node.
*/
TreeNode *treenode_init(TreeItem treeItem, TreeNode *leftNode, TreeNode *rightNode);

/*
* Destroys/frees a given tree node.
* @param treeNode Pointer of the tree node to destroy/free.
*/
void treenode_destroy(TreeNode *treeNode);

/* ================================================================== */
/* Tree methods */
/* ================================================================== */

/*
* Creates a new tree.
* @return Returns a pointer to a structure of the type Tree.
*/
Tree *tree_init();

/*
* Checks if a tree is empty or not.
* @param tree Pointer to the tree to check if is or not empty.
* @return     Any number different than zero if its empty. Zero if its not empty.
*/
int tree_empty(Tree *tree);

/*
* Inserts a new item into a given tree. Not used, may be deleted.
* @param tree     Pointer to the tree to insert item into.
* @param treeItem Item to insert into the tree.
*/
void tree_insert(Tree *tree, TreeItem treeItem);

/*
* Counts the number of elements of a given tree.
* @param tree Pointer to the tree to count the elements.
* @return     Number of elements in the tree.
*/
int tree_count(Tree *tree);

/*
* Checks the height of a given tree.
* @param tree Pointer of the tree to check the height.
* @return     Height of the tree, keep in mind that leafs count as zero.
*/
int tree_height(Tree *tree);

/*
* Checks if a tree is or not balanced. Only used to test if auto-balancing was working. May be deleted.
* @param tree Pointer of the tree to check if its balanced or not.
* @return     Any number different than zero if its balanced. Zero if its not balanced.
*/
int tree_balanced(Tree *tree);

/*
* Searches a tree item in a given tree that has a given key.
* @param tree    Pointer of the tree where we are going to search the item.
* @param itemKey Key of the item that we want to search.
* @return        Returns a pointer to the item if the item was found, otherwise returns NULL.
*/
TreeItem *tree_search(Tree *tree, TreeItemKey itemKey);

/*
* Prints the tree.
* @param tree Pointer of the tree that we want to print.
*/
void tree_print(Tree *tree);

/*
* Destroys/frees a given tree.
* @param tree Pointer of the tree to destroy/free.
*/
void tree_destroy(Tree *tree);

/* ================================================================== */
/* Tree recursive methods */
/* ================================================================== */

/*
* Inserts a new item into a given node, or in it's children.
* @param treeNodePtr Pointer to pointer of the TreeNode that we want to add our item into.
* @param treeItem    Item to insert into the node.
*/
void _tree_insert(TreeNode **treeNodePtr, TreeItem treeItem);

/*
* Counts the number of children of a given node.
* @param treeNodePtr Pointer to pointer of the TreeNode that we want to count the children.
* @return            Number of children that the node has.
*/
int _tree_count(TreeNode **treeNodePtr);

/*
* Gives the height of a given node.
* @param treeNodePtr Pointer to pointer of the TreeNode that we want to compute the height.
* @return            Height of the node, keep in mind that leafs count as zero.
*/
int _tree_height(TreeNode **treeNodePtr);

/*
* Gives the balance factor of a given node.
* @param treeNodePtr Pointer to pointer of the TreeNode that we want to compute the balance factor.
* @return            Balance factor of the node. Formula = height(left child) - height(right child).
*/
int _tree_balance_factor(TreeNode **treeNodePtr);

/*
* Checks if a node is or not balanced. Only used to test if auto-balancing was working. May be deleted.
* @param treeNodePtr Pointer to pointer of the TreeNode that we want to check if its balanced or not.
* @return            Any number different than zero if its balanced. Zero if its not balanced.
*/
int _tree_balanced(TreeNode **treeNodePtr);

/*
* Balances a given node.
* @param treeNodePtr Pointer to pointer of the TreeNode that we want to balance.
*/
void _tree_balance(TreeNode **treeNodePtr);

/*
* Rotates a given node to the left. Be sure that the right child exists!
* @param treeNodePtr Pointer to pointer of the TreeNode that we want to rotate to the left.
*/
void _tree_rotate_left(TreeNode **treeNodePtr);

/*
* Rotates the left child to the left and after that rotates the node to the right.
* @param treeNodePtr Pointer to pointer of the TreeNode that we want to rotate to the left and then to the right.
*/
void _tree_rotate_left_right(TreeNode **);

/*
* Rotates a given node to the right. Be sure that the left child exists!
* @param treeNodePtr Pointer to pointer of the TreeNode that we want to perform a left right rotation.
*/
void _tree_rotate_right(TreeNode **treeNodePtr);

/*
* Rotates the right child to the right and after that rotates the node to the left.
* @param treeNodePtr Pointer to pointer of the TreeNode that we want to perform a right left rotation.
*/
void _tree_rotate_right_left(TreeNode **treeNodePtr);

/*
* Searches for a item in a given node, and it's children, that have a given key.
* @param treeNodePtr Pointer to pointer of the TreeNode where we are going to search the item.
* @param itemKey     Key of the item that we want to search.
* @return            Returns a pointer to the item if the item was found, otherwise returns NULL.
*/
TreeItem *_tree_search(TreeNode **treeNodePtr, TreeItemKey itemKey);

/*
* Prints the node and all it's children.
* @param treeNodePtr Pointer to pointer of the TreeNode that we want to print.
*/
void _tree_print(TreeNode **treeNodePtr);

/*
* Destroys/frees a given node, and all it's children.
* @param treeNodePtr Pointer to pointer of the TreeNode to destroy/free.
*/
void _tree_destroy(TreeNode **treeNodePtr);