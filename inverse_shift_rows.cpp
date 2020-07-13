#include "AES.hpp"

Mat inverse_shift_rows(Mat block){
    //Make a copy
    Mat shifted_block(ROWS,COLS,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            shifted_block.at<uint8_t>(i,j) = block.at<uint8_t>(i,j);
        }
    } 

    //perform shifting
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<i; j++){
            for (int k=0; k<COLS; k++){
                shifted_block.at<uint8_t>(i,(k+(j+1))%ROWS) = block.at<uint8_t>(i,k);
            }
        }
    }

    return shifted_block;
}