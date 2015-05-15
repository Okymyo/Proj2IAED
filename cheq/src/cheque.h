/* =====================
 * Grupo 5, IAED, LEIC-T
 * 81900 - Nuno Anselmo
 * 81943 - Goncalo Matos
 * 82047 - Andre Mendes
   ===================== */

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
    unsigned long amount;
    unsigned long sender;
    unsigned long receiver;
} Cheque;

/*
* Our ChequeKey is going to be a long, the reference of the cheque.
*/
typedef unsigned long ChequeKey;

/*
* Returns a cheque initialized with the given values
* @param reference Reference of the cheque
* @param amount    Value of the cheque
* @param sender    Reference of the cheque's sender
* @param receiver  Reference of the cheque's receiver
* @return          Cheque initialized with previous values.
*/
Cheque cheque_init(unsigned long reference, unsigned long amount, unsigned long sender, unsigned long receiver);

/*
* Returns the amount of a given cheque.
* @param cheque Pointer to the cheque from which we're extracting the amount.
* @return       Amount that we are returning.
*/
unsigned long cheque_amount(Cheque *cheque);

/*
* Returns the sender of a given cheque.
* @param cheque Pointer to the cheque from which we're extracting the sender.
* @return       Sender that we are returning.
*/
unsigned long cheque_sender(Cheque *cheque);

/*
* Returns the receiver of a given cheque.
* @param cheque Pointer to the cheque from which we're extracting the receiver.
* @return       Receiver that we are returning.
*/
unsigned long cheque_receiver(Cheque *cheque);

/*
* Prints a given cheque
* @param cheque Pointer to the cheque we are printing.
*/
void cheque_print(Cheque *cheque);

/*
* Returns a cheque that will be equated as nil.
* @return Cheque that is nil.
*/
Cheque cheque_nil();

/*
* Checks whether two given cheques are the one and the same.
* @param cheque1 Cheque we are comparing.
* @param cheque2 Cheque we are comparing it to.
* @return        True if the cheques are the same, False otherwise.
*/
int cheque_equal(Cheque *cheque1, Cheque *cheque2);

/*
* Gives the key of a given cheque.
* @param cheque Pointer to the cheque that we want to obtain the key.
* @return       The key of the cheque.
*/
ChequeKey cheque_key(Cheque *cheque);
