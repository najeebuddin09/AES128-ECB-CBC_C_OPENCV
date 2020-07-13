#include "AES.hpp"

Mat * keys[11];

void find_keys(Mat key){
    Mat copy_of_key = key;
    keys[0] = new Mat(4,4,CV_8UC1);
    *keys[0] = copy_of_key;
    for (int i=1; i<11; i++){
        keys[i] = new Mat(4,4,CV_8UC1);
        copy_of_key = key_schedule(copy_of_key,i-1);
        *keys[i] = copy_of_key;
        //printf("printing key %d\n",i);
        //log_block(*keys[i]);
    }
}

Mat key_schedule(Mat key, unsigned int rcon_index){
    #include "sbox.hpp"
    #include "rcon.hpp"
    Mat new_key(4,4,CV_8UC1);

    for (int i=0; i<COLS; i++){
        for (int j=0; j<ROWS; j++){
            if (i == 0) //first column of the new_key
            {
                new_key.at<uint8_t>(j,i) = key.at<uint8_t>(j,i)
                ^ sbox[(key.at<uint8_t>((j+1)%(ROWS),COLS-1) & 0xf0) >> 4][key.at<uint8_t>((j+1)%(ROWS),COLS-1) & 0x0f]
                ^ rcon[j][rcon_index];
                //log("key value for sbox");
                //log_Mat_value(key.at<uint8_t>(j,i));
                //log("new_key sbox value");
                //log_Mat_value(sbox[(key.at<uint8_t>((j+1)%(ROWS),COLS-1) & 0xf0) >> 4][key.at<uint8_t>((j+1)%(ROWS),COLS-1) & 0x0f]);
                //log("new_key rcon value");
                //log_Mat_value(rcon[j][RCON_INDEX]);
                //log("new_key first value");
                //log_Mat_value(new_key.at<uint8_t>(j,i));
                //printf("i: %d & j: %d\n",i,j);
            }
            else
            {
                new_key.at<uint8_t>(j,i) = key.at<uint8_t>(j,i) ^ new_key.at<uint8_t>(j,i-1);
            }
        }
    }
    
    return new_key;
}