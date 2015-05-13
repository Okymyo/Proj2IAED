#include "cheque.h"

Cheque cheque_init(unsigned long reference, unsigned long amount, unsigned long sender, unsigned long receiver) {
    Cheque new;
	new.reference = reference;
    new.amount = amount;
    new.sender = sender;
    new.receiver = receiver;
    return new;
}

unsigned long cheque_reference(Cheque *cheque){
	return cheque->reference;
}

unsigned long cheque_amount(Cheque *cheque){
	return cheque->amount;
}

unsigned long cheque_sender(Cheque *cheque){
	return cheque->sender;
}

unsigned long cheque_receiver(Cheque *cheque){
	return cheque->receiver;
}

void cheque_print(Cheque *cheque){
	printf("%lu %lu %lu %lu", cheque_reference(cheque), cheque_amount(cheque), cheque_sender(cheque), cheque_receiver(cheque));
}