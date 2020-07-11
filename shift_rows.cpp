#include "AES.hpp"

Mat shift_rows(Mat block){

    //Make a copy
    Mat shifted_block(ROWS,COLS,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            shifted_block.at<uint8_t>(i,j) = block.at<uint8_t>(i,j);
        }
    } 
    uint8_t temp;
    //perform shifting
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<i; j++){
            //printf("value of i: %d and j: %d\n",i,j);
            temp = block.at<uint8_t>(i,j);
            //log("temp value:");
            //log_Mat_value(temp);
            for (int k=0; k+1<COLS; k++){
                //log("temp value:");
                //log_Mat_value(temp);
                //log("block value:");
                //log_Mat_value(block.at<uint8_t>(i,k+1));
                //log("shifted_block value:");
                //log_Mat_value(shifted_block.at<uint8_t>(i,k));
                shifted_block.at<uint8_t>(i,k) = shifted_block.at<uint8_t>(i,k+1);
            }
            shifted_block.at<uint8_t>(i,COLS-1) = temp;       
        }
    }

    return shifted_block;
}