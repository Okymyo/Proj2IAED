/* =====================
 * Grupo 5, IAED, LEIC-T
 * 81900 - Nuno Anselmo
 * 81943 - Gonçalo Matos
 * 82047 - André Mendes
   ===================== */

#include "tree.h"

#ifndef max
#define max(a, b) a > b? a :b
#endif

/* ================================================================== */
/* TreeNode methods */
/* ================================================================== */

TreeNode *treenode_init(TreeItem treeItem, TreeNode *leftNode, TreeNode *rightNode) {
    TreeNode *new = (TreeNode *) malloc(sizeof(TreeNode));
    new->item = treeItem;
    new->left = leftNode;
    new->right = rightNode;
    new->height = 0;
    return new;
}

void treenode_destroy(TreeNode *treeNode) {
    tree_item_destroy(treeNode->item);
    free(treeNode);
}

/* ================================================================== */
/* Tree methods */
/* ================================================================== */

Tree *tree_init() {
    return (Tree *) calloc(1, sizeof(Tree));
}

int tree_empty(Tree *tree) {
    return tree->root == NULL;
}

void tree_insert(Tree *tree, TreeItem treeItem) {
    if (tree_search(tree, tree_item_key(treeItem)) == NULL)
        _tree_insert(&tree->root, treeItem);
}

void tree_remove(Tree *tree, TreeItemKey itemKey) {
    _tree_remove(&tree->root, itemKey);
}

unsigned int tree_count(Tree *tree) {
    return _tree_count(&tree->root);
}

TreeItem *tree_search(Tree *tree, TreeItemKey itemKey) {
    return _tree_search(&(tree->root), itemKey);
}

void tree_print(Tree *tree) {
    _tree_print(&tree->root);
}

void tree_destroy(Tree *tree) {
    _tree_destroy(&tree->root);
    free(tree);
}
/* ================================================================== */
/* Tree recursive methods */
/* ================================================================== */

void _tree_insert(TreeNode **treeNodePtr, TreeItem treeItem) {
    if (*treeNodePtr == NULL) {
        /* We hit the bottom! Make a new leaf */
        *treeNodePtr = treenode_init(treeItem, NULL, NULL);
        return;
    }
    if (tree_item_compare(tree_item_key(treeItem), tree_item_key((*treeNodePtr)->item)) < 0) {
        /* If the key is lesser than this nodes' item key, go insert it in the left subtree */
        _tree_insert(&((*treeNodePtr)->left), treeItem);
    } else {
        /* If the key is bigger than this nodes' item key, go insert it in the right subtree */
        _tree_insert(&((*treeNodePtr)->right), treeItem);
    }
    /* Balance it! */
    _tree_balance(treeNodePtr);
}


void _tree_remove(TreeNode **treeNodePtr, TreeItemKey itemKey) {
    if (*treeNodePtr != NULL) {
        int comparison = tree_item_compare(itemKey, tree_item_key((*treeNodePtr)->item));
        /* If the key is lesser than this nodes' item key, go delete it from the left subtree */
        if (comparison < 0) _tree_remove(&((*treeNodePtr)->left), itemKey);
        /* If the key is biger than this nodes' item key, go delete it from the right subtree */
        else if (comparison > 0) _tree_remove(&((*treeNodePtr)->right), itemKey);
        /* If the key is equal than this nodes' item key, go delete it this node! */
        else {
            if ((*treeNodePtr)->left != NULL && (*treeNodePtr)->right != NULL) {
                /* If it is an "internal" node, find the max child of the left subtree */
                TreeNode *max = _tree_max(&(*treeNodePtr)->left);
                /* Change items with the node */
                (*treeNodePtr)->item = max->item;
                /* Delete the max child in the left subtree, which is either a leaf,
                 * or a node with only one subtree */
                _tree_remove(&((*treeNodePtr)->left), tree_item_key(max->item));
            } else {
                TreeNode *aux = *treeNodePtr;
                if ((*treeNodePtr)->left == NULL && (*treeNodePtr)->right == NULL) {
                    /* If its a leaf, just make it NULL so our parent points to NULL */
                    *treeNodePtr = NULL;
                } else {
                    if ((*treeNodePtr)->left == NULL) {
                        /* If it doesn't have a left subtree, make it point to the right subtree */
                        *treeNodePtr = (*treeNodePtr)->right;
                    } else {
                        /* If it doesn't have a righ subtree, make it point to the left subtree */
                        *treeNodePtr = (*treeNodePtr)->left;
                    }
                }
                /* Destroy the node! We dont want any memory leaks! */
                treenode_destroy(aux);
            }
        }
        /* Balance it! */
        _tree_balance(treeNodePtr);
    }
}


