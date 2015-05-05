#include <stdio.h>
#include <stdlib.h>
#include "client.h"

Client *client_init(long reference, long money) {
    Client *new = (Client*) malloc(sizeof(Client));
    new->reference = reference;
    new->money = money;
    return new;
}

Client *client_nil() {
    return NULL;
}

long client_compare(Key key, Key key1) {
    return key - key1;
}

long client_key(Client *client) {
    return client->reference;
}

void client_print(Client *client) {
    printf("[Client] -> Refererence:%li, Money:%li\n", client->reference, client->money);
}

void client_destroy(Client *client) {
    free(client);
}
