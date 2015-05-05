#include <stdio.h>
#include <stdlib.h>
#include "client.h"

Client client_init(long reference, long money) {
    Client new = (Client) malloc(sizeof(struct client));
    new->reference = reference;
    new->money = money;
    return new;
}

Client client_nil() {
    return NULL;
}

long client_compare(Key key, Key key1) {
    return key - key1;
}

long client_key(Client client1) {
    return client1->reference;
}

void client_print(Client c) {
    printf("[Client] -> Refererence:%li, Money:%li\n", c->reference, c->money);
}

void client_destroy(Client client) {
    free(client);
}
