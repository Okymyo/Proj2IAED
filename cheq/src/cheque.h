#pragma once
#include "includes.h"

typedef struct {
    unsigned long reference;
	unsigned long value;
    unsigned long sender;
	unsigned long receiver;
} Cheque;

Cheque cheque_init(long reference, long value, long sender, long receiver);