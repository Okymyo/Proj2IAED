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
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
void database_destroy(Database *database);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
void database_cheque(Database *database, unsigned long valor, unsigned long refe, unsigned long refb, unsigned long refc);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
void database_process(Database *database);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
void database_processr(Database *database, unsigned long refc);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
void database_infocheque(Database *database, unsigned long ref);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
void database_infoclient(Database *database, unsigned long ref);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
void database_info(Database *database);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
void database_quit(Database *database);