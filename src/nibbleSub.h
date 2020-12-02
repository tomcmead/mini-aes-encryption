#ifndef _NIBBLE_SUB_H
#define _NIBBLE_SUB_H

#include <iostream>
#include "../miniAES.h"
using namespace std;

void nibbleSub(nibbles_block_t &A);

int sBox(int in);

#endif