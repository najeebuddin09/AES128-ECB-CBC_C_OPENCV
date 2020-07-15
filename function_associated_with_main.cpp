#include "AES.hpp"

Mat slice_of_data(Mat data, int x, int y){
    Mat block(4,4,CV_8UC1);
    block = Mat::zeros(4,4,CV_8UC1);
    for (int i=y; i<(y+ROWS); i++){
        for (int j=x; j<(x+COLS); j++){
            if (i<data.rows && j<data.cols){
                block.at<uint8_t>(i-y,j-x) = data.at<uint8_t>(i,j);
            }
        }
    }
    return block;
}

void put_back_together(Mat * destination, Mat source, int x, int y){
    for (int i=y; i<(y+ROWS); i++){
        for (int j=x; j<(x+COLS); j++){
            //printf("i: %d & j: %d destination: %x source: %x\n",i,j,destination->at<uint8_t>(i,j),source.at<uint8_t>(i-y,j-x));
            destination->at<uint8_t>(i,j) = source.at<uint8_t>(i-y,j-x);
        }
    }
}

Mat manipulate_data_any_size_ecb(Mat block, Mat key, Mat callback_function(Mat,Mat)){
    printf("rows: %d cols: %d\n",block.rows-(block.rows%ROWS)+(block.rows%ROWS ? ROWS : 0),block.cols-(block.cols%COLS)+(block.cols%COLS ? COLS : 0));
    Mat crop, encrypted_block = Mat::zeros(block.rows-(block.rows%ROWS)+(block.rows%ROWS ? ROWS : 0),block.cols-(block.cols%COLS)+(block.cols%COLS ? COLS : 0),CV_8UC1);
    int x_axis = 0, y_axis = 0;
    for (int i=0; y_axis < block.rows; i++){
        for (int j=0; x_axis < block.cols; j++){
            crop = slice_of_data(block, x_axis, y_axis);
            //printf("x_axis %d y_axis %d block\n",x_axis,y_axis);
            //log_block(crop);
            crop = callback_function(crop,key);
            if (callback_function == encrypt_block){
                //log("put together function for encryption is called");
                put_back_together(&encrypted_block, crop, x_axis, y_axis);
            } else if (callback_function == decrypt_block){
                //log("put together function for decryption is called");
                put_back_together(&encrypted_block, crop, x_axis, y_axis);
            }
            //printf("x_axis %d y_axis %d encrypted block\n",x_axis,y_axis);
            //log_block(crop);
            x_axis += COLS;
        }
        x_axis = 0;
        y_axis += ROWS;
    }
    return encrypted_block;
}

int char_count(fstream * file_handler){
    char a;
    int char_count = 0;
    file_handler->read(&a,1);
    char_count++;
    while (!file_handler->eof()){
        char_count++;
        file_handler->read(&a,1);

    }
    file_handler->clear();
    file_handler->seekg(0,ios::beg);
    return char_count;
}

Mat read_and_copy_text_file_to_mat_object(const char * file){
    fstream file_handler;
    file_handler.open(file,ios::in | ios::binary);

    if (file_handler.is_open()){
        int number_of_char;
        number_of_char = char_count(&file_handler);
        int number_of_columns = ceil(number_of_char/ROWS);
        //printf("number of column: %d number of char: %d\n",number_of_columns,number_of_char);
        Mat data = Mat::zeros(ROWS, number_of_columns,CV_8UC1); 
        char a;
        file_handler.read(&a,1);
        for (int i=0; !file_handler.eof() && i<number_of_columns; i++){
            for (int j=0; !file_handler.eof() && j<ROWS; j++){
                data.at<uint8_t>(j,i) = a;
                //printf("%x ",a);
                file_handler.read(&a,1);
            }
        }
        //log_block(data);
        file_handler.close(); 
        return data;
    } else { //return an empty object if file does not open
        Mat data = Mat::zeros(ROWS, COLS,CV_8UC1); 
        return data;
    }
}

void convert_mat_object_into_string_and_store_it_in_a_file(Mat data, const char * file){
    fstream file_handler;
    file_handler.open(file, ios::out | ios::binary | ios::trunc);

    //log("convert_mat_object_into_string_and_store_it_in_a_file");
    //printf("rows: %d cols: %d\n",data.rows,data.cols);

    if (file_handler.is_open()){
        char a;
        for (int i=0; i<data.cols; i++){
            for (int j=0; j<data.rows; j++){
                a = (char)data.at<uint8_t>(j,i); 
                //cout<<hex<<(int)data.at<uint8_t>(j,i)<<" ";
                //cout<<hex<<(int)a<<" ";
                if (a == 0){
                    break;
                }
                //printf("i: %d j: %d\n",i,j);
                file_handler.write(&a,1);
                //if (file_handler.eof() ){
                //    log("failbit is set");
                //    exit(1);
                //} 
            }
            if (a == 0){
                break;
            }
        }
        file_handler.close(); 
    }
}