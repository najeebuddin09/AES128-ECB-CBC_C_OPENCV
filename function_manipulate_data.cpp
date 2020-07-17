#include "AES.hpp"

Mat manipulate_data_any_size_ecb(Mat block, Mat key, Mat callback_function(Mat,Mat)){
    //printf("rows: %d cols: %d\n",block.rows-(block.rows%ROWS)+(block.rows%ROWS ? ROWS : 0),block.cols-(block.cols%COLS)+(block.cols%COLS ? COLS : 0));
    Mat crop, encrypted_block = Mat::zeros(block.rows-(block.rows%ROWS)+(block.rows%ROWS ? ROWS : 0),block.cols-(block.cols%COLS)+(block.cols%COLS ? COLS : 0),CV_8UC1);
    int x_axis = 0, y_axis = 0;
    for (int i=0; y_axis < block.rows; i++){
        for (int j=0; x_axis < block.cols; j++){
            crop = slice_of_data(block, x_axis, y_axis);
            //printf("x_axis %d y_axis %d block\n",x_axis,y_axis);
            //log_block(crop);
            crop = callback_function(crop,key);
            put_back_together(&encrypted_block, crop, x_axis, y_axis);
            //printf("x_axis %d y_axis %d encrypted block\n",x_axis,y_axis);
            //log_block(crop);
            x_axis += COLS;
        }
        x_axis = 0;
        y_axis += ROWS;
    }
    return encrypted_block;
}


Mat manipulate_data_any_size_cbc(Mat block, Mat key, Mat iv, Mat callback_function(Mat,Mat)){
    Mat crop, decrypted_crop,encrypted_block = Mat::zeros(block.rows-(block.rows%ROWS)+(block.rows%ROWS ? ROWS : 0),block.cols-(block.cols%COLS)+(block.cols%COLS ? COLS : 0),CV_8UC1);
    int x_axis = 0, y_axis = 0;
    for (int i=0; y_axis < block.rows; i++){
        for (int j=0; x_axis < block.cols; j++){
            crop = slice_of_data(block, x_axis, y_axis);
            //printf("x_axis %d y_axis %d block\n",x_axis,y_axis);
            //log_block(crop);
            if (callback_function == encrypt_block){
                crop = add_round_key(crop, iv);
                crop = callback_function(crop,key);
                iv = crop;
            } else if (callback_function == decrypt_block){
                decrypted_crop = callback_function(crop,key);
                decrypted_crop = add_round_key(decrypted_crop, iv);
                iv = crop;
                crop = decrypted_crop;
            }
            put_back_together(&encrypted_block, crop, x_axis, y_axis);
            //printf("x_axis %d y_axis %d encrypted block\n",x_axis,y_axis);
            //log_block(crop);
            x_axis += COLS;
        }
        x_axis = 0;
        y_axis += ROWS;
    }
    return encrypted_block;
}