/*************************************************************************//**
* @file keys.h
* @brief Function prototypes, nested includes and constants for keys operation
*****************************************************************************/
#ifndef _KEYS_H
#define _KEYS_H

/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include "../miniAES.h"
#include "mixColumn.h"
#include "nibbleSub.h"

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/
#define KEY0 0xC
#define KEY1 0x3
#define KEY2 0xF
#define KEY3 0x0
#define RCON1 0x1
#define RCON2 0x2

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void keyGeneration(int *keys0, int *keys1, int *keys2, bool isEncrypting);

#endif