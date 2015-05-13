#pragma once
#include "includes.h"

/*
* Cheque type is a structure that has four fields:
*  -> A long, that is the reference of a cheque.
*  -> Another long that is the value for that cheque.
*  -> Another long that is that cheque's sender's reference.
*  -> Another long that is that cheque's receiver's reference.
* Size: 32 bytes [for implementations where size of long is 8].
*/
typedef struct {
    unsigned long reference;
	unsigned long value;
    unsigned long sender;
	unsigned long receiver;
} Cheque;

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
Cheque cheque_init(long reference, long value, long sender, long receiver);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
unsigned long cheque_reference(Cheque *cheque){
	return cheque->reference;
}

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
unsigned long cheque_value(Cheque *cheque){
	return cheque->value;
}

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
unsigned long cheque_sender(Cheque *cheque){
	return cheque->sender;
}

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
unsigned long cheque_receiver(Cheque *cheque){
	return cheque->receiver;
}