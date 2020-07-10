#include <iostream>
#include <stdint.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat subbyte(Mat block){
    #include "sbox.hpp"
    Mat block_after_substitution;
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            block_after_substitution.at<uint8_t>(i,j) = sbox[(block.at<uint8_t>(i,j) & 0xf0) >> 8][block.at<uint8_t>(i,j) & 0x0f]; 
        }
    }
    return block_after_substitution;
}