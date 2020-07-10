#include <iostream>
#include <stdint.h>

using namespace std;

void subbyte(){
    #include "sbox.hpp"
    cout<<sbox[0x0f][0x0f]<<endl;
}