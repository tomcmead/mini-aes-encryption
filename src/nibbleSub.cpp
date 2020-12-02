/*************************************************************************//**
* @file nibbleSub.cpp
* @brief substitutes each input nibble with an output nibble
according to a 4 × 4 substitution table (S-box).
*****************************************************************************/
#include "nibbleSub.h"


void nibbleSub(nibbles_block_t &A){
    A.n0 = sBox(A.n0);
    A.n1 = sBox(A.n1);
    A.n2 = sBox(A.n2);
    A.n3 = sBox(A.n3);
    if((A.n0 || A.n1 || A.n2 || A.n3) == -1){
        cout << "ERROR: nibbleSub" << endl;
    }
}


int sBox(int in){
    switch(in){
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