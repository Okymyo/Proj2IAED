/* =====================
 * Grupo 5, IAED, LEIC-T
 * 81900 - Nuno Anselmo
 * 81943 - Gonçalo Matos
 * 82047 - André Mendes
   ===================== */

#pragma once

#include "includes.h"
#include "tree.h"
#include "table.h"

typedef struct {
    Tree *tree;
    Table *table;
} Database;

/*
* Creates a new database.
* @return A pointer to a structure of the type Database.
*/
Database *database_init();

/*
* Adds a cheque to a given database.
* @param database  A pointer to the database that we are adding the cheque into.
* @param amount    Value of the cheque
* @param sender    Reference of the cheque's sender
* @param receiver  Reference of the cheque's receiver
* @param reference Reference of the cheque
*/
void database_cheque(Database *database, unsigned long value, unsigned long sender, unsigned long receiver,
                     unsigned long reference);

/*
* Processes the first added cheque of a given database.
* @param database A pointer to the database where the first added cheque will be processed.
*/
void database_process(Database *database);

/*
* Processes the cheque with a given reference in a given database.
* @param database  A pointer to the database where the cheque with the given reference will be processed.
* @param reference The reference of the cheque that we want to process.
*/
void database_processr(Database *database, unsigned long reference);

/*
* Displays the information of a cheque with a given reference in a given database.
* @param database  A pointer to the database where the cheque with the given reference will have its information displayed.
* @param reference The reference of the cheque that we want to display.
*/
void database_infocheque(Database *database, unsigned long reference);

/*
* Displays the information of a active client with a given reference in a given database.
* @param database  A pointer to the database where the client with the given reference will have its information displayed.
* @param reference The reference of the client that we want to display.
*/
void database_infoclient(Database *database, unsigned long reference);

/*
* Displays the information of all active clients of a given database.
* @param database A pointer to the database where we want to have all the active clients information displayed.
*/
void database_info(Database *database);

/*
* Will quit a given database.
* @param database A pointer to the database that we want to quit from.
*/
void database_quit(Database *database);

/*
* Deallocates all of the resources in use by a given database.
* @param Database that we are deallocating.
*/
void database_destroy(Database *database);
