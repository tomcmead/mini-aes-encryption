/*************************************************************************//**
* @file keys.cpp
* @brief  Generates keys for AES encryption/decryption
*****************************************************************************/
/*----------------------------------------------------------------------------
  include files
----------------------------------------------------------------------------*/
#include "keys.h"

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Generates 3 rounds of keys
* @param int *keys0, int *keys1, int *keys2 pointer to start of nibble array 
for each binary keys
* @return None
*****************************************************************************/
void keyGeneration(int *keys0, int *keys1, int *keys2, bool isEncrypting){
  
    int w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11;

    w0 = KEY0;
    w1 = KEY1;
    w2 = KEY2;
    w3 = KEY3;

    w4 = galoisAdd(w0, nibbleSub(w3, 1));
    w4 = galoisAdd(w4, RCON1);
    w5 = galoisAdd(w1, w4);
    w6 = galoisAdd(w2, w5);
    w7 = galoisAdd(w3, w6);

    w8 = galoisAdd(w4, nibbleSub(w7, 1));
    w8 = galoisAdd(w8, RCON2);
    w9 = galoisAdd(w5, w8);
    w10 = galoisAdd(w6, w9);
    w11 = galoisAdd(w7, w10); 

    keys0[0] = w0;  keys0[1] = w1;  keys0[2] = w2;  keys0[3] = w3; 
    keys1[0] = w4;  keys1[1] = w5;  keys1[2] = w6;  keys1[3] = w7; 
    keys2[0] = w8;  keys2[1] = w9;  keys2[2] = w10;  keys2[3] = w11; 

    return;
}
