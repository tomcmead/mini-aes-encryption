#ifndef _KEYS_H
#define _KEYS_H

#include "../miniAES.h"
#include "mixColumn.h"
#include "nibbleSub.h"

#define KEY0 0xC
#define KEY1 0x3
#define KEY2 0xF
#define KEY3 0x0
#define RCON1 0x1
#define RCON2 0x2

void keyGeneration(int *keys0, int *keys1, int *keys2);

#endif