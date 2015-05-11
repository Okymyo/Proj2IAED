#include "main.h"

int main() {
    /*long i;
    Tree tree;
    tree_init(&tree);
    for (i = 0; i < 1000; i++) {
        tree_insert(&tree, client_init(i , i, i));
    }
    tree_print(&tree);
    printf("A nossa tree esta balanced? %s\n", (tree_balanced(&tree) ? "Sim." : "Nao!"));
    printf("A arvore tem %d elementos!\n", tree_count(&tree));
    printf("O height da nossa arvore e %d!\n", tree_height(&tree));
    tree_destroy(&tree);
    return 0;*/
	
	long long test = 23622;
	unsigned int result = hash(test);
	printf("%u\n", result);
	printf("%i\n", sizeof(long long));
	printf("%i\n", sizeof(unsigned int));
}