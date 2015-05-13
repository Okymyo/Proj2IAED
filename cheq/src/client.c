#include "client.h"

Client client_init(unsigned long reference, unsigned long balance, unsigned long outstanding) {
    Client new;
    new.reference = reference;
    new.amountReceivedPending = balance;
    new.amountIssuedPending = outstanding;
    return new;
}

int client_compare(ClientKey clientKey1, ClientKey clientKey2) {
    if(clientKey1 > clientKey2) return 1;
    if(clientKey1 < clientKey2) return -1;
    return 0;
}

void client_print(Client client) {
    printf("[Client] -> Refererence:%li, Balance:%li, Outstanding:%li\n", client.reference, client.amountReceivedPending,
           client.amountIssuedPending);
}

int client_update_issued(Client *client, long amount) {
    client->amountIssuedPending += amount;
    if(amount > 0)
        client->chequesIssuedPending++;
    else
        client->chequesIssuedPending--;
    return client->chequesIssuedPending && client->chequesReceivingPending;
}

int client_update_received(Client *client, long amount) {
    client->amountReceivedPending += amount;
    if(amount > 0)
        client->chequesReceivingPending++;
    else
        client->chequesReceivingPending--;
    return client->chequesIssuedPending && client->chequesReceivingPending;
}

unsigned long client_key(Client client) {
    return client.reference;
}