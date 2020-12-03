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


int main(){

    int encrypt[NIBBLES_BLOCK_SIZE];
    uint16_t plaintext=0x9C63;      // 16-bit plaintext block

    encrytionAES(plaintext, encrypt);
 
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
        cout << hex << arr[i] << " ";
    }
    cout << endl;
}

void encrytionAES(int plaintext, int *encrypt){
    
    int P[NIBBLES_BLOCK_SIZE];

    // Key generation
    int keysR0[NIBBLES_BLOCK_SIZE];
    int keysR1[NIBBLES_BLOCK_SIZE];
    int keysR2[NIBBLES_BLOCK_SIZE];
    keyGeneration(keysR0, keysR1, keysR2);

    cout << "Round 1 Keys: ";
    displayArray(keysR0);
    cout << "Round 2 Keys: ";
    displayArray(keysR1);
    cout << "Round 3 Keys: ";
    displayArray(keysR2);

    // Transform 16 bit plaintext block into 4 nibbles
    bool binaryNum [16];
    dec2Binary(plaintext, binaryNum);
    
    bool p0Bits[4], p1Bits[4], p2Bits[4], p3Bits[4];
    for(int i=0; i<4; i++){
        p0Bits[i] = binaryNum[i+12];
        p1Bits[i] = binaryNum[i+8];
        p2Bits[i] = binaryNum[i+4];
        p3Bits[i] = binaryNum[i];
    }

    P[0] = binary2Dec(p0Bits, 4);
    P[1] = binary2Dec(p1Bits, 4);
    P[2] = binary2Dec(p2Bits, 4);
    P[3] = binary2Dec(p3Bits, 4);

    cout << "\nPlaintext: ";
    displayArray(P);
    cout << endl;

    for(int round=0; round < NUM_OF_ROUNDS-1; round++){

        switch(round){
            case 0:
                for(int i=0; i<NIBBLES_BLOCK_SIZE; i++)
                    encrypt[i] = galoisAdd(P[i], keysR0[i]);
                break;
            case 1:
                for(int i=0; i<NIBBLES_BLOCK_SIZE; i++)
                    encrypt[i] = galoisAdd(encrypt[i], keysR1[i]);
                break;
        }

        cout << "Round Key" << round << " Encrypted: ";
        displayArray(encrypt);

        if(round == NUM_OF_ROUNDS-1)
            return;

        cout << "\nROUND " << round+1 << ":" << endl;

        // NibbleSub
        // substitutes each nibble with output nibble from S-Box look-up table
        for(int i=0; i<NIBBLES_BLOCK_SIZE; i++)
            encrypt[i] = nibbleSub(encrypt[i]);

        cout << "Nibble Substitute: ";
        displayArray(encrypt);

        // ShiftRow
        // Rotates each row of input block left by different amounts
        // a0 a1 a2 a3  ->  a0 a3 a2 a3
        shiftRow(encrypt);

        cout << "Shift Row: ";
        displayArray(encrypt);

        // MixColumn
        // Takes each column of input block and multiples it with constant matrix
        if(round != NUM_OF_ROUNDS-2){
            mixColumn(encrypt);

            cout << "Mix Column: ";
            displayArray(encrypt); 
        }
        else{
            for(int i=0; i<NIBBLES_BLOCK_SIZE; i++)
                encrypt[i] = galoisAdd(encrypt[i], keysR2[i]);

            cout << "Round Key" << NUM_OF_ROUNDS-1 << " Encrypted: ";
            displayArray(encrypt);
            cout << "\nAES Encrypted: ";
            displayArray(encrypt); 
        }
    }
}