#include "tree.h"

/* TreeNode methods */
TreeNode *treenode_init(TreeItem item, TreeNode *left, TreeNode *right) {
    TreeNode *new = (TreeNode *) malloc(sizeof(TreeNode));
    new->item = item;
    new->left = left;
    new->right = right;
    return new;
}

void treenode_destroy(TreeNode *node) {
    tree_item_destroy(node->item);
    free(node);
}

/* Tree type methods */
void tree_init(Tree *tree) {
    tree->root = NULL;
}

int tree_empty(Tree *tree) {
    return tree->root == NULL;
}

void tree_insert(Tree *tree, TreeItem item) {
    if (tree_search(tree, tree_item_key(item)) == tree_item_nil())
        _tree_insert(&tree->root, item);
}

int tree_count(Tree *tree) {
    return _tree_count(&tree->root);
}

int tree_height(Tree *tree) {
    return _tree_height(&tree->root);
}

int tree_balanced(Tree *tree) {
    return _tree_balanced(&tree->root);
}

TreeItem *tree_search(Tree *tree, TreeItemKey key) {
    return _tree_search(&(tree->root), key);
}

void tree_print(Tree *tree) {
    _tree_print(&tree->root);
}

void tree_destroy(Tree *tree) {
    _tree_destroy(&tree->root);
}

/* tree recursive methods */
void _tree_insert(TreeNode **node, TreeItem item) {
    if (*node == NULL) {
        *node = treenode_init(item, NULL, NULL);
        return;
    }
    if (tree_item_compare(tree_item_key(item), tree_item_key((*node)->item)) < 0) {
        _tree_insert(&((*node)->left), item);
    } else {
        _tree_insert(&((*node)->right), item);
    }
    _tree_balance(node);
}

int _tree_count(TreeNode **node) {
    if (*node != NULL) {
        return 1 + _tree_count(&((*node)->left)) + _tree_count(&((*node)->right));
    }
    return 0;
}

int _tree_height(TreeNode **node) {
    int heightLeft, heightRight;
    if (*node != NULL) {
        heightLeft = _tree_height(&((*node)->left));
        heightRight = _tree_height(&((*node)->right));
        if (heightLeft > heightRight) return heightLeft + 1;
        return heightRight + 1;
    }
    return -1;
}

int _tree_balance_factor(TreeNode **pNode) {
    if (*pNode != NULL) {
        return _tree_height((&(*pNode)->left)) - _tree_height((&(*pNode)->right));
    }
    return 0;
}

void _tree_rotate_left(TreeNode **pNode) {
    TreeNode *nodeRight = (*pNode)->right;
    (*pNode)->right = nodeRight->left;
    nodeRight->left = *pNode;
    *pNode = nodeRight;
}

void _tree_rotate_left_right(TreeNode **pNode) {
    if (*pNode != NULL) {
        _tree_rotate_left(&((*pNode)->left));
        _tree_rotate_right(pNode);
    }
}

void _tree_rotate_right(TreeNode **pNode) {
    TreeNode *nodeLeft = (*pNode)->left;
    (*pNode)->left = nodeLeft->right;
    nodeLeft->right = *pNode;
    *pNode = nodeLeft;
}

void _tree_rotate_right_left(TreeNode **pNode) {
    if (*pNode != NULL) {
        _tree_rotate_right(&((*pNode)->right));
        _tree_rotate_left(pNode);
    }
}

void _tree_balance(TreeNode **pNode) {
    int balanceFactor;
    if (*pNode == NULL) return;
    balanceFactor = _tree_balance_factor(pNode);
    if (balanceFactor > 1) {
        if (_tree_balance_factor(&((*pNode)->left)) > 0) {
            _tree_rotate_right(pNode);
        } else {
            _tree_rotate_left_right(pNode);
        }
    } else if (balanceFactor < -1) {
        if (_tree_balance_factor(&((*pNode)->right)) < 0) {
            _tree_rotate_left(pNode);
        } else {
            _tree_rotate_right_left(pNode);
        }
    }
}

int _tree_balanced(TreeNode **pNode) {
    if (*pNode != NULL) {
        int factor = _tree_balance_factor(pNode);
        if (factor <= 1 && factor >= -1) {
            return _tree_balanced(&((*pNode)->left)) && _tree_balanced(&((*pNode)->right));
        }
        return 0;
    }
    return 1;
}

TreeItem *_tree_search(TreeNode **node, TreeItemKey key) {
    if (*node != NULL) {
        long comparison = tree_item_compare(key, tree_item_key((*node)->item));
        if (comparison == 0) {
            return &(*node)->item;
        }
        if (comparison < 0) {
            return _tree_search(&((*node)->left), key);
        }
        return _tree_search(&((*node)->right), key);
    }
    return tree_item_nil();
}

void _tree_print(TreeNode **leaf) {
    if (*leaf != NULL) {
        _tree_print(&((*leaf)->left));
        tree_item_print((*leaf)->item);
        _tree_print(&((*leaf)->right));
    }
}

void _tree_destroy(TreeNode **leaf) {
    if (*leaf != NULL) {
        _tree_destroy(&((*leaf)->left));
        _tree_destroy(&((*leaf)->right));
        treenode_destroy(*leaf);
    }
}