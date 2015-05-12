#include "cheque.h"

Cheque cheque_init(long reference, long value, long sender, long receiver) {
    Cheque new;
	new.reference = reference;
    new.value = value;
    new.sender = sender;
    new.receiver = receiver;
    return new;
}