#pragma once
#include "includes.h"

/*
* Client type is a structure that has three fields:
*  -> A long, that is the reference of a client.
*  -> Another long that is the balance of a client.
*  -> Another long that is the outstanding of a client.
* Size: 24 bytes.
*/
typedef struct {
    unsigned long reference;
    unsigned long balance;
    unsigned long outstanding;
} Client;

/*
* Our ClientKey is going to be a long, the reference of the client.
*/
typedef unsigned long ClientKey;

/*
* Creates a new client.
* @param reference   Reference of the new client.
* @param balance     Balance of the new client.
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
* Gives the key of a given client.
* @param client Client that we want to obtain the key.
* @return       The key of the client.
*/
unsigned long client_key(Client client);

/*
* Prints a given client.
* @param client Client that we want to print.
*/
void client_print(Client client);