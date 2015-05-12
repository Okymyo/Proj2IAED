#include "database.h"

Database *database_init(){
	Database *database = malloc(sizeof(Database));
	database->tree = tree_init();
	database->table = table_init();
	return database;
}

void database_destroy(Database *database){
	tree_destroy(database->tree);
	table_destroy(database->table);
	free(database);
}

void database_cheque(Database *database, unsigned long value, unsigned long sender, unsigned long receiver, unsigned long reference){
}

void database_process(Database *database){
}

void database_processr(Database *database, unsigned long reference){
}

void database_infocheque(Database *database, unsigned long reference){
}

void database_infoclient(Database *database, unsigned long reference){
}

void database_info(Database *database){
}

void database_quit(Database *database){
}