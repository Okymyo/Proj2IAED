#pragma once
#include "includes.h"

/*
* Client type is a structure that has three fields:
*  -> A long, that is the reference of a client.
*  -> Another long that is the amount of money issued of a client.
*  -> Another long that is the amount of money to be received that is pending of a client.
*  -> A int that contains the number of issued cheques that are pending of a client.
*  -> Another int that contains the number of cheques to be received that are pending of a client.
* Size: 32 bytes [for implementations where size of long is 8].
*/
typedef struct {
    unsigned long reference;
    unsigned long amountIssuedPending;
    unsigned long amountReceivingPending;
    unsigned int chequesIssuedPending;
    unsigned int chequesReceivingPending;
} Client;

/*
* Our ClientKey is going to be a long, the reference of the client.
*/
typedef unsigned long ClientKey;

/*
* Creates a new client.
* @param reference               Reference of the new client.
* @param amountIssuedPending     Amount money issued pending of the new client.
* @param amountReceivingPending  Amount money to be received that is pending of the new client.
* @param chequesIssuedPending    Number of issued cheques that are pending of the new client.
* @param chequesReceivingPending Number of cheques to be received that are pending of the new client.
* @return                        The newly created client.
*/
Client client_init(unsigned long reference, unsigned long amountIssuedPending, unsigned long amountReceivingPending, unsigned int chequesIssuedPending, unsigned int chequesReceivingPending);

/*
* Compares two client keys.
* @param clientKey1 First key of the first client that we want to compare.
* @param clientKey2 Second key of the second client that we want to compare.
* @return           Returns > 0, if clientKey1 is bigger than clientKey2, < 0 if clientKey1 is less than clientKey2, == 0 if both keys are the same.
*/
int client_compare(ClientKey clientKey1, ClientKey clientKey2);

/*
* Prints a given client.
* @param client Pointer to the client that we want to print.
* @param prefix Prefix that we want to append before the client info is printed.
*/
void client_print(Client *client, char * prefix);

/*
 * Updates the issued amount of a given client.
 * @param client Pointer to the client that we want to update the issued amount pending.
 * @param amount Amount to update the issued amount pending of the client.
 * @return       Returns false if the client is still active after the update, otherwise returns true.
 */
int client_update_issued(Client *client, long amount);

/*
 * Updates the receiving amount of a given client.
 * @param client Pointer to the client that we want to update the receiving amount pending.
 * @param amount Amount to update the issued amount receiving of the client.
 * @return       Returns false if the client is still active after the update, otherwise returns true.
 */
int client_update_receiving(Client *client, long amount);

/*
* Gives the key of a given client.
* @param client Pointer to the client that we want to obtain the key.
* @return       The key of the client.
*/
unsigned long client_key(Client *client);

/*
* Gives the reference of a given client.
* @param client Pointer to the client that we want to obtain the reference.
* @return       The reference of the client.
*/
unsigned long client_reference(Client *client);

/*
* Gives the amount issued pending of a given client.
* @param client Pointer to the client that we want to obtain the amount issued pending.
* @return       The amount issued pending of the client.
*/
unsigned long client_amountIssuedPending(Client *client);

/*
* Gives the amount receiving pending of a given client.
* @param client Pointer to the client that we want to obtain the amount receiving pending.
* @return       The amount receiving pending of the client.
*/
unsigned long client_amountReceivingPending(Client *client);

/*
* Gives the number of issued pending cheques of a given client.
* @param client Pointer to the client that we want to obtain the number of issued pending.
* @return       The number of issued pending cheques of the client.
*/
unsigned int client_chequesIssuedPending(Client *client);

/*
* Gives the number of receiving cheques of a given client.
* @param client Pointer to the client that we want to obtain the number of receiving cheques.
* @return       The number of receiving cheques of the client.
*/
unsigned int client_chequesReceivingPending(Client *client);
