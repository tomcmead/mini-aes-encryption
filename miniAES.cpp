/*************************************************************************//**
* @file miniAES.h
* @brief Mini AES Controller
*****************************************************************************/

/*----------------------------------------------------------------------------
  include files
----------------------------------------------------------------------------*/
#include <iostream>
#include <math.h>
#include "miniAES.h"
#include "src/nibbleSub.h"
#include "src/shiftRow.h"
#include "src/mixColumn.h"
#include "src/keys.h"

using namespace std;

int main(){

    uint16_t plaintext=0xFA50;      // 16-bit plaintext block
    //nibbles_block_t p, a, b, c, d;

    int encrypt[NIBBLES_BLOCK_SIZE];

    // Key generation
    int keysR0[NIBBLES_BLOCK_SIZE];
    int keysR1[NIBBLES_BLOCK_SIZE];
    int keysR2[NIBBLES_BLOCK_SIZE];
    keyGeneration(keysR0, keysR1, keysR2);

    cout << "Round 0 Keys: ";
    displayArray(keysR0);
    cout << "Round 1 Keys: ";
    displayArray(keysR1);
    cout << "Round 2 Keys: ";
    displayArray(keysR2);

    // Transform 16 bit block into 4 nibbles
    bool binaryNum [16];
    dec2Binary(plaintext, binaryNum);
    
    bool p0Bits[4], p1Bits[4], p2Bits[4], p3Bits[4];
    for(int i=0; i<4; i++){
        p0Bits[i] = binaryNum[i];
        p1Bits[i] = binaryNum[i+4];
        p2Bits[i] = binaryNum[i+8];
        p3Bits[i] = binaryNum[i+12];
    }
    encrypt[0] = binary2Dec(p0Bits, 4);
    encrypt[1] = binary2Dec(p1Bits, 4);
    encrypt[2] = binary2Dec(p2Bits, 4);
    encrypt[3] = binary2Dec(p3Bits, 4);

    cout << "Plaintext: ";
    displayArray(encrypt);

    // NibbleSub
    // substitutes each nibble with output nibble from S-Box look-up table
    for(int i=0; i<NIBBLES_BLOCK_SIZE; i++)
        encrypt[i] = nibbleSub(encrypt[i]);

    cout << "\nNibble Substitute: ";
    displayArray(encrypt);

    // ShiftRow
    // Rotates each row of input block left by different amounts
    // a0 a1 a2 a3  ->  a0 a3 a2 a3
    shiftRow(encrypt);

    cout << "\nShift Row: ";
    displayArray(encrypt);

    // MixColumn
    // Takes each column of input block and multiples it with constant matrix
    mixColumn(encrypt);

    cout << "\nMix Column: ";
    displayArray(encrypt);

    
    // KeyAddition
    // Each nibble XORed with correspong ith round key


    // KeyScheduler
    // 16-bit secret key passed through key-schedule to generated keys for 
    // following round. 3 rounds in total for miniAES

    return 0;
}

void dec2Binary(int dec, bool *binaryNum){
    int i = 0;
    while(dec>0){
        binaryNum[i] = dec % 2;
        dec = dec / 2;
        i++;
    }
}

int binary2Dec(bool *binary, int bits){    
    int decimal = 0;
    for(int i=0; i<bits; i++){
        if(binary[i]==1)
            decimal += pow(2,i);
    }
    return decimal;
}

void displayArray(int *arr){
    for(int i=0; i<NIBBLES_BLOCK_SIZE; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}