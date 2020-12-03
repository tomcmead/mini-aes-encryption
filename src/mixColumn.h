/*************************************************************************//**
* @file mixColumn.h
* @brief Mix Column configuration
*****************************************************************************/
#ifndef _MIX_COLUMN_H
#define _MIX_COLUMN_H

#include "../miniAES.h"

void mixColumn(nibbles_block_t &C);
int galoisAdd(int a, int b);
int galoisMult(int a, int b);
int galoisMod(int);

#endif