#include "main.h"

int main() {
    long i;
    Tree *tree = tree_init();
    for (i = 0; i < 1000; i++) {
        tree_insert(tree, client_init(i , i, i));
    }
    tree_print(tree);
    printf("A nossa tree esta balanced? %s\n", (tree_balanced(tree) ? "Sim." : "Nao!"));
    printf("A arvore tem %d elementos!\n", tree_count(tree));
    printf("O height da nossa arvore e %d!\n", tree_height(tree));
    printf("Esta vazia? %s\n", (tree_empty(tree) ? "Sim." : "Nao!"));
    tree_destroy(tree);
    printf("%lu", sizeof(Tree));
    return 0;
}