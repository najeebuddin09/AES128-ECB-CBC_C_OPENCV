#include "AES.hpp"

int main(int argc, char ** argv){

    #include "args_checks.hpp"
        
    if (strstr(file,".txt")!=NULL){
        //log("inside text file encryption condition");
        //check file existence
        fstream check_existence(file);
        if (!check_existence.is_open()){
            log("ERROR: Sorry this file does not exist");
            return 1;
        }
        check_existence.close();

        Mat key = retrieve_arg(argc,argv,"-key");
        
        //log("before reading from file");
        Mat data = read_and_copy_text_file_to_mat_object(file);
        Mat encrypted_data;
        struct timeval stop, start;
        //log("before condition check for mode");
        if (search_through_program_args(argc,argv,"-cbc")){
            Mat iv = retrieve_arg(argc,argv,"-iv");
            gettimeofday(&start, NULL);
            encrypted_data = manipulate_data_any_size_cbc(data,key,iv,encrypt_block);
            gettimeofday(&stop, NULL);
        } else {
            gettimeofday(&start, NULL);
            encrypted_data = manipulate_data_any_size_ecb(data,key,encrypt_block);
            gettimeofday(&stop, NULL);
        }
        const char * encrypted_file_name = "encrypted_file.txt";
        //log("before writing to file");
        convert_mat_object_into_string_and_store_it_in_a_file(encrypted_data,encrypted_file_name);
        cout<<encrypted_file_name<<" file created that contains the encrypted text"<<endl;
        cout<<"The encryption took about "<<(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec<<"  micro seconds"<<endl;
    } else if (strstr(file,".jpg")!=NULL){
        Mat image = imread(file,IMREAD_COLOR);    

        if (image.empty()){
            log("ERROR: Sorry the file does not exist");
            return 1;
        } 

        Mat splitChannels[3];
        Mat encrypted_splitChannels[3];
        Mat key = retrieve_arg(argc,argv,"-key");
        struct timeval stop, start;

        split(image, splitChannels);
        if (search_through_program_args(argc,argv,"-cbc")){
            Mat iv = retrieve_arg(argc,argv,"-iv");
            gettimeofday(&start, NULL);
            for (int i=0; i<3; i++){
                encrypted_splitChannels[i] = manipulate_data_any_size_cbc(splitChannels[i], key, iv, encrypt_block);    
            }
            gettimeofday(&stop, NULL);
        } else {
            gettimeofday(&start, NULL);
            for (int i=0; i<3; i++){
                encrypted_splitChannels[i] = manipulate_data_any_size_ecb(splitChannels[i], key, encrypt_block);    
            }
            gettimeofday(&stop, NULL);
        }

        Mat encrypted_image;

        merge(encrypted_splitChannels, 3, encrypted_image);
        const char * encrypted_file_name = "encrypted_file.png";
        imwrite(encrypted_file_name,encrypted_image);
        cout<<encrypted_file_name<<" file created that contains the encrypted image"<<endl;
        cout<<"The encryption took about "<<(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec<<"  micro seconds"<<endl;
   }



    return 0;
}
// test for encrypt_block function
/*
    uint8_t test_block[ROWS][COLS] = {
        {0x32, 0x88, 0x31, 0xe0},
        {0x43, 0x5a, 0x31, 0x37},
        {0xf6, 0x30, 0x98, 0x07},
        {0xa8, 0x8d, 0xa2, 0x34}
    };
    
    uint8_t test_key[ROWS][COLS] = {
        {0x2b, 0x28, 0xab, 0x09},
        {0x7e, 0xae, 0xf7, 0xcf},
        {0x15, 0xd2, 0x15, 0x4f},
        {0x16, 0xa6, 0x88, 0x3c}
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
    
    log("block of data");
    log_block(block); 

    Mat encrypted_block = encrypt_block(block,key);
    
    log("block of data after encryption");
    log_block(encrypted_block); 
*/