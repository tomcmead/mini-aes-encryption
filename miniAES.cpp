#include <iostream>
using namespace std;

int main(){

    // Transform 16 bit block into 4 nibbles



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