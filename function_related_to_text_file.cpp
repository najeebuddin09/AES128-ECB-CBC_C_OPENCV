#include "AES.hpp"

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
        int number_of_char = char_count(&file_handler);
        int number_of_columns = ceil(number_of_char/ROWS);
        char str[number_of_char];
        file_handler.read(str,number_of_char);
        //printf("number of column: %d number of char: %d\n",number_of_columns,number_of_char);
        Mat data = Mat::zeros(ROWS, number_of_columns,CV_8UC1); 
        int k=0;
        for (int i=0; i<number_of_columns; i++){
            for (int j=0; j<ROWS; j++){
                data.at<uint8_t>(j,i) = (uint8_t)str[k];
                k++;
            }
        }
        file_handler.close();
        return data;
    } else { //return an empty object if file does not open
        Mat data = Mat::zeros(ROWS, COLS,CV_8UC1); 
        return data;
    }
}
//working
/*
        int number_of_char = char_count(&file_handler);
        int number_of_columns = ceil(number_of_char/ROWS);
        char str[number_of_char];
        file_handler.read(str,number_of_char);
        printf("number of column: %d number of char: %d\n",number_of_columns,number_of_char);
        Mat data = Mat::zeros(ROWS, number_of_columns,CV_8UC1); 
        int k=0;
        for (int i=0; i<number_of_columns; i++){
            for (int j=0; j<ROWS; j++){
                data.at<uint8_t>(j,i) = (uint8_t)str[k];
                k++;
            }
        }
        file_handler.close();
*/
//using string class
/*
    fstream file_handler;
    file_handler.open(file,ios::in | ios::binary);

    if (file_handler.is_open()){
        int number_of_char;
        number_of_char = char_count(&file_handler);
        int number_of_columns = ceil(number_of_char/ROWS);
        printf("number of column: %d number of char: %d\n",number_of_columns,number_of_char);
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
*/   
//updated version of above function
/*
        int number_of_char;
        string data_file;
        file_handler>>data_file;
        number_of_char = char_count(&file_handler);
        int number_of_columns = ceil(number_of_char/ROWS);
        printf("number of column: %d number of char: %d\n",number_of_columns,number_of_char);
        Mat data = Mat::zeros(ROWS, number_of_columns,CV_8UC1); 
        string::iterator it = data_file.begin();
        for (int i=0; !file_handler.eof() && i<number_of_columns; i++){
            for (int j=0; !file_handler.eof() && j<ROWS; j++){
                data.at<uint8_t>(j,i) = *it;
                cout<<data.at<uint8_t>(j,i)<<" ";
            }
        }
        //log_block(data);
        file_handler.close(); 
        return data;
*/

void convert_mat_object_into_string_and_store_it_in_a_file(Mat data, const char * file){
    fstream file_handler;
    file_handler.open(file, ios::out | ios::binary | ios::trunc);

    //log("convert_mat_object_into_string_and_store_it_in_a_file");
    //printf("rows: %d cols: %d\n",data.rows,data.cols);

    int number_of_char = data.rows * data.cols;
    char str[number_of_char];

    int k=0;
    if (file_handler.is_open()){
        string data_to_string;
        for (int i=0; i<data.cols; i++){
            for (int j=0; j<data.rows; j++){
                if (i >= data.cols-COLS && data.at<uint8_t>(j,i) == 0){
                    break;
                }
                str[k] = data.at<uint8_t>(j,i); 
                k++;
            }
        }
        file_handler.write(str,k);
        file_handler.close(); 
    }
}
/*
    fstream file_handler;
    file_handler.open(file, ios::out | ios::binary | ios::trunc);

    log("convert_mat_object_into_string_and_store_it_in_a_file");
    printf("rows: %d cols: %d\n",data.rows,data.cols);

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
*/