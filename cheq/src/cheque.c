#include "cheque.h"

Cheque cheque_init(long reference, long value, long sender, long receiver) {
    Cheque new;
	new.reference = reference;
    new.value = value;
    new.sender = sender;
    new.receiver = receiver;
    return new;
}

unsigned long cheque_reference(Cheque *cheque){
	return cheque->reference;
}

unsigned long cheque_value(Cheque *cheque){
	return cheque->value;
}

unsigned long cheque_sender(Cheque *cheque){
	return cheque->sender;
}

unsigned long cheque_receiver(Cheque *cheque){
	return cheque->receiver;
}