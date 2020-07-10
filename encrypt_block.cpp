#include "AES.hpp"
#include <opencv2/opencv.hpp>
#include <stdint.h>

using namespace std;
using namespace cv;

uint8_t test_block[4][4] = {
    {0x19, 0xa0, 0x9a, 0xe9},
    {0x3d, 0xf4, 0xc6, 0xf8},
    {0xe3, 0xe2, 0x8d, 0x48},
    {0xbe, 0x2b, 0x2a, 0x08}
};

void encrypt_block(){
    Mat block;
    
}