#include "AES.hpp"

void encrypt_block(){
    //cout<<"inside the encrypt_block function"<<endl;
    uint8_t test_block[ROWS][COLS] = {
        {0x19, 0xa0, 0x9a, 0xe9},
        {0x3d, 0xf4, 0xc6, 0xf8},
        {0xe3, 0xe2, 0x8d, 0x48},
        {0xbe, 0x2b, 0x2a, 0x08}
    };

    Mat block(ROWS,COLS,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            block.at<uint8_t>(i,j) = test_block[i][j];
        }
    } 
    Mat substituted_block = subbyte(block);
    Mat shifted_block = shift_rows(substituted_block);
    Mat mixed_column_block = mix_columns(shifted_block);
    
    log("block of data");
    log_block(block); 
    
    log("block of data after substitution");
    log_block(substituted_block); 
    
    log("block of data after shifting");
    log_block(shifted_block);
    
    log("block of data after mix column");
    log_block(mixed_column_block); 
}