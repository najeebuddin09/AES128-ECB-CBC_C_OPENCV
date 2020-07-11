#include "AES.hpp"

Mat subbyte(Mat block){
    #include "sbox.hpp"
    Mat block_after_substitution(4,4,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            //cout<<hex<<(int)(block.at<uint8_t>(i,j))<<endl;
            //cout<<hex<<(int)((block.at<uint8_t>(i,j) & 0xf0) >> 4)<<endl;
            //cout<<hex<<(int)(block.at<uint8_t>(i,j) & 0x0f)<<endl;
            block_after_substitution.at<uint8_t>(i,j) = sbox[(block.at<uint8_t>(i,j) & 0xf0) >> 4][block.at<uint8_t>(i,j) & 0x0f]; 
        }
    }
    return block_after_substitution;
}