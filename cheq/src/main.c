#include "main.h"

#define QUIT 1
#define CONTINUE 0

#define ARGUMENT_SIZE 12
#define ARGUMENTS_NUMBER 4

void parseArguments(int *argc, char argv[ARGUMENTS_NUMBER][ARGUMENT_SIZE]) {
    char line[1024];
    int linePosition;
    char charRead;

    char insideWord = 0;
    int wordPosition = 0;

    fgets(line, 1024, stdin);
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
        argv[*argc][wordPosition] = '\0';
    }
}

/* We have to give tree and table here */
int requestInput(Tree *tree) {
    int argc = 0;
    char argv[ARGUMENTS_NUMBER][ARGUMENT_SIZE];
    parseArguments(&argc, argv);

    if(strcmp(argv[0], "cheque") == 0){

    }else if(strcmp(argv[0], "sair") == 0){
        return QUIT;
    }
    return CONTINUE;
}

int main(int argc, const char *argv[]) {
    /*while(requestInput(NULL) != QUIT);
    return 0;*/
	
	long i;
	Table *table;
	
	table = table_init();
	for (i = 0; i < 5; i++)
		table_insert(table, cheque_init(i, i, i, i));
		
	table_remove(table, cheque_init(1, 1, 1, 1));
	table_print(table);
	table_destroy(table);
	return 0;
}