TreeNode *_tree_max(TreeNode **treeNodePtr) {
    /* Dive into the right tree like crazy until there is no more! */
    if (*treeNodePtr != NULL && (*treeNodePtr)->right != NULL) {
        return _tree_max(&((*treeNodePtr)->right));
    }
    return *treeNodePtr;
}

unsigned int _tree_count(TreeNode **treeNodePtr) {
    if (*treeNodePtr != NULL) {
        return 1 + _tree_count(&((*treeNodePtr)->left)) + _tree_count(&((*treeNodePtr)->right));
    }
    return 0;
}

int _tree_height(TreeNode **treeNodePtr) {
    if (*treeNodePtr != NULL) {
        return (*treeNodePtr)->height;
    }
    return -1;
}

void _tree_recalculate_height(TreeNode **treeNodePtr) {
    (*treeNodePtr)->height = max(_tree_height(&((*treeNodePtr)->left)), _tree_height(&((*treeNodePtr)->right))) + 1;
}

int _tree_balance_factor(TreeNode **treeNodePtr) {
    if (*treeNodePtr != NULL) {
        return _tree_height((&(*treeNodePtr)->left)) - _tree_height((&(*treeNodePtr)->right));
    }
    return 0;
}

void _tree_rotate_left(TreeNode **treeNodePtr) {
    TreeNode *nodeRight = (*treeNodePtr)->right;
    (*treeNodePtr)->right = nodeRight->left;
    nodeRight->left = *treeNodePtr;

    _tree_recalculate_height(treeNodePtr);
    _tree_recalculate_height(&nodeRight);

    *treeNodePtr = nodeRight;
}

void _tree_rotate_left_right(TreeNode **treeNodePtr) {
    if (*treeNodePtr != NULL) {
        _tree_rotate_left(&((*treeNodePtr)->left));
        _tree_rotate_right(treeNodePtr);
    }
}

void _tree_rotate_right(TreeNode **treeNodePtr) {
    TreeNode *nodeLeft = (*treeNodePtr)->left;
    (*treeNodePtr)->left = nodeLeft->right;
    nodeLeft->right = *treeNodePtr;

    _tree_recalculate_height(treeNodePtr);
    _tree_recalculate_height(&nodeLeft);

    *treeNodePtr = nodeLeft;
}

void _tree_rotate_right_left(TreeNode **treeNodePtr) {
    if (*treeNodePtr != NULL) {
        _tree_rotate_right(&((*treeNodePtr)->right));
        _tree_rotate_left(treeNodePtr);
    }
}

void _tree_balance(TreeNode **treeNodePtr) {
    int balanceFactor;
    if (*treeNodePtr == NULL) return;
    balanceFactor = _tree_balance_factor(treeNodePtr);
    if (balanceFactor > 1) {
        if (_tree_balance_factor(&((*treeNodePtr)->left)) > 0) {
            _tree_rotate_right(treeNodePtr);
        } else {
            _tree_rotate_left_right(treeNodePtr);
        }
    } else if (balanceFactor < -1) {
        if (_tree_balance_factor(&((*treeNodePtr)->right)) < 0) {
            _tree_rotate_left(treeNodePtr);
        } else {
            _tree_rotate_right_left(treeNodePtr);
        }
    } else {
        _tree_recalculate_height(treeNodePtr);
    }
}

TreeItem *_tree_search(TreeNode **treeNodePtr, TreeItemKey itemKey) {
    if (*treeNodePtr != NULL) {
        long comparison = tree_item_compare(itemKey, tree_item_key((*treeNodePtr)->item));
        if (comparison == 0) {
            return &(*treeNodePtr)->item;
        }
        if (comparison < 0) {
            return _tree_search(&((*treeNodePtr)->left), itemKey);
        }
        return _tree_search(&((*treeNodePtr)->right), itemKey);
    }
    return NULL;
}

void _tree_print(TreeNode **treeNodePtr) {
    if (*treeNodePtr != NULL) {
        _tree_print(&((*treeNodePtr)->left));
        tree_item_print((*treeNodePtr)->item);
        _tree_print(&((*treeNodePtr)->right));
    }
}

void _tree_destroy(TreeNode **treeNodePtr) {
    if (*treeNodePtr != NULL) {
        _tree_destroy(&((*treeNodePtr)->left));
        _tree_destroy(&((*treeNodePtr)->right));
        treenode_destroy(*treeNodePtr);
    }
}