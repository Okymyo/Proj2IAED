#pragma once
#include "includes.h"

/*
* Client type is a structure that has three fields:
*  -> A long, that is the reference of a client.
*  -> Another long that is the balancePending of a client.
*  -> Another long that is the outstanding of a client.
* Size: 24 bytes [for implementations where size of long is 8].
*/
typedef struct {
    unsigned long reference;
    unsigned long amountIssuedPending;
    unsigned long amountReceivedPending;
    unsigned int chequesIssuedPending;
    unsigned int chequesReceivingPending;
} Client;

/*
* Our ClientKey is going to be a long, the reference of the client.
*/
typedef unsigned long ClientKey;

/*
* Creates a new client.
* @param reference   Reference of the new client.
* @param balancePending     Balance of the new client.
* @param outstanding Outstanding of the new client.
* @return            The newly created client.
*/
Client client_init(unsigned long reference, unsigned long balance, unsigned long outstanding);

/*
* Compares two client keys.
* @param clientKey1 First key of the first client that we want to compare.
* @param clientKey2 Second key of the second client that we want to compare.
* @return           Returns > 0, if clientKey1 is bigger than clientKey2, < 0 if clientKey1 is less than clientKey2, == 0 if both keys are the same.
*/
int client_compare(ClientKey clientKey1, ClientKey clientKey2);

/*
* Prints a given client.
* @param client Client that we want to print.
*/
void client_print(Client client);

/*
 * Updates the issued amount of a given client.
 * @param client The client that we want to update the issued amount pending.
 * @param amount Amount to update the issued amount pending of the client.
 * @return       Returns false if the client is still active after the update, otherwise returns true.
 */
int client_update_issued(Client *client, long amount);

/*
 * Updates the received amount of a given client.
 * @param client The client that we want to update the received amount pending.
 * @param amount Amount to update the issued amount received of the client.
 * @return       Returns false if the client is still active after the update, otherwise returns true.
 */
int client_update_received(Client *client, long amount);

/*
* Gives the key of a given client.
* @param client Client that we want to obtain the key.
* @return       The key of the client.
*/
unsigned long client_key(Client client);
