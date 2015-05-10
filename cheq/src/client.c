#include <stdio.h>
#include <stdlib.h>
#include "client.h"

Client client_init(long reference, long balance, long outstanding) {
    Client new;
    new.reference = reference;
    new.balance = balance;
    new.outstanding = outstanding;
    return new;
}

Client *client_nil() {
    return NULL;
}

long client_compare(ClientKey key, ClientKey key1) {
    return key - key1;
}

long client_key(Client client) {
    return client.reference;
}

void client_print(Client client) {
    printf("[Client] -> Refererence:%li, Balance:%li, Outstanding:%li\n", client.reference, client.balance,
           client.outstanding);
}
