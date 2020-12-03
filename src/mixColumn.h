/*************************************************************************//**
* @file mixColumn.h
* @brief Function prototypes and nested includes for mixColumn operation
*****************************************************************************/
#ifndef _MIX_COLUMN_H
#define _MIX_COLUMN_H

/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include "../miniAES.h"

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void mixColumn(int *c);
int galoisAdd(int a, int b);
int galoisMult(int a, int b);
int galoisMod(int);

#endif