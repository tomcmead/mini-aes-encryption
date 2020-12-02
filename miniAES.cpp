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

using namespace std;

int main(){

    uint16_t plaintext=0x9C63;      // 16-bit plaintext block
    nibbles_block_t p, a;
    

    // Transform 16 bit block into 4 nibbles
    bool binaryNum [16];
    dec2Binary(plaintext, binaryNum);
    
    bool n0Bits[4], n1Bits[4], n2Bits[4], n3Bits[4];
    for(int i=0; i<4; i++){
        n0Bits[i] = binaryNum[i];
        n1Bits[i] = binaryNum[i+4];
        n2Bits[i] = binaryNum[i+8];
        n3Bits[i] = binaryNum[i+12];
    }
    p.n0 = binary2Dec(n0Bits);
    p.n1 = binary2Dec(n1Bits);
    p.n2 = binary2Dec(n2Bits);
    p.n3 = binary2Dec(n3Bits);

    cout << "Plaintext: ";
    displayNibbleBlock(p);

    a = p;

    // NibbleSub
    // substitutes each nibble wiwth output nibble from S-Box look-up table
    nibbleSub(a);

    cout << "\nNibble Substitute: ";
    displayNibbleBlock(a);

    // ShiftRow
    // Rotates each row of input block left by different amounts
    // a0 a1 a2 a3  ->  a0 a3 a2 a3



    // MixColumn
    // Takes each column of input block and multiples it with constant matrix


    
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

int binary2Dec(bool *binary){    
    int decimal = 0;
    for(int i=0; i<4; i++){
        if(binary[i]==1)
            decimal += pow(2,i);
    }
    return decimal;
}


void displayNibbleBlock(nibbles_block_t nib){
    cout << hex << nib.n0 << " ";
    cout << hex << nib.n1 << " ";
    cout << hex << nib.n2 << " ";
    cout << hex << nib.n3 << " ";
    cout << "\n"; 
}