#include "AES.hpp"

void log(const char * str){
    cout<<str<<endl;
}

void log_block(Mat block){
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            cout<<std::hex<<(int)block.at<uint8_t>(i,j)<<' ';
        }
        cout<<endl;
    } 

}

void log_Mat_value(uint8_t a){
    cout<<hex<<(int)a<<endl;
}