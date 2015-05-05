#include <stdio.h>
#include "client_tree.h"


int main() {
    TreeNode root;
    client_tree_init(&root);
    client_tree_insert(&root, client_init(8, 2));
    client_tree_insert(&root, client_init(2, 2));
    client_tree_insert(&root, client_init(1, 2));
    client_tree_insert(&root, client_init(4, 2));
    client_tree_insert(&root, client_init(10, 4));
    client_tree_insert(&root, client_init(12, 2));
    client_tree_print(&root);
    printf("A arvore tem %d elementos!\n", client_tree_count(&root));
    printf("O tamanho da nossa arvore e %d!\n", client_tree_height(&root));
    client_tree_destroy(&root);
    return 0;
}