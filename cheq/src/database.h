#pragma once
#include "includes.h"
#include "tree.h"
#include "table.h"

typedef struct {
	Tree *tree;
	Table *table;
} Database;

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
Database *database_init();

/*
* Deallocates all of the resources in use by a given database.
* @param Database that we are deallocating.
*/
void database_destroy(Database *database);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
*/
void database_cheque(Database *database, unsigned long value, unsigned long sender, unsigned long receiver, unsigned long reference);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
*/
void database_process(Database *database);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
*/
void database_processr(Database *database, unsigned long reference);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
*/
void database_infocheque(Database *database, unsigned long reference);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
*/
void database_infoclient(Database *database, unsigned long reference);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
*/
void database_info(Database *database);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
*/
void database_quit(Database *database);