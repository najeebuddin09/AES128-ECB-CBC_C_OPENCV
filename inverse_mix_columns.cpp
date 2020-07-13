#include "AES.hpp"

Mat inverse_mix_columns(Mat block){
    #include "hex_multiply_with_9_lookup.hpp"
    #include "hex_multiply_with_11_lookup.hpp"
    #include "hex_multiply_with_13_lookup.hpp"
    #include "hex_multiply_with_14_lookup.hpp"
    Mat mixed_column(4,4,CV_8UC1);
    for (int j=0; j<COLS; j++){
        for (int i=0; i<ROWS; i++){
            mixed_column.at<uint8_t>(0,j) = hex_multiply_with_14_lookup[(block.at<uint8_t>(0,j) & 0xf0) >> 4][block.at<uint8_t>(0,j) & 0x0f]
            ^    hex_multiply_with_9_lookup[(block.at<uint8_t>(3,j) & 0xf0) >> 4][block.at<uint8_t>(3,j) & 0x0f]
            ^    hex_multiply_with_13_lookup[(block.at<uint8_t>(2,j) & 0xf0) >> 4][block.at<uint8_t>(2,j) & 0x0f]
            ^    hex_multiply_with_11_lookup[(block.at<uint8_t>(1,j) & 0xf0) >> 4][block.at<uint8_t>(1,j) & 0x0f];
            mixed_column.at<uint8_t>(1,j) = hex_multiply_with_14_lookup[(block.at<uint8_t>(1,j) & 0xf0) >> 4][block.at<uint8_t>(1,j) & 0x0f]
            ^    hex_multiply_with_9_lookup[(block.at<uint8_t>(0,j) & 0xf0) >> 4][block.at<uint8_t>(0,j) & 0x0f]
            ^    hex_multiply_with_13_lookup[(block.at<uint8_t>(3,j) & 0xf0) >> 4][block.at<uint8_t>(3,j) & 0x0f]
            ^    hex_multiply_with_11_lookup[(block.at<uint8_t>(2,j) & 0xf0) >> 4][block.at<uint8_t>(2,j) & 0x0f];
            mixed_column.at<uint8_t>(2,j) = hex_multiply_with_14_lookup[(block.at<uint8_t>(2,j) & 0xf0) >> 4][block.at<uint8_t>(2,j) & 0x0f]
            ^    hex_multiply_with_9_lookup[(block.at<uint8_t>(1,j) & 0xf0) >> 4][block.at<uint8_t>(1,j) & 0x0f]
            ^    hex_multiply_with_13_lookup[(block.at<uint8_t>(0,j) & 0xf0) >> 4][block.at<uint8_t>(0,j) & 0x0f]
            ^    hex_multiply_with_11_lookup[(block.at<uint8_t>(3,j) & 0xf0) >> 4][block.at<uint8_t>(3,j) & 0x0f];
            mixed_column.at<uint8_t>(3,j) = hex_multiply_with_14_lookup[(block.at<uint8_t>(3,j) & 0xf0) >> 4][block.at<uint8_t>(3,j) & 0x0f]
            ^    hex_multiply_with_9_lookup[(block.at<uint8_t>(2,j) & 0xf0) >> 4][block.at<uint8_t>(2,j) & 0x0f]
            ^    hex_multiply_with_13_lookup[(block.at<uint8_t>(1,j) & 0xf0) >> 4][block.at<uint8_t>(1,j) & 0x0f]
            ^    hex_multiply_with_11_lookup[(block.at<uint8_t>(0,j) & 0xf0) >> 4][block.at<uint8_t>(0,j) & 0x0f];
        }
    }
    return mixed_column;
}