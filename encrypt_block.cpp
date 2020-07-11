#include "AES.hpp"

void encrypt_block(){
    //cout<<"inside the encrypt_block function"<<endl;
    uint8_t test_block[ROWS][COLS] = {
        {0x19, 0xa0, 0x9a, 0xe9},
        {0x3d, 0xf4, 0xc6, 0xf8},
        {0xe3, 0xe2, 0x8d, 0x48},
        {0xbe, 0x2b, 0x2a, 0x08}
    };
    
    uint8_t test_key[ROWS][COLS] = {
        {0xa0, 0x88, 0x23, 0x2a},
        {0xfa, 0x54, 0xa3, 0x6c},
        {0xfe, 0x2c, 0x39, 0x76},
        {0x17, 0xb1, 0x39, 0x05}
    };

    Mat block(ROWS,COLS,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            block.at<uint8_t>(i,j) = test_block[i][j];
        }
    } 
    Mat key(ROWS,COLS,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            key.at<uint8_t>(i,j) = test_key[i][j];
        }
    } 
    Mat substituted_block = subbyte(block);
    Mat shifted_block = shift_rows(substituted_block);
    Mat mixed_column_block = mix_columns(shifted_block);
    Mat after_adding_round_key = add_round_key(mixed_column_block, key);
    
    log("block of data");
    log_block(block); 
    
    log("block of data after substitution");
    log_block(substituted_block); 
    
    log("block of data after shifting");
    log_block(shifted_block);
    
    log("block of data after mix column");
    log_block(mixed_column_block); 
    
    log("block of data after adding round key");
    log_block(after_adding_round_key); 

}