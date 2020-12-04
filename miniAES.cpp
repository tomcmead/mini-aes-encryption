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

    bool isEncrypting;              // 1 for encryption, 0 for decryption
    uint16_t plaintext=0x9C63;      // 16-bit plaintext block

    //----------------------------ENCRYPTION----------------------------
    // AES Encryption of plaintext and print ciphertext result
    isEncrypting = 1;
    int cipher = miniAES(plaintext, isEncrypting);      
    cout << "Ciphertext: 0x" << hex << cipher << endl;

    //----------------------------DECRYPTION----------------------------
    // AES Decryption of ciphertext and print plaintext result
    isEncrypting = 0;
    int plain = miniAES(cipher, isEncrypting);      
    cout << "Plaintext: 0x" << hex << plain << endl;
 
}

/*************************************************************************//**
* @brief Decimal to binary array conversion
* @param int dec decimal, bool *binaryNum pointer to start of binary array
* @return None
*****************************************************************************/
void dec2Binary(int dec, bool *binary){
    int i = 0;
    while(dec>0){
        binary[i] = dec % 2;
        dec = dec / 2;
        i++;
    }
}

/*************************************************************************//**
* @brief Binary array to decimal conversion
* @param bool *binary pointer to start of binary array, int bits number bits in
binary array
* @return int decimal result
*****************************************************************************/
int binary2Dec(bool *binary, int bits){    
    int decimal = 0;
    for(int i=0; i<bits; i++){
        if(binary[i]==1)
            decimal += pow(2,i);
    }
    return decimal;
}

/*************************************************************************//**
* @brief Print binary array data
* @param int *arr pointer to start of binary array
* @return None
*****************************************************************************/
void displayArray(int *arr){
    cout << "0x";
    for(int i=0; i<NIBBLES_BLOCK_SIZE; i++){
        cout << hex << arr[i];
    }
    cout << endl;
}

/*************************************************************************//**
* @brief AES Encryption/Decryption
* @param int text input either plaintext or cipher text, for encrypting or
decrypting respectively. bool isEncrypting is 1 for encryption, 0 for decryption
* @return int ciphertext result if encrypting or plaintex if decrypting
*****************************************************************************/
int miniAES(int text, bool isEncrypting){
    
    int TP[NIBBLES_BLOCK_SIZE];          // Text nibble array, each int element is 4-bit nibble
    int encrypt[NIBBLES_BLOCK_SIZE];    // Encrypted nibble array, each int element is 4-bit nibble

    //-----------------------------KEY GENERATION-----------------------------
    int keysR0[NIBBLES_BLOCK_SIZE];     // Each int element is 4-bit nibble key k0, k1, k2, k3
    int keysR1[NIBBLES_BLOCK_SIZE];
    int keysR2[NIBBLES_BLOCK_SIZE];

    keyGeneration(keysR0, keysR1, keysR2);

    cout << "Round 1 Keys: ";
    displayArray(keysR0);
    cout << "Round 2 Keys: ";
    displayArray(keysR1);
    cout << "Round 3 Keys: ";
    displayArray(keysR2);

    // Transform 16 bit text block into 4 4-bit nibbles
    bool binaryNum [16];
    dec2Binary(text, binaryNum);    // Convert pass int 'text' to bool 16-bit (element) binary array
    
    // Store each nibble of 16-bit 'text' bool binary number in a int 4-bit nibble array 
    bool t0Nibble[4], t1Nibble[4], t2Nibble[4], t3Nibble[4];   
    for(int i=0; i<4; i++){
        t0Nibble[i] = binaryNum[i+12];
        t1Nibble[i] = binaryNum[i+8];
        t2Nibble[i] = binaryNum[i+4];
        t3Nibble[i] = binaryNum[i];
    }

    // Convert each nibble back to decimal and store in array T (text nibble array)
    T[0] = binary2Dec(t0Nibble, 4);
    T[1] = binary2Dec(t1Nibble, 4);
    T[2] = binary2Dec(t2Nibble, 4);
    T[3] = binary2Dec(t3Nibble, 4);

    // Display plaintext/ciphertext if encrypting/decrypting respectively
    if(isEncrypting)
        cout << "\nPlaintext: ";
    else
        cout << "\nCiphertext: ";    
    displayArray(T);
    cout << endl;

    // Loop through all round of AES algorithm 0-2
    for(int round=0; round < NUM_OF_ROUNDS-1; round++){

        //------------------------ROUND KEY ENCRYPTION-----------------------
        // First round GF addition of each nibble of text and corresponding
        // round key, text nibble0 + k0, text nibble1 + k1...
        if(round == 0)
            for(int i=0; i<NIBBLES_BLOCK_SIZE; i++)
                encrypt[i] = galoisAdd(T[i], keysR0[i]); // galiosAdd declared in mixColumn.h

        if(round == 1)
            for(int i=0; i<NIBBLES_BLOCK_SIZE; i++)
                encrypt[i] = galoisAdd(encrypt[i], keysR1[i]);

        // Display round key encryption/decryption result
        if(isEncrypting)
            cout << "Round Key" << round << " Encrypted: ";
        else
            cout << "Round Key" << round << " Decrypted: ";        
        displayArray(encrypt);

        cout << "\nROUND " << round+1 << ":" << endl;


        //---------------------------NIBBLE SUBSTITUTION--------------------------
        for(int i=0; i<NIBBLES_BLOCK_SIZE; i++) // Nibble substitue all 4 nibbles individually
            encrypt[i] = nibbleSub(encrypt[i], isEncrypting); 

        cout << "Nibble Substitute: ";
        displayArray(encrypt);


        //-------------------------------SHIFT ROW--------------------------------
        shiftRow(encrypt);      

        cout << "Shift Row: ";
        displayArray(encrypt);

        
        if(round != NUM_OF_ROUNDS-2){  // Do not perform mix column on final round
            //-----------------------------MIX COLUMN-----------------------------
            mixColumn(encrypt);

            cout << "Mix Column: ";
            displayArray(encrypt); 
        }
        else{   // Final round - galois addition of encryted text & final round key 
            for(int i=0; i<NIBBLES_BLOCK_SIZE; i++)
                encrypt[i] = galoisAdd(encrypt[i], keysR2[i]);
                

            cout << "Round Key" << NUM_OF_ROUNDS-1 << " Encrypted: ";
            displayArray(encrypt);
            cout << "\nCiphertext: ";
            displayArray(encrypt); 
        }
    }
    // Return ciphertext as an integer
    return (encrypt[0]<<12) + (encrypt[1]<<8) + (encrypt[2]<<4) + encrypt[3];
}