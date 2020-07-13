#include "AES.hpp"

Mat decrypt_block(Mat block, Mat key){
    
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

    //evaluate all keys
    find_keys(copy_of_key);
    copy_of_key = *keys[10];
    
    copy_of_block = add_round_key(copy_of_block,copy_of_key);
    //log("after add round key");
    //log_block(copy_of_block); 
    copy_of_block = inverse_shift_rows(copy_of_block);
    //printf("after final shift rows\n");
    //log_block(copy_of_block); 
    copy_of_block = inverse_subbyte(copy_of_block);
    //printf("after final subbyte \n");
    //log_block(copy_of_block); 
    
    for (int i=9; i>0 ; i--){
        copy_of_key = *keys[i];
        //printf("after key schedule %d\n",i);
        //log_block(copy_of_key); 
        copy_of_block = add_round_key(copy_of_block,copy_of_key);
        //printf("after add round key %d\n",i);
        //log_block(copy_of_block); 
        copy_of_block = inverse_mix_columns(copy_of_block);
        //printf("after mix columns %d\n",i);
        //log_block(copy_of_block); 
        copy_of_block = inverse_shift_rows(copy_of_block);
        //printf("after shift rows %d\n",i);
        //log_block(copy_of_block); 
        copy_of_block = inverse_subbyte(copy_of_block);
        //printf("after subbyte %d\n",i);
        //log_block(copy_of_block); 
    }    

    copy_of_key = *keys[0];
    //printf("after final key schedule in decryption\n");
    //log_block(copy_of_key); 
    copy_of_block = add_round_key(copy_of_block,copy_of_key);

    //release memory allocated for keys global array
    for (int i=0; i<11; i++){
        delete keys[i];
    }

    return copy_of_block;
}