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

void database_cheque(Database *database, unsigned long amount, unsigned long sender, unsigned long receiver, unsigned long reference){
	client_update_issued(tree_search(database->tree, sender), amount);
	client_update_receiving(tree_search(database->tree, receiver), amount);
	table_insert(database->table, cheque_init(reference, amount, sender, receiver));
}

void database_process(Database *database){
	Cheque cheque;
	cheque = table_unqueue(database->table);
	if (client_update_issued(tree_search(database->tree, cheque_sender(cheque)), -cheque_amount(cheque)))
		tree_remove(database->tree, cheque_sender(cheque));
	if (client_update_receiving(tree_search(database->tree, cheque_receiver(cheque)), -cheque_amount(cheque)))
		tree_remove(database->tree, cheque_receiver(cheque));
}

void database_processr(Database *database, unsigned long reference){
	Cheque cheque;
	cheque = table_remove(database->table, reference);
	if (client_update_issued(tree_search(database->tree, cheque_sender(cheque)), -cheque_amount(cheque)))
		tree_remove(database->tree, cheque_sender(cheque));
	if (client_update_receiving(tree_search(database->tree, cheque_receiver(cheque)), -cheque_amount(cheque)))
		tree_remove(database->tree, cheque_receiver(cheque));
}

void database_infocheque(Database *database, unsigned long reference){
	cheque_print(table_search(database->table, reference));
}

void database_infoclient(Database *database, unsigned long reference){
	client_print(tree_search(database->tree, reference));
}

void database_info(Database *database){
	tree_print(database->tree);
}

void database_quit(Database *database){
	Cheque cheque;
	unsigned int clients = 0, cheques = 0;
	unsigned long sum;
	clients = tree_count(database->tree);
	while ((cheque = table_unqueue(database->table)) != cheque_nil()){
		cheques++;
		sum += cheque.amount;
	}
	printf("%u %u %lu", clients, cheques, sum);
}