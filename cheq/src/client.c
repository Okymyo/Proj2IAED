#include "client.h"

Client client_init(long reference, long balance, long outstanding) {
    Client new;
    new.reference = reference;
    new.balance = balance;
    new.outstanding = outstanding;
    return new;
}

int client_compare(ClientKey clientKey1, ClientKey clientKey2) {
    /* Doing some implicit casts */
    return (int) (clientKey1 - clientKey2);
}

long client_key(Client client) {
    return client.reference;
}

void client_print(Client client) {
    printf("[Client] -> Refererence:%li, Balance:%li, Outstanding:%li\n", client.reference, client.balance,
           client.outstanding);
}