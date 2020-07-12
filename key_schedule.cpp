#include "AES.hpp"

//global
uint8_t RCON_INDEX = 0;

Mat key_schedule(Mat key){
    #include "sbox.hpp"
    #include "rcon.hpp"
    Mat new_key(4,4,CV_8UC1);

    for (int i=0; i<COLS; i++){
        for (int j=0; j<ROWS; j++){
            if (i == 0) //first column of the new_key
            {
                new_key.at<uint8_t>(j,i) = key.at<uint8_t>(j,i)
                ^ sbox[(key.at<uint8_t>((j+1)%(ROWS),COLS-1) & 0xf0) >> 4][key.at<uint8_t>((j+1)%(ROWS),COLS-1) & 0x0f]
                ^ rcon[j][RCON_INDEX];
                //log("key value for sbox");
                //log_Mat_value(key.at<uint8_t>((j+1)%(ROWS-1),COLS-1) & 0x0f);
                //log("new_key sbox value");
                //log_Mat_value(sbox[(key.at<uint8_t>((j+1)%(ROWS),COLS-1) & 0xf0) >> 4][key.at<uint8_t>((j+1)%(ROWS),COLS-1) & 0x0f]);
                //log("new_key rcon value");
                //log_Mat_value(rcon[j][RCON_INDEX]);
            }
            else
            {
                new_key.at<uint8_t>(j,i) = key.at<uint8_t>(j,i) ^ new_key.at<uint8_t>(j,i-1);
            }
        }
    }
    RCON_INDEX++;
    return new_key;
}