/*************************************************************************//**
* @file nibbleSub.h
* @brief Function prototypes and nested includes for nibbleSub operation
*****************************************************************************/
#ifndef _NIBBLE_SUB_H
#define _NIBBLE_SUB_H

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
int nibbleSub(int b, bool isEncrypting);
int sBox(int input);
int sBoxInverse(int input);

#endif