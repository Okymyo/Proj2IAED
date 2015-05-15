/* =====================
 * Grupo 5, IAED, LEIC-T
 * 81900 - Nuno Anselmo
 * 81943 - Gonçalo Matos
 * 82047 - André Mendes
   ===================== */

/* ============= "Short" explanation of how everything works =============
	This program is able to handle cheques and clients, receiving cheques
		with given values, and automatically generating clients.
		It then allows us to process said cheques, effectively eliminating
		them, and producing effects on the clients associated with them.
	
	Our file structure is as follows (includes.h excluded):
		main
			database
				cheque
				client
				table
					table_item
						cheque
				tree
					tree_item
						client

	Files are only aware of files directly below them in the structure.
	This means that, for example, "table" isn't aware of "cheque".
	The only way for it to reach "cheque" is through "table_item", which
		works as if it were a translator: an abstraction barrier.

	Main receives our inputs, and handles them, calling functions in
		database with the correct parameters.
	Database takes those inputs and using functions defined in cheque
		and client, and using the data structures defined in table and
		tree, and processes them.
	Cheque handles all functions directly related to cheques, and Client
		all the functions directly related to clients.
	Table is responsible for our table data structure, which is a hash
		table with a built-in queue. Basically, it is a hash table that
		can also store order. It includes table_item, which is how it
		understands how to store the cheques.
	Tree is responsible for our tree, which is an auto-balancing AVL.
		It includes tree_item, which is what it uses to be able to
		handle clients correctly.

	To switch out the data structures in use, for example the tree, all
		that needs to be done is to switch that file, make sure database
		calls the new functions from the new structure, and adapt
		tree_item so that it correctly handles the data it is storing.

	That is, summed up, how our program is structured.
   ======================================================================= */

#include "includes.h"
#include "database.h"

#define ARGUMENT_SIZE 13
#define ARGUMENTS_NUMBER 5
#define LINESIZE 512

#define QUIT 1
#define CONTINUE 0

/*
* Parses arguments just like main would. Only able to parse ARGUMENTS_NUMBER arguments each with a maximum length of ARGUMENT_SIZE-1.
* @param argc Pointer to an int where its going to be stored the number of arguments parsed.
* @param argv Array of "strings", where it will store all the arguments parsed. Command used is in argv[0].
*/
void parseArguments(int *argc, char argv[ARGUMENTS_NUMBER][ARGUMENT_SIZE]);

/*
* Requests input from user and modifies/updates a given database depending on the user input.
* @param database A pointer to the database that we want to modify/update depending on the user input.
* @return         CONTINUE, if it should continue asking for input, QUIT if it should quit.
*/
int requestInput(Database *database);
