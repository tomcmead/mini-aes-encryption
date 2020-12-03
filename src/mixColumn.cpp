/*************************************************************************//**
* @file mixColumn.cpp
* @brief MixColumn takes each column of the input block and multiplies it with 
a constant matrix to obtain a new output column.
*****************************************************************************/
#include "mixColumn.h"

void mixColumn(nibbles_block_t &C){
    nibbles_block_t D;
    D.n0 = galoisAdd(galoisMult(3, C.n0), galoisMult(2, C.n1));             (3*C.n0) ^ (2*C.n1);     // (3*C.n0) + (2*C.n1);
    D.n1 = galoisAdd(galoisMult(2, C.n0), galoisMult(3, C.n1));
    D.n2 = galoisAdd(galoisMult(3, C.n2), galoisMult(2, C.n3));
    D.n3 = galoisAdd(galoisMult(2, C.n2), galoisMult(3, C.n3));  
    C = D;  
}

int galoisAdd(int a, int b){
    return a ^ b;
}

int galoisMult(int a, int b){

    int x[] = {0, 0, 0, 0, 0, 0, 0};
    int result;
    bool product[7];
    bool binaryA[4] = {0, 0, 0, 0};
    bool binaryB[4] = {0, 0, 0, 0};
    dec2Binary(a, binaryA);
    dec2Binary(b, binaryB);

    for(int j=0; j<4; j++){
        for(int i=0; i<4; i++)
            if(binaryA[j] && binaryB[i])
                x[i+j]++;      
    }

    for(int i=0; i<7; i++)
        product[i] = x[i]%2 == 1 ? 1 : 0;
    

    result = binary2Dec(product, 7);
    result = galoisMod(result);

    return result;
}

int galoisMod(int product){

    bool pArray[] = {0, 0, 0, 0, 0, 0, 0};
    dec2Binary(product, pArray);

    if(product == 0){
        return 0;
    }
  
    if(pArray[6]==1){       
        pArray[6] ^= 1;
        pArray[3] ^= 1;
        pArray[2] ^= 1;
    }
    if(pArray[5]==1){       
        pArray[5] ^= 1;
        pArray[2] ^= 1;
        pArray[1] ^= 1;
    }
        if(pArray[4]==1){       
        pArray[4] ^= 1;
        pArray[1] ^= 1;
        pArray[0] ^= 1;
    }

    product = binary2Dec(pArray, 7);
    return product;
}