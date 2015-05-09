#ifndef C_CLIENTE_H
#define C_CLIENTE_H

typedef long ClientKey;
typedef struct {
    long reference;
    long balance;
    long outstanding;
} Client;

Client *client_init(long, long, long);

Client *client_nil();

long client_compare(ClientKey, ClientKey);

long client_key(Client *);

void client_print(Client *);

void client_destroy(Client *);

#endif
