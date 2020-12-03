/*************************************************************************//**
* @file nibbleSub.cpp
* @brief Substitutes each input nibble with an output nibble
according to a 4 × 4 substitution table (S-box).
*****************************************************************************/
/*----------------------------------------------------------------------------
  include files
----------------------------------------------------------------------------*/
#include "nibbleSub.h"

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Nibble substitutes current value with one in S-Box lookup table
* @param int a number to be substituted
* @return int
*****************************************************************************/
int nibbleSub(int b){
    return sBox(b);
}

/*************************************************************************//**
* @brief S-Box lookup table
* @param int input number to be substituted
* @return int
*****************************************************************************/
int sBox(int input){
    switch(input){
        case 0:         // b'0000
            return 14;  // b'1110
        case 1:         // b'0001
            return 4;   // b'0100
        case 2:         // b'0010
            return 13;  // b'1101
        case 3:         // b'0011
            return 1;   // b'0001
        case 4:         // b'0100
            return 2;   // b'0010  
        case 5:         // b'0101
            return 15;  // b'1111
        case 6:         // b'0110
            return 11;  // b'1011
        case 7:         // b'0111
            return 8;   // b'1000
        case 8:         // b'1000
            return 3;   // b'0011
        case 9:         // b'1001
            return 10;  // b'1010
        case 10:        // b'1010
            return 6;   // b'0110
        case 11:        // b'1011
            return 12;  // b'1100
        case 12:        // b'1100
            return 5;   // b'0101
        case 13:        // b'1101
            return 9;   // b'1001
        case 14:        // b'1110
            return 0;   // b'0000
        case 15:        // b'1111
            return 7;   // b'0111

    }
    return -1;
}