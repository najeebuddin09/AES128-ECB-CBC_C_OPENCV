#include "AES.hpp"

int search_through_program_args(int argc, char ** argv, const char * search_for){
    for (int i=1; i<argc; i++){
        if(!strcmp(argv[i],search_for)){
            return i;
        }
    }
    return 0;
}

Mat retrieve_arg(int argc, char ** argv, const char * type){
    Mat type_key(ROWS,COLS,CV_8UC1);
    char a;
    char b[2];
    //log("before calling search function");
    int argument_index = search_through_program_args(argc,argv,type)+1;
    string key_type = argv[argument_index];
    //log("after calling search function");
    //cout<<key_type<<endl;
    int k = 0;
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            //log("before copy");
            key_type.copy(b,2,k);
            //log("before sscanf");
            sscanf(b,"%x",&a);
            //cout<<hex<<a<<" ";
            type_key.at<uint8_t>(i,j) = a;
            k+=2;
        }
    }
    //log("retrieved key");
    //log_block(type_key);
    return type_key;
}