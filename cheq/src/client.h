#ifndef C_CLIENTE_H
#define C_CLIENTE_H

typedef long Key;
typedef struct {
    long reference;
    long money;
} Client;

Client *client_init(long, long);

Client *client_nil();

long client_compare(Key, Key);

long client_key(Client*);

void client_print(Client*);

void client_destroy(Client*);

#endif
