#include "client.h"

Client client_init(unsigned long reference, unsigned long amountIssuedPending, unsigned long amountReceivingPending, unsigned int chequesIssuedPending, unsigned int chequesReceivingPending) {
    Client new;
    new.reference = reference;
    new.amountIssuedPending = amountIssuedPending;
    new.amountReceivingPending = amountReceivingPending;
    new.chequesIssuedPending = chequesIssuedPending;
    new.chequesReceivingPending = chequesReceivingPending;
    return new;
}

int client_compare(ClientKey clientKey1, ClientKey clientKey2) {
    if(clientKey1 > clientKey2) return 1;
    if(clientKey1 < clientKey2) return -1;
    return 0;
}

void client_print(Client *client) {
    printf("[Client] -> Refererence:%li, Balance:%li, Outstanding:%li\n", client->reference, client->amountReceivingPending,
           client->amountIssuedPending);
}

int client_update_issued(Client *client, long amount) {
    client->amountIssuedPending += amount;
    if(amount > 0)
        client->chequesIssuedPending++;
    else
        client->chequesIssuedPending--;
    return client->chequesIssuedPending && client->chequesReceivingPending;
}

int client_update_receiving(Client *client, long amount) {
    client->amountReceivingPending += amount;
    if(amount > 0)
        client->chequesReceivingPending++;
    else
        client->chequesReceivingPending--;
    return client->chequesIssuedPending && client->chequesReceivingPending;
}

unsigned long client_key(Client *client) {
    return client->reference;
}

unsigned long client_reference(Client *client) {
    return client->reference;
}

unsigned long client_amountIssuedPending(Client *client) {
    return client->amountIssuedPending;
}

unsigned long client_amountReceivingPending(Client *client) {
    return client->amountReceivingPending;
}

unsigned int client_chequesIssuedPending(Client *client) {
    return client->chequesIssuedPending;
}

unsigned int client_chequesReceivingPending(Client *client) {
    return client->chequesReceivingPending;
}
