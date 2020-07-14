#include "AES.hpp"

Mat slice_of_data(Mat data, int x, int y){
    Mat block(4,4,CV_8UC1);
    block = Mat::zeros(4,4,CV_8UC1);
    for (int i=y; i<(y+ROWS); i++){
        for (int j=x; j<(x+COLS); j++){
            if (i<data.rows && j<data.cols){
                block.at<uint8_t>(i-y,j-x) = data.at<uint8_t>(i,j);
            }
        }
    }
    return block;
}

void put_back_together(Mat * destination, Mat source, int x, int y){
    for (int i=y; i<(y+ROWS); i++){
        for (int j=x; j<(x+COLS); j++){
            destination->at<uint8_t>(i,j) = source.at<uint8_t>(i-y,j-x);
        }
    }
}

Mat manipulate_data_any_size_ecb(Mat block, Mat key, Mat callback_function(Mat,Mat)){
    Mat crop, encrypted_block = Mat::zeros(block.rows+(block.rows%ROWS),block.cols+(block.cols%COLS),CV_8UC1);
    int x_axis = 0, y_axis = 0;
    for (int i=0; y_axis < block.rows; i++){
        for (int j=0; x_axis < block.cols; j++){
            crop = slice_of_data(block, x_axis, y_axis);
            crop = callback_function(crop,key);
            if (callback_function == encrypt_block){
                log("put together function for encryption is called");
                put_back_together(&encrypted_block, crop, x_axis, y_axis);
            } else if (callback_function == decrypt_block){
                log("put together function for decryption is called");
                put_back_together(&encrypted_block, crop, x_axis, y_axis);
            }
            //printf("x_axis %d y_axis %d\n",x_axis,y_axis);
            //log_block(crop);
            x_axis += COLS;
        }
        x_axis = 0;
        y_axis += ROWS;
    }
    return encrypted_block;
}