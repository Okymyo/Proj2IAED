#include "includes.h"
#include "tree.h"
#include "table.h"

typedef struct {
	Tree *tree;
	Table *table;
} Database;

Database *database_init();

void database_destroy(Database *database);

void database_cheque(Database *database, unsigned long valor, unsigned long refe, unsigned long refb, unsigned long refc);

void database_process(Database *database);

void database_processr(Database *database, unsigned long refc);

void database_infocheque(Database *database, unsigned long ref);

void database_infoclient(Database *database, unsigned long ref);

void database_info(Database *database);

void database_quit(Database *database);