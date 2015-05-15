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
* @param argv Array of "strings", with all the arguments parsed. Command used is in argv[0].
*/
void parseArguments(int *argc, char argv[ARGUMENTS_NUMBER][ARGUMENT_SIZE]);

/*
* Requests input from user and modifies/updates a given database depending on the user input.
* @param database A pointer to the database that we want to modify/update depending on the user input.
* @return         CONTINUE, if it should continue asking for input, QUIT if it should quit.
*/
int requestInput(Database *database);