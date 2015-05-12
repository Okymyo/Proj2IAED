#include "main.h"

#define QUIT 1
#define CONTINUE 0

#define ARGUMENT_SIZE 12
#define LINESIZE 512
#define ARGUMENTS_NUMBER 5

void parseArguments(int *argc, char argv[ARGUMENTS_NUMBER][ARGUMENT_SIZE]) {
    char line[LINESIZE];
    int linePosition;
    char charRead;

    char insideWord = 0;
    int wordPosition = 0;

    fgets(line, LINESIZE, stdin);
    for(linePosition = 0; (charRead = line[linePosition]) != '\n' && *argc < ARGUMENTS_NUMBER; linePosition++){
        if(!insideWord && charRead != ' '){
            insideWord = 1;
            wordPosition = 0;
        }
        if(insideWord && charRead != ' '){
            argv[*argc][wordPosition] = charRead;
            wordPosition++;
        }
        if(insideWord && charRead == ' '){
            argv[*argc][wordPosition] = '\0';
            insideWord = 0;
            (*argc)++;
        }
    }
	argv[*argc][wordPosition] = '\0';
}

/* We have to give tree and table here */
int requestInput(Tree *tree, Table *table) {
    int argc = 0;
    char argv[ARGUMENTS_NUMBER][ARGUMENT_SIZE];
    parseArguments(&argc, argv);

    if(strcmp(argv[0], "cheque") == 0){
		unsigned long valor = 0, refe = 0, refb = 0, refc = 0;
		sscanf(argv[1], "%lu", &valor);
		sscanf(argv[2], "%lu", &refe);
		sscanf(argv[3], "%lu", &refb);
		sscanf(argv[4], "%lu", &refc);
		table_insert(table, cheque_init(refc, valor, refe, refb));
    }
	else if(strcmp(argv[0], "processa") == 0){
		table_unqueue(table);
    }
	else if(strcmp(argv[0], "processaR") == 0){
		unsigned long refc = 0;
		sscanf(argv[1], "%lu", &refc);
		table_remove(table, refc);
    }
	else if(strcmp(argv[0], "infocheque") == 0){
		
    }
	else if(strcmp(argv[0], "infocliente") == 0){

    }
	else if(strcmp(argv[0], "info") == 0){

    }
	else if(strcmp(argv[0], "sair") == 0){
		table_print(table);
		tree_print(tree);
        return QUIT;
    }
    return CONTINUE;
}

int main(int argc, const char *argv[]) {
	Tree *tree = tree_init();
	Table *table = table_init();
    while(requestInput(tree, table) != QUIT);
	tree_destroy(tree);
	table_destroy(table);
    return 0;
}