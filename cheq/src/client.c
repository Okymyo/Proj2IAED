#include "client.h"

Client client_init(unsigned long reference, unsigned long balance, unsigned long outstanding) {
    Client new;
    new.reference = reference;
    new.balance = balance;
    new.outstanding = outstanding;
    return new;
}

int client_compare(ClientKey clientKey1, ClientKey clientKey2) {
    if(clientKey1 > clientKey2) return 1;
    if(clientKey1 < clientKey2) return -1;
    return 0;
}

unsigned long client_key(Client client) {
    return client.reference;
}

void client_print(Client client) {
    printf("[Client] -> Refererence:%li, Balance:%li, Outstanding:%li\n", client.reference, client.balance,
           client.outstanding);
}