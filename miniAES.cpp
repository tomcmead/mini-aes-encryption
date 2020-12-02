/*************************************************************************//**
* @file miniAES.h
* @brief Mini AES Controller
*****************************************************************************/

/*----------------------------------------------------------------------------
  include files
----------------------------------------------------------------------------*/
#include <iostream>
#include "miniAES.h"
using namespace std;

void dec2Binary(uint16_t dec, bool *binaryNum);

int main(){

    
    uint16_t plaintext=0x9C63;      // 16-bit plaintext block

    // Transform 16 bit block into 4 nibbles
    p_nibbles P;
    bool binaryNum[16];
    dec2Binary(plaintext, binaryNum);
    //bool binaryNum[] = {0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1};
    for(int i=0; i<4; i++){
        P.p0[i] = binaryNum[i];
        P.p1[i] = binaryNum[i+4];
        P.p2[i] = binaryNum[i+8];
        P.p3[i] = binaryNum[i+12];
    }

    cout << "Plaintext Bits:" << endl;
    for(int i=0; i<4; i++){
        cout << P.p0[i] << " ";
    }
    cout << " ";
    for(int i=0; i<4; i++){
        cout << P.p1[i] << " ";
    }
    cout << " ";
    for(int i=0; i<4; i++){
        cout << P.p2[i] << " ";
    }
    cout << " ";
    for(int i=0; i<4; i++){
        cout << P.p3[i] << " ";
    }
    cout << " "; 



    // NibbleSub
    // substitutes each nibble wiwth output nibble from S-Box look-up table



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

void dec2Binary(uint16_t dec, bool *binaryNum){

    int i = 0;
    while(dec>0){
        binaryNum[i] = dec % 2;
        dec = dec / 2;
        i++;
    }
    return;
}