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
            //printf("i: %d & j: %d destination: %x source: %x\n",i,j,destination->at<uint8_t>(i,j),source.at<uint8_t>(i-y,j-x));
            destination->at<uint8_t>(i,j) = source.at<uint8_t>(i-y,j-x);
        }
    }
}