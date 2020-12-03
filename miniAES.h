/*************************************************************************//**
* @file miniAES.h
* @brief Mini AES configuration
*****************************************************************************/

#ifndef _MINI_AES_H
#define _MINI_AES_H

#define NIBBLES_BLOCK_SIZE 4
#define NUM_OF_ROUNDS 3

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef struct{
    int n0;
    int n1;
    int n2;
    int n3;
}nibbles_block_t;

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/

int binary2Dec(bool *binary, int bits);
void displayArray(int *arr);
void dec2Binary(int dec, bool *binaryNum);


#endif