/* =====================
 * Grupo 5, IAED, LEIC-T
 * 81900 - Nuno Anselmo
 * 81943 - Gonçalo Matos
 * 82047 - André Mendes
   ===================== */

#include "database.h"

Database *database_init() {
    Database *database = malloc(sizeof(Database));
    database->tree = tree_init();
    database->table = table_init();
    return database;
}

void database_destroy(Database *database) {
    /* Free our tree, our table, and then the database itself */
    tree_destroy(database->tree);
    table_destroy(database->table);
    free(database);
}

void database_cheque(Database *database, unsigned long amount, unsigned long sender, unsigned long receiver,
                     unsigned long reference) {
    Client *client;

    /* Add the cheque to our table */
    table_insert(database->table, cheque_init(reference, amount, sender, receiver));

    /* Check whether the sender exists. If it doesn't, create it. If it does, change the values */
    if ((client = tree_search(database->tree, sender)) != NULL)
        client_update_issued(client, amount);
    else
        tree_insert(database->tree, client_init(sender, amount, 0, 1, 0));

    /* Do the same as above, but for the receiver */
    if ((client = tree_search(database->tree, receiver)) != NULL)
        client_update_receiving(client, amount);
    else
        tree_insert(database->tree, client_init(receiver, 0, amount, 0, 1));
}

void database_process(Database *database) {
    Cheque cheque, nil = cheque_nil();
    cheque = table_unqueue(database->table);

    /* If table_unqueue returns a nil cheque, it is empty */
    if (cheque_equal(&cheque, &nil)) {
        printf("Nothing to process\n");
        return;
    }

    /* Update the values in our clients (sender and receiver), and if any of them report being empty, remove them */
    if (client_update_issued(tree_search(database->tree, cheque_sender(&cheque)), -cheque_amount(&cheque)))
        tree_remove(database->tree, cheque_sender(&cheque));
    if (client_update_receiving(tree_search(database->tree, cheque_receiver(&cheque)), -cheque_amount(&cheque)))
        tree_remove(database->tree, cheque_receiver(&cheque));
}

void database_processr(Database *database, unsigned long reference) {
    Cheque cheque, nil = cheque_nil();
    cheque = table_remove(database->table, reference);

    /* If table_remove returns a nil cheque, the reference we have given doesn't have a matching cheque */
    if (cheque_equal(&cheque, &nil)) {
        printf("Cheque %lu does not exist\n", reference);
        return;
    }

    /* Update the values in our clients (sender and receiver), and delete them should they be empty */
    if (client_update_issued(tree_search(database->tree, cheque_sender(&cheque)), -cheque_amount(&cheque)))
        tree_remove(database->tree, cheque_sender(&cheque));
    if (client_update_receiving(tree_search(database->tree, cheque_receiver(&cheque)), -cheque_amount(&cheque)))
        tree_remove(database->tree, cheque_receiver(&cheque));
}

void database_infocheque(Database *database, unsigned long reference) {
    cheque_print(table_search(database->table, reference));
}

void database_infoclient(Database *database, unsigned long reference) {
    client_print(tree_search(database->tree, reference), "Cliente-info: ");
}

void database_info(Database *database) {
    if (tree_empty(database->tree)) {
        printf("No active clients\n");
        return;
    }

    /* Print our entire tree */
    tree_print(database->tree);
}

void database_quit(Database *database) {
    unsigned int clients = 0, cheques = 0;
    unsigned long sum = 0;
    Cheque cheque, nil = cheque_nil();

    clients = tree_count(database->tree);
    while (cheque = table_unqueue(database->table), !cheque_equal(&cheque, &nil)) {
        cheques++;
        sum += cheque.amount;
    }
    printf("%u %u %lu\n", clients, cheques, sum);
}