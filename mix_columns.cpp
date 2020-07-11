#include "AES.hpp"

Mat mix_columns(Mat block){
    #include "hex_multiply_with_2_lookup.hpp"
    #include "hex_multiply_with_3_lookup.hpp"
    Mat mixed_column(4,4,CV_8UC1);
    for (int j=0; j<COLS; j++){
        for (int i=0; i<ROWS; i++){
            mixed_column.at<uint8_t>(0,j) = hex_multiply_with_2_lookup[(block.at<uint8_t>(0,j) & 0xf0) >> 4][block.at<uint8_t>(0,j) & 0x0f]
            ^    hex_multiply_with_3_lookup[(block.at<uint8_t>(1,j) & 0xf0) >> 4][block.at<uint8_t>(1,j) & 0x0f]
            ^    block.at<uint8_t>(2,j)  
            ^    block.at<uint8_t>(3,j); 
            mixed_column.at<uint8_t>(1,j) = block.at<uint8_t>(0,j)
            ^    hex_multiply_with_2_lookup[(block.at<uint8_t>(1,j) & 0xf0) >> 4][block.at<uint8_t>(1,j) & 0x0f]
            ^    hex_multiply_with_3_lookup[(block.at<uint8_t>(2,j) & 0xf0) >> 4][block.at<uint8_t>(2,j) & 0x0f]
            ^    block.at<uint8_t>(3,j);  
            mixed_column.at<uint8_t>(2,j) = block.at<uint8_t>(0,j) 
            ^    block.at<uint8_t>(1,j)  
            ^    hex_multiply_with_2_lookup[(block.at<uint8_t>(2,j) & 0xf0) >> 4][block.at<uint8_t>(2,j) & 0x0f]
            ^    hex_multiply_with_3_lookup[(block.at<uint8_t>(3,j) & 0xf0) >> 4][block.at<uint8_t>(3,j) & 0x0f];
            mixed_column.at<uint8_t>(3,j) = hex_multiply_with_3_lookup[(block.at<uint8_t>(0,j) & 0xf0) >> 4][block.at<uint8_t>(0,j) & 0x0f]
            ^    block.at<uint8_t>(1,j)  
            ^    block.at<uint8_t>(2,j)  
            ^    hex_multiply_with_2_lookup[(block.at<uint8_t>(3,j) & 0xf0) >> 4][block.at<uint8_t>(3,j) & 0x0f];
        }
    }
    return mixed_column;
}
/*
    #include "mix_column_matrix.hpp"
    Mat mix_column_matrix_mat(4,4,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            mix_column_matrix_mat.at<uint8_t>(i,j) = mix_column_matrix[i][j];
        }
    }
    Mat temp(4,1,CV_8UC1);
    Mat temp2(4,1,CV_8UC1);
    Mat mixed_column(4,4,CV_16UC1);
    for (int j=0; j<COLS; j++){
        for (int i=0; i<ROWS; i++){
            temp.at<uint8_t>(i,0) = block.at<uint8_t>(i,j);
        }
        printf("rows of mixcol: %d cols of mixcol: %d\n",mix_column_matrix_mat.rows,mix_column_matrix_mat.cols); 
        printf("rows of temp: %d cols of temp: %d\n",temp.rows,temp.cols); 
        temp2 = mix_column_matrix_mat * temp;

        for (int i=0; i<ROWS; i++){
            mixed_column.at<uint16_t>(i,j) = temp2.at<uint16_t>(i,0);
        }
    }
    
    return mixed_column;
*/