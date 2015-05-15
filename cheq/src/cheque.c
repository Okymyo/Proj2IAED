/* =====================
 * Grupo 5, IAED, LEIC-T
 * 81900 - Nuno Anselmo
 * 81943 - Gonçalo Matos
 * 82047 - André Mendes
   ===================== */

#include "cheque.h"

Cheque cheque_init(unsigned long reference, unsigned long amount, unsigned long sender, unsigned long receiver) {
    Cheque new;
    new.reference = reference;
    new.amount = amount;
    new.sender = sender;
    new.receiver = receiver;
    return new;
}

unsigned long cheque_amount(Cheque *cheque) {
    return cheque->amount;
}

unsigned long cheque_sender(Cheque *cheque) {
    return cheque->sender;
}

unsigned long cheque_receiver(Cheque *cheque) {
    return cheque->receiver;
}

void cheque_print(Cheque *cheque) {
    printf("Cheque-info: %lu %lu %lu --> %lu\n", cheque->reference, cheque->amount, cheque->sender, cheque->receiver);
}

Cheque cheque_nil() {
    Cheque new;
    new.reference = 0;
    new.amount = 0;
    new.sender = 0;
    new.receiver = 0;
    return new;
}

int cheque_equal(Cheque *cheque1, Cheque *cheque2) {
    return cheque_key(cheque1) == cheque_key(cheque2);
}

ChequeKey cheque_key(Cheque *cheque) {
    return cheque->reference;
}
