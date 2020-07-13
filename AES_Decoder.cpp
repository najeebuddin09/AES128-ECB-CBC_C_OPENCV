#include "AES.hpp"

int main(int argc, char ** argv){
    uint8_t test_block[ROWS][COLS] = {
        {0x32, 0x88, 0x31, 0xe0},
        {0x43, 0x5a, 0x31, 0x37},
        {0xf6, 0x30, 0x98, 0x07},
        {0xa8, 0x8d, 0xa2, 0x34}
    };
    
    uint8_t test_key[ROWS][COLS] = {
        {0x2b, 0x28, 0xab, 0x09},
        {0x7e, 0xae, 0xf7, 0xcf},
        {0x15, 0xd2, 0x15, 0x4f},
        {0x16, 0xa6, 0x88, 0x3c}
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
    
    log("block of data");
    log_block(block); 

    Mat encrypted_block = encrypt_block(block,key);
    
    log("block of data after encryption");
    log_block(encrypted_block); 
    
    Mat decrypted_block = decrypt_block(encrypted_block,key);
    
    log("block of data after decryption");
    log_block(decrypted_block); 

    return 0;
}