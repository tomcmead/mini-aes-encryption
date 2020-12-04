/*************************************************************************//**
* @file mixColumn.cpp
* @brief MixColumn takes each column of the input block and multiplies it with 
a constant matrix to obtain a new output column
*****************************************************************************/
/*----------------------------------------------------------------------------
  include files
----------------------------------------------------------------------------*/
#include "mixColumn.h"

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Takes each column of the input block and multiplies it with constant 
matrix [[3 2] [2 3]]
* @param int *c pointer to start of nibble array to be mix columned
* @return None
*****************************************************************************/
void mixColumn(int *c){

    int c0 = galoisAdd(galoisMult(3, c[0]), galoisMult(2, c[1]));   
    int c1= galoisAdd(galoisMult(2, c[0]), galoisMult(3, c[1]));
    int c2 = galoisAdd(galoisMult(3, c[2]), galoisMult(2, c[3]));
    int c3 = galoisAdd(galoisMult(2, c[2]), galoisMult(3, c[3]));  

    c[0] = c0;
    c[1] = c1;
    c[2] = c2;
    c[3] = c3;  
}

/*************************************************************************//**
* @brief GF(2^4) addition (XOR) of inputs passed
* @param int a, int b inputs to be galois field added
* @return int result
*****************************************************************************/
int galoisAdd(int a, int b){
    return a ^ b;
}

/*************************************************************************//**
* @brief GF(2^4) multiplication of inputs passed
* @param int a, int b inputs to be galois field added
* @return int result
*****************************************************************************/
int galoisMult(int a, int b){

    int numOfCoef[] = {0, 0, 0, 0, 0, 0, 0};    // Number of coefficents for each one
    int result;
    bool product[7];
    bool binaryA[4] = {0, 0, 0, 0};
    bool binaryB[4] = {0, 0, 0, 0};

    dec2Binary(a, binaryA); 
    dec2Binary(b, binaryB);

    // Find number of coeffiecent for each coeffiecents
    // {1, x, x^2, x^3, x^4, x^5, x^6}
    for(int j=0; j<4; j++){
        for(int i=0; i<4; i++)
            if(binaryA[j] && binaryB[i])
                numOfCoef[i+j]++;      
    }

    // Find XOR of number of coef, found through mod 2
    // so integer result of 1 if odd number of coef or else 0 
    for(int i=0; i<7; i++)
        product[i] = numOfCoef[i]%2 == 1 ? 1 : 0;
    

    result = binary2Dec(product, 7);    // 7-bit binary number to decimal
    result = galoisMod(result);         // Galois modulo m = b10011

    return result;
}


/*************************************************************************//**
* @brief GF(2^4) modulo m(x), where m(x) = b10011
* @param int product to be galois field modulo with m(x)
* @return int result
*****************************************************************************/
int galoisMod(int product){

    bool pArray[] = {0, 0, 0, 0, 0, 0, 0};
    dec2Binary(product, pArray);    // convert input to binary array

    if(product == 0){
        return 0;       // Return 0 if input 0
    }

    // If MSB is 6th bit XOR array with m(x)<<2 as m(x) degree 4
    if(pArray[6]==1){       
        pArray[6] ^= 1;
        pArray[3] ^= 1;
        pArray[2] ^= 1;
    }
    // If MSB is 5th bit XOR array with m(x)<<1 as m(x) degree 4
    if(pArray[5]==1){       
        pArray[5] ^= 1;
        pArray[2] ^= 1;
        pArray[1] ^= 1;
    }
    // If MSB is 4th bit XOR array with m(x) as m(x) degree 4
    if(pArray[4]==1){       
        pArray[4] ^= 1;
        pArray[1] ^= 1;
        pArray[0] ^= 1;
    }
    // Otherwise pArray degree less than m(x) so it is remainer itself

    product = binary2Dec(pArray, 7);    // Convert 7-bit array to decimal
    return product;
}