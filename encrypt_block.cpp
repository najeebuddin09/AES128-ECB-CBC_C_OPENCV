#include "AES.hpp"

void encrypt_block(){
    //cout<<"inside the encrypt_block function"<<endl;
    uint8_t test_block[4][4] = {
        {0x19, 0xa0, 0x9a, 0xe9},
        {0x3d, 0xf4, 0xc6, 0xf8},
        {0xe3, 0xe2, 0x8d, 0x48},
        {0xbe, 0x2b, 0x2a, 0x08}
    };

    Mat block(4,4,CV_8UC1);
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            block.at<uint8_t>(i,j) = test_block[i][j];
        }
    } 
    Mat substituted_block = subbyte(block);
    
    cout<<"block of data before substitution"<<endl;
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            //cout<<"Printing in loop"<<endl;
            cout<<std::hex<<(int)block.at<uint8_t>(i,j)<<' ';
        }
        cout<<endl;
    } 
    
    cout<<"block of data after substitution"<<endl;
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            //cout<<"Printing in loop"<<endl;
            cout<<std::hex<<(int)substituted_block.at<uint8_t>(i,j)<<' ';
        }
        cout<<endl;
    } 
}