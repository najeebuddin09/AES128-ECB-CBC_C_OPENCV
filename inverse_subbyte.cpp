#include "AES.hpp"

Mat inverse_subbyte(Mat block){
    #include "inverse_sbox.hpp"
    Mat block_after_substitution(4,4,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            block_after_substitution.at<uint8_t>(i,j) = inverse_sbox[(block.at<uint8_t>(i,j) & 0xf0) >> 4][block.at<uint8_t>(i,j) & 0x0f]; 
        }
    }
    return block_after_substitution;
}