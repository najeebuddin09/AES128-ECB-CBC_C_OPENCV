#include "AES.hpp"

Mat add_round_key(Mat block, Mat key){
    Mat after_adding_round_key(4,4,CV_8UC1);

    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            after_adding_round_key.at<uint8_t>(i,j) = block.at<uint8_t>(i,j) ^ key.at<uint8_t>(i,j);
        }
    }

    return after_adding_round_key;
}