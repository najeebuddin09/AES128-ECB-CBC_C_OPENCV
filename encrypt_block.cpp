#include "AES.hpp"

Mat encrypt_block(Mat block, Mat key){
    //create a copy of the block
    Mat copy_of_block(ROWS,COLS,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            copy_of_block.at<uint8_t>(i,j) = block.at<uint8_t>(i,j);
        }
    }
    //creat a copy of key
    Mat copy_of_key(ROWS,COLS,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            copy_of_key.at<uint8_t>(i,j) = key.at<uint8_t>(i,j);
        }
    }

    copy_of_block = add_round_key(copy_of_block,copy_of_key);
    
    //log("after add round key");
    //log_block(copy_of_block); 
    
    for (int i=0; i<9 ; i++){
        copy_of_key = key_schedule(copy_of_key);
        //printf("after key schedule %d\n",i);
        //log_block(copy_of_block); 
        copy_of_block = subbyte(copy_of_block);
        //printf("after subbyte %d\n",i);
        //log_block(copy_of_block); 
        copy_of_block = shift_rows(copy_of_block);
        //printf("after shift rows %d\n",i);
        //log_block(copy_of_block); 
        copy_of_block = mix_columns(copy_of_block);
        //printf("after mix columns %d\n",i);
        //log_block(copy_of_block); 
        copy_of_block = add_round_key(copy_of_block,copy_of_key);
        //printf("after mix add round key %d\n",i);
        //log_block(copy_of_block); 
    }    

    copy_of_key = key_schedule(copy_of_key);
    //printf("after final key schedule\n");
    //log_block(copy_of_block); 
    copy_of_block = subbyte(copy_of_block);
    //printf("after final subbyte \n");
    //log_block(copy_of_block); 
    copy_of_block = shift_rows(copy_of_block);
    //printf("after final shift rows\n");
    //log_block(copy_of_block); 
    copy_of_block = add_round_key(copy_of_block,copy_of_key);

    return copy_of_block;
}
//test for key scheduling
/*
    uint8_t test_key[ROWS][COLS] = {
        {0x2b, 0x28, 0xab, 0x09},
        {0x7e, 0xae, 0xf7, 0xcf},
        {0x15, 0xd2, 0x15, 0x4f},
        {0x16, 0xa6, 0x88, 0x3c}
    };
    Mat key(ROWS,COLS,CV_8UC1);
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            key.at<uint8_t>(i,j) = test_key[i][j];
        }
    }
    
    Mat key_after_scheduling = key_schedule(key);
    
    log("initial key");
    log_block(key); 
    
    log("key after first scheduling");
    log_block(key_after_scheduling); 
    
    key_after_scheduling = key_schedule(key_after_scheduling);
    
    log("key after second scheduling");
    log_block(key_after_scheduling); 
*/
//test for all the aes steps (functions)
/*
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

*/