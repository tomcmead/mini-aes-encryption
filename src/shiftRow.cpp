/*************************************************************************//**
* @file shiftRow.cpp
* @brief rotates each row of the input block to the left by different nibble
 amounts. The first row is unchanged while the second row is rotated left by 
 one nibble.
*****************************************************************************/
#include "shiftRow.h"

void shiftRow(nibbles_block_t &B){

    int temp = B.n1;
    B.n1 = B.n3;
    B.n3 = temp;
}