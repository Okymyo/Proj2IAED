#include <stdio.h>
#include <stdlib.h>
#include "client_tree.h"
#include "client.h"


int main() {
    int i;
    ClientTree tree;
    client_tree_init(&tree);
    for(i = 0; i < 1000; i++){
        client_tree_insert(&tree, client_init(i*7/2, i, i));
    }
    client_tree_print(&tree);
    printf("A nossa tree esta balanced? %s\n", (client_tree_balanced(&tree) ? "Sim." : "Nao!"));
    printf("A arvore tem %d elementos!\n", client_tree_count(&tree));
    printf("O height da nossa arvore e %d!\n", client_tree_height(&tree));
    client_tree_destroy(&tree);
    return 0;
}