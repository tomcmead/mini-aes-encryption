/*************************************************************************//**
* @file shiftRow.cpp
* @brief Rotates each row of the input block to the left by different nibble
 amounts. The first row is unchanged while the second row is rotated left by 
 one nibble.
*****************************************************************************/

/*----------------------------------------------------------------------------
  include files
----------------------------------------------------------------------------*/
#include "../miniAES.h"
#include "shiftRow.h"

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Shifts each row of input nibble block array, swaps elements 1 and 3
* @param int *b pointer to start of nibble array to be shifted
* @return None
*****************************************************************************/
void shiftRow(int *b){
    int temp = b[1];
    b[1] = b[3];
    b[3] = temp;
